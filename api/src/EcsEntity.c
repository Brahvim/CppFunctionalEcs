#include <memory.h>
#include <stdlib.h>

#include "Ecs.h"

#pragma region // API Implementation.
struct ecs_component_counts_array {

    size_t capacity;
    size_t *array;

};

struct ecs_components_array {

    size_t capacity;
    struct ecs_component **darray;

};

struct ecs_entities_array {

    size_t capacity;
    struct ecs_entity *array;

};

struct ecs_entities_table {

    struct ecs_entities_array entities;
    struct ecs_components_array components;
    struct ecs_component_counts_array component_counts;

};

struct ecs_instance {

    size_t next_id;
    size_t entry_count;
    struct ecs_entities_table table;

};

size_t check_overflow_calloc_style(const size_t p_count, const size_t p_element_size) {
    return (p_element_size != 0 && p_count > __SIZE_MAX__ / p_element_size) ? p_count * p_element_size : 0;
}

// If you have to write more allocations here, MAKE SURE TO FREE THEM!:
enum ecs_status ecs_create(struct ecs_instance **p_instance) {
    struct ecs_instance *to_ret = malloc(sizeof(struct ecs_instance));

    if (!to_ret)
        return ECS_STATUS_MALLOC;

    // Initialization:
    to_ret->table.component_counts.array = malloc(check_overflow_calloc_style(ECS_INITIAL_ENTITY_CAPACITY, sizeof(size_t)));
    to_ret->table.entities.array = malloc(check_overflow_calloc_style(ECS_INITIAL_ENTITY_CAPACITY, sizeof(struct ecs_entity)));
    to_ret->table.components.darray = malloc(check_overflow_calloc_style(ECS_INITIAL_ENTITY_CAPACITY, sizeof(struct ecs_component*)));

    // Checks (in the given order because checks on data "seated deeper" *might* be optimized by cache.
    // Of course that's not necessary at all here - just felt like telling what I noticed):
    if (!to_ret->table.entities.array) {
        *p_instance = to_ret;
        return ECS_STATUS_ENTITY_MALLOC;
    } else to_ret->table.entities.capacity = ECS_INITIAL_ENTITY_CAPACITY;

    // PS We set the `*p_instance` at tail ends (right before returning) due to the possibility of threaded code.
    if (!to_ret->table.components.darray) {
        *p_instance = to_ret;
        return ECS_STATUS_COMPONENT_MALLOC;
    } else to_ret->table.components.capacity = ECS_INITIAL_ENTITY_CAPACITY;

    if (!to_ret->table.component_counts.array) {
        *p_instance = to_ret;
        return ECS_STATUS_COMPONENT_COUNT_MALLOC;
    } else to_ret->table.component_counts.capacity = ECS_INITIAL_ENTITY_CAPACITY;

    to_ret->next_id = 1;
    to_ret->entry_count = 0;

    *p_instance = to_ret;
    return ECS_STATUS_OKAY;
}

// Hey, buddy!
// If you're here to edit this one, good luck.
// Remember to take your time. You **need** to give this guy a lot of time.
// *Don't run away!*
enum ecs_status ecs_destroy(struct ecs_instance *p_instance) {
    if (!p_instance)
        return ECS_STATUS_INVALID_INSTANCE;

    struct ecs_entities_table *table = &(p_instance->table);

    if (!table)
        goto free_instance_now;

#pragma region // Free the `table`!
    size_t *counts = table->component_counts.array;
    struct ecs_component **components = table->components.darray;

    if (table->entities.array)
        free(table->entities.array);

    if (!counts) {
        free(components);
        goto free_instance_now;
    }

    if (!components) {
        free(counts);
        goto free_instance_now;
    }

#pragma region // Destroy the components!
    // For every entry:
    for (size_t i = 0; i < p_instance->entry_count; ++i) {
        // Fetch its array:
        struct ecs_component *array = components[i];

        if (!array)
            continue;

        // ...And detach all components inside!:
        for (size_t j = 0; j < counts[i]; ++j) {
            struct ecs_component c = array[j];
            c.type->destructor(&c);
        }

        free(array);
    }
#pragma endregion

    free(components);
    free(counts);
#pragma endregion

    // VSCode keeps indenting this:
    free_instance_now:
    free(p_instance);
    return ECS_STATUS_OKAY;
}

bool ecs_ensure_space(struct ecs_instance *p_instance, size_t p_entity_count) {
    if (p_instance->table.component_counts.capacity >= p_entity_count
        && p_instance->table.components.capacity >= p_entity_count
        && p_instance->table.entities.capacity >= p_entity_count)
        return true;

    size_t *counts = realloc(p_instance->table.component_counts.array, p_entity_count * sizeof(size_t));
    struct ecs_entity *entities = realloc(p_instance->table.entities.array, p_entity_count * sizeof(struct ecs_entity));
    struct ecs_component **components = realloc(p_instance->table.components.darray, p_entity_count * sizeof(struct ecs_component*));

    if (counts) {
        p_instance->table.component_counts.array = counts;
        p_instance->table.component_counts.capacity = p_entity_count;
    }

    if (entities) {
        p_instance->table.entities.array = entities;
        p_instance->table.entities.capacity = p_entity_count;
    }

    if (components) {
        p_instance->table.components.darray = components;
        p_instance->table.components.capacity = p_entity_count;
    }

    return counts && entities && components;
}

enum ecs_status ecs_create_entity(struct ecs_instance* const p_instance, struct ecs_entity **p_entity) {
    const size_t next_id = p_instance->entry_count + 1;

    if (!ecs_ensure_space(p_instance, next_id))
        return ECS_STATUS_MALLOC;

    ++(p_instance->entry_count); // We have reserved the space, other thread in crime!

    struct ecs_entity *const to_assign = malloc(sizeof(struct ecs_entity));
    enum ecs_status to_ret = ECS_STATUS_OKAY;

    if (!to_assign)
        return ECS_STATUS_ENTITY_MALLOC;

    // p_instance->table.entities.array[next_id] = (struct ecs_entity) { .id = next_id };
    p_instance->table.components.darray[next_id] = malloc(sizeof(struct ecs_component**));
    p_instance->table.entities.array[next_id] = *to_assign;
    p_instance->table.component_counts.array[next_id] = 0;

    if (!p_instance->table.components.darray[next_id])
        to_ret = ECS_STATUS_COMPONENT_MALLOC;

    *p_entity = to_assign;
    return to_ret;
}

enum ecs_status ecs_destroy_entity(struct ecs_instance* const p_instance, struct ecs_entity *p_entity) {

}

const char* const ecs_status_to_string(enum ecs_status p_status) {
    switch (p_status) {
        default: return "Unknown status";
        case ECS_STATUS_OKAY:                       return "Okay";
        case ECS_STATUS_MALLOC:                     return "Memory allocation failure";
        case ECS_STATUS_INVALID_ENTITY:             return "Invalid `struct ecs_entity`";
        case ECS_STATUS_INVALID_INSTANCE:           return "Invalid `struct ecs_instance`";
        case ECS_STATUS_INVALID_COMPONENT:          return "Invalid `struct ecs_component`";
        case ECS_STATUS_ENTITY_MALLOC:                  return "Memory allocation failure for IDs array";
        case ECS_STATUS_COMPONENT_MALLOC:          return "Memory allocation failure for components arrays";
        case ECS_STATUS_COMPONENT_COUNT_MALLOC:    return "Memory allocation failure for component counts array";
    }
}
#pragma endregion
