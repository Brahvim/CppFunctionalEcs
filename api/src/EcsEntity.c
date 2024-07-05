#include <memory.h>
#include <stdlib.h>

#include "Ecs.h"

#pragma region // API Implementation.
size_t check_overflow_calloc_style(const size_t p_count, const size_t p_element_size) {
    return (p_element_size != 0 && p_count > __SIZE_MAX__ / p_element_size) ? p_count * p_element_size : 0;
}

enum ecs_status ecs_create(struct ecs_instance **p_instance) {
    struct ecs_instance *to_ret = malloc(sizeof(struct ecs_instance));

    if (!to_ret)
        return ECS_STATUS_MALLOC;

    // We set the `*p_instance` at tail ends (right before returning) due to the possibility of threaded code.

    // Initialization:
    to_ret->entry_count = ECS_INITIAL_ENTITY_CAPACITY;
    to_ret->table.capacity = ECS_INITIAL_ENTITY_CAPACITY;
    to_ret->table.component_counts = calloc(ECS_INITIAL_ENTITY_CAPACITY, sizeof(size_t));
    to_ret->table.ids_array = calloc(ECS_INITIAL_ENTITY_CAPACITY, sizeof(struct ecs_entity));
    to_ret->table.components = calloc(ECS_INITIAL_ENTITY_CAPACITY, sizeof(struct ecs_component*));

    // Checks (in the given order because checks on data "seated deeper" *might* be optimized by cache.
    // Of course that's not necessary at all here - just felt like telling what I noticed):
    if (!to_ret->table.ids_array) {
        *p_instance = to_ret;
        return ECS_STATUS_ID_MALLOC;
    }

    if (!to_ret->table.components) {
        *p_instance = to_ret;
        return ECS_STATUS_COMPONENTS_MALLOC;
    }

    if (!to_ret->table.component_counts) {
        *p_instance = to_ret;
        return ECS_STATUS_COMPONENT_COUNTS_MALLOC;
    }

    *p_instance = to_ret;
    return ECS_STATUS_OKAY;
}

enum ecs_status ecs_destroy(struct ecs_instance *p_instance) {
    if (!p_instance)
        return ECS_STATUS_INVALID_INSTANCE;

    struct ecs_entities_table *table = &(p_instance->table);

    if (!table)
        goto table_does_not_exist;

    size_t *counts = table->component_counts;
    struct ecs_component **components = table->components;

    if (table->ids_array)
        free(table->ids_array);

    if (!counts) {
        free(components);
        goto table_arrays_do_not_exist;
    }

    if (!components) {
        free(counts);
        goto table_arrays_do_not_exist;
    }

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

    free(components);
    free(counts);

table_arrays_do_not_exist:
    // free(table); ...Uhh, apparently you can't deallocate `struct` members.
    // Probably 'cause their addresses ain't a part'a the free-list!

table_does_not_exist:
    free(p_instance);
    return ECS_STATUS_OKAY;
}

const char* const ecs_status_to_string(enum ecs_status p_status) {
    switch (p_status) {
        default: return "Unknown status";
        case ECS_STATUS_OKAY: return "Okay";
        case ECS_STATUS_MALLOC: return "Memory allocation failure";
        case ECS_STATUS_INVALID_ENTITY: return "Invalid `struct ecs_entity`";
        case ECS_STATUS_INVALID_INSTANCE: return "Invalid `struct ecs_instance`";
        case ECS_STATUS_INVALID_COMPONENT: return "Invalid `struct ecs_component`";
        case ECS_STATUS_ID_MALLOC: return "Memory allocation failure for IDs array";
        case ECS_STATUS_COMPONENTS_MALLOC: return "Memory allocation failure for components arrays";
        case ECS_STATUS_COMPONENT_COUNTS_MALLOC: return "Memory allocation failure for component counts array";
    }
}
#pragma endregion
