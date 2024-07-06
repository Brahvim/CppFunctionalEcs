#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "Ecs.h"

#pragma region // API Implementation.

/*
## Entities Table Layout
    / ------------------------------------------------------------------ \
    |  IDs  | Component Arrays | Component Counts | Component Capacities |
    | ------------------------------------------------------------------ |
[0] |   0   | [..............] |        0         |           4          |
[1] |   6   | [..#...........] |        1         |           3          |
[2] |   2   | [..#..#........] |        2         |           2          |
[3] |   3   | [..#..#..#.....] |        3         |           1          |
[4] |   9   | [..#..#..#..#..] |        4         |           0          |
    \ ------------------------------------------------------------------ /

- Each column - each heading - each top-down region of the table, represents an array.

- The vertically-placed square brackets on the left show array indices.
  They show that each row of the table - each left-right region, represents an entry in each of these arrays, and thus, an entry in the table.

- Components are stored in a "sparse" manner.
  Only the ID, and some *type information* (see the use of `struct ecs_component_type` in `struct ecs_component`) is stored by the elements
  of the "Component Arrays" (`struct ecs_components_darray`).

- Each column's corresponding *actual array* is stored as a `struct` so its length may be tracked:

/ -------------------------------------------------------------- \
| Column Name             : Code Representation                  |
| -------------------------------------------------------------- |
| IDs                     : `struct ecs_entities_array`,         |
| Component Arrays        : `struct ecs_components_darray`,      |
| Component Counts        : `struct ecs_component_counts_array`, |
| Component Capacities    : `struct ecs_caps_array`.             |
\ -------------------------------------------------------------- /

- Each `struct` stores the "actual array `struct`s" as direct members and not pointers to disallow further re-direction.
*/

struct ecs_component_counts_array {

    size_t capacity;
    size_t *array;

};

struct ecs_component_caps_array {

    size_t capacity;
    size_t *array;

};

struct ecs_components_darray {

    size_t capacity;
    struct ecs_component **darray;

};

struct ecs_entities_array {

    size_t capacity;
    struct ecs_entity *array;

};

struct ecs_entities_table {

    struct ecs_entities_array entities;
    struct ecs_components_darray components;
    struct ecs_component_counts_array counts;

};

struct ecs_instance {

    size_t next_id;
    size_t entry_count;
    struct ecs_entities_table table;

};

size_t check_overflow_calloc_style(const size_t p_count, const size_t p_element_size) {
    const size_t to_ret =
        (p_element_size != 0 && p_count > __SIZE_MAX__ / p_element_size)
        ? 0
        : p_count * p_element_size;
    return to_ret;
}

void ecs_print_table(struct ecs_instance *p_instance) {
    // I have done the table-spaces-sorting thing before, but I'm not doing it this time...
    puts("ECS entities table (format):");
    puts("------------------------------------------------");
    puts("| Index | Entity ID | Components Array Address |");
    puts("------------------------------------------------");
    puts("Table data:");
    puts("------------------------------------------------");
    for (size_t i = 0; i < p_instance->entry_count; ++i) {
        printf("| %zu | %zu | %p |\n",
            i,
            p_instance->table.entities.array[i].id,
            p_instance->table.components.darray);
    }
    puts("------------------------------------------------");
}

const char* const ecs_status_to_string(enum ecs_status p_status) {
    switch (p_status) {
        default: return "Unknown status";
        case ECS_STATUS_OKAY:                       return "Okay";
        case ECS_STATUS_MALLOC:                     return "Memory allocation failure";
        case ECS_STATUS_INVALID_ENTITY:             return "Invalid `struct ecs_entity`";
        case ECS_STATUS_INVALID_INSTANCE:           return "Invalid `struct ecs_instance`";
        case ECS_STATUS_INVALID_COMPONENT:          return "Invalid `struct ecs_component`";
        case ECS_STATUS_ENTITY_MALLOC:              return "Memory allocation failure for IDs array";
        case ECS_STATUS_COMPONENT_MALLOC:           return "Memory allocation failure for components arrays";
        case ECS_STATUS_COMPONENT_COUNT_MALLOC:     return "Memory allocation failure for component counts array";
    }
}

// If you have to write more allocations here, MAKE SURE TO FREE THEM!:
enum ecs_status ecs_create_instance(struct ecs_instance **p_instance) {
    struct ecs_instance *to_ret = malloc(sizeof(struct ecs_instance));

    if (!to_ret)
        return ECS_STATUS_MALLOC;

    // Initialization:

    // NOLINTBEGIN(clang-analyzer-optin.portability.UnixAPI)
    to_ret->table.counts.array = malloc(check_overflow_calloc_style(ECS_INITIAL_ENTITY_CAPACITY, sizeof(size_t)));
    to_ret->table.entities.array = malloc(check_overflow_calloc_style(ECS_INITIAL_ENTITY_CAPACITY, sizeof(struct ecs_entity)));
    to_ret->table.components.darray = malloc(check_overflow_calloc_style(ECS_INITIAL_ENTITY_CAPACITY, sizeof(struct ecs_component*)));
    // NOLINTEND(clang-analyzer-optin.portability.UnixAPI)

    // Checks (in the given order because checks on data "seated deeper" *might* be optimized by cache.
    // Of course that's not necessary at all here - just felt like telling what I noticed):
    if (!to_ret->table.components.darray) {
        *p_instance = to_ret;
        return ECS_STATUS_COMPONENT_MALLOC;
    } else to_ret->table.components.capacity = ECS_INITIAL_ENTITY_CAPACITY;

    // PS We set the `*p_instance` at tail ends (right before returning) due to the possibility of threaded code.
    if (!to_ret->table.entities.array) {
        *p_instance = to_ret;
        return ECS_STATUS_ENTITY_MALLOC;
    } else to_ret->table.entities.capacity = ECS_INITIAL_ENTITY_CAPACITY;

    if (!to_ret->table.counts.array) {
        *p_instance = to_ret;
        return ECS_STATUS_COMPONENT_COUNT_MALLOC;
    } else to_ret->table.counts.capacity = ECS_INITIAL_ENTITY_CAPACITY;

    to_ret->next_id = 0;
    to_ret->entry_count = 0;

    struct ecs_entity *null_entity;
    ecs_create_entity(to_ret, &null_entity);

    *p_instance = to_ret;
    return ECS_STATUS_OKAY;
}

// Hey, buddy!
// If you're here to edit this one, good luck.
// Remember to take your time. You **need** to give this guy a lot of time.
// *Don't run away!*
enum ecs_status ecs_destroy_instance(struct ecs_instance *p_instance) {
    if (!p_instance)
        return ECS_STATUS_INVALID_INSTANCE;

    struct ecs_entities_table *table = &(p_instance->table);

    if (!table)
        goto free_instance_now;

#pragma region // Free the `table`!
    size_t *counts = table->counts.array;
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

bool ecs_ensure_space(struct ecs_instance *const p_instance, size_t p_entity_count) {
    if (p_instance->table.counts.capacity >= p_entity_count
        && p_instance->table.components.capacity >= p_entity_count
        && p_instance->table.entities.capacity >= p_entity_count)
        return true;

    size_t *counts = realloc(p_instance->table.counts.array, p_entity_count * sizeof(size_t));
    struct ecs_entity *entities = realloc(p_instance->table.entities.array, p_entity_count * sizeof(struct ecs_entity));
    struct ecs_component **components = realloc(p_instance->table.components.darray, p_entity_count * sizeof(struct ecs_component*));

    if (counts) {
        p_instance->table.counts.array = counts;
        p_instance->table.counts.capacity = p_entity_count;
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

enum ecs_status ecs_create_entity(struct ecs_instance *const p_instance, struct ecs_entity **p_entity) {
    ecs_print_table(p_instance);

    if (!ecs_ensure_space(p_instance, p_instance->next_id))
        return ECS_STATUS_MALLOC;

    const size_t id = p_instance->next_id;

    struct ecs_entity *to_assign = &(p_instance->table.entities.array[p_instance->next_id]);
    p_instance->table.components.darray[id] = NULL;
    p_instance->table.counts.array[id] = 0;
    to_assign->id = id;

    // We have reserved our space, dear threads in crime!:
    ++(p_instance->next_id);
    ++(p_instance->entry_count);
    // (Yeah, I know I'm telling them about it late...)

    *p_entity = to_assign;
    return ECS_STATUS_OKAY;
}

enum ecs_status ecs_destroy_entity(struct ecs_instance *const p_instance, struct ecs_entity *p_entity) {
    if (p_entity->id == 0)
        return ECS_STATUS_INVALID_ENTITY;

    size_t i = 0;

    // TODO Replace with map when that happens, else a cache-aware search!:
    for (; i < p_instance->entry_count; ++i)
        if (p_instance->table.entities.array[i].id == p_entity->id)
            break;

    // Remember - `entry_count` is itself out-of-bounds. It is the upper limit:
    if (i == p_instance->entry_count)
        return ECS_STATUS_INVALID_ENTITY;

    p_instance->table.components.darray[i] = p_instance->table.components.darray[p_instance->entry_count - 1];
    p_instance->table.counts.array[i] = p_instance->table.counts.array[p_instance->entry_count - 1];
    --(p_instance->entry_count);
    p_entity->id = 0;

    return ECS_STATUS_OKAY;
}
#pragma endregion
