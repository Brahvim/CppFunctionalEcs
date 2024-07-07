#include <stdio.h>

#include "Ecs.h"
#include "EcsInternals.h"

#pragma region // API Implementation.
// If you have to write more allocations here, MAKE SURE TO FREE THEM!:
enum ecs_status ecs_context_create(struct ecs_context **p_context) {
    struct ecs_context *to_ret = malloc(sizeof(struct ecs_context));

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
        *p_context = to_ret;
        return ECS_STATUS_COMPONENT_MALLOC;
    } else to_ret->table.components.capacity = ECS_INITIAL_ENTITY_CAPACITY;

    // PS We set the `*p_context` at tail ends (right before returning) due to the possibility of threaded code.
    if (!to_ret->table.entities.array) {
        *p_context = to_ret;
        return ECS_STATUS_ENTITY_MALLOC;
    } else to_ret->table.entities.capacity = ECS_INITIAL_ENTITY_CAPACITY;

    if (!to_ret->table.counts.array) {
        *p_context = to_ret;
        return ECS_STATUS_COMPONENT_COUNT_MALLOC;
    } else to_ret->table.counts.capacity = ECS_INITIAL_ENTITY_CAPACITY;

    to_ret->next_id = 0;
    to_ret->entry_count = 0;

    *p_context = to_ret;
    return ECS_STATUS_OKAY;
}

// Hey, buddy!
// If you're here to edit this one, good luck.
// Remember to take your time. You **need** to give this guy a lot of time.
// *Don't run away!*
enum ecs_status ecs_context_destroy(struct ecs_context *p_context) {
    if (!p_context)
        return ECS_STATUS_INVALID_CONTEXT;

    struct ecs_context_table *table = &(p_context->table);

    if (!table)
        goto free_context_now;

#pragma region // Free the `table`!
    size_t *counts = table->counts.array;
    struct ecs_component **components = table->components.darray;

    if (table->entities.array)
        free(table->entities.array);

    if (!counts) {
        free(components);
        goto free_context_now;
    }

    if (!components) {
        free(counts);
        goto free_context_now;
    }

#pragma region // Destroy the components!
    // For every entry:
    for (size_t i = 0; i < p_context->entry_count; ++i) {
        // Fetch its array:
        struct ecs_component *array = components[i];

        if (!array)
            continue;

        // ...And detach all components inside!:
        for (size_t j = 0; j < counts[i]; ++j) {
            struct ecs_component c = array[j];
            c.type->detacher(&c);
        }

        free(array);
    }
#pragma endregion

    free(components);
    free(counts);
#pragma endregion

    // VSCode keeps indenting this:
    free_context_now:
    free(p_context);
    return ECS_STATUS_OKAY;
}

size_t ecs_context_trim(struct ecs_context *p_context) {
    size_t to_ret = 0;
    const size_t need = p_context->entry_count;
    struct ecs_context_table *const table = &p_context->table;

    void **arrays[] = {
        (void **) &table->counts.array,
        (void **) &table->entities.array,
        (void **) &table->components.darray
    };

    size_t *capacities[] = {
       &table->counts.capacity,
       &table->entities.capacity,
       &table->components.capacity
    };

    const size_t element_sizes[] = {
        sizeof(size_t),
        sizeof(struct ecs_entity),
        sizeof(struct ecs_component*),
    };

    const size_t num_arrays = sizeof(arrays) / sizeof(arrays[0]);

    for (size_t i = 0; i < num_arrays; ++i) {

        const size_t capacity = (*capacities[i]);
        const size_t diff = capacity - need;

        if (diff < 1)
            continue;

        to_ret += diff * capacity;
        void *array = (*arrays[i]); // Remember, this is a copy!

        // cppcheck-suppress memleakOnRealloc
        array = realloc(array, need * element_sizes[i]);

        // These are modifications - they won't benefit from "cached values":
        (*capacities[i]) = need;
        (*arrays[i]) = array;

        // The stuff *above* would. - but it's the only one who needs it!
        // I should *always* leave stuff like this to the compiler anyway!...

    }

    return to_ret;
}

bool ecs_context_ensure_space(struct ecs_context *const p_context, const size_t p_entity_count) {
    if (p_context->table.counts.capacity >= p_entity_count
        && p_context->table.components.capacity >= p_entity_count
        && p_context->table.entities.capacity >= p_entity_count)
        return true;

    size_t *counts = p_context->table.counts.array;
    struct ecs_entity *entities = p_context->table.entities.array;
    struct ecs_component **components = p_context->table.components.darray;

    // cppcheck-suppress memleakOnRealloc
    counts = realloc(counts, p_context->table.counts.capacity * 2 * sizeof(size_t));
    // cppcheck-suppress memleakOnRealloc
    entities = realloc(entities, p_context->table.entities.capacity * 2 * sizeof(struct ecs_entity));
    // cppcheck-suppress memleakOnRealloc
    components = realloc(components, p_context->table.components.capacity * 2 * sizeof(struct ecs_component*));

    if (counts) {
        p_context->table.counts.capacity *= 2;
        p_context->table.counts.array = counts;
    }

    if (entities) {
        p_context->table.entities.capacity *= 2;
        p_context->table.entities.array = entities;
    }

    if (components) {
        p_context->table.components.capacity *= 2;
        p_context->table.components.darray = components;
    }

    return counts && entities && components;
}

void ecs_context_print_table(const struct ecs_context *p_context) {
    // I have done the table-spaces-sorting thing before, but I'm not doing it this time...
    puts("ECS entities table (format):");
    puts("------------------------------------------------");
    puts("| Index | Entity ID | Components Array Address |");
    puts("------------------------------------------------");
    puts("Table data:");
    puts("------------------------------------------------");
    for (size_t i = 0; i < p_context->entry_count; ++i) {
        printf("| %zu | %zu | %p |\n",
            i,
            p_context->table.entities.array[i].id,
            p_context->table.components.darray);
    }
    puts("------------------------------------------------");
}

const char* const ecs_context_status_to_string(enum ecs_status p_status) {
    switch (p_status) {
        default: return "Unknown status";
        case ECS_STATUS_OKAY:                       return "Okay";
        case ECS_STATUS_MALLOC:                     return "Memory allocation failure";
        case ECS_STATUS_INVALID_ENTITY:             return "Invalid `struct ecs_entity`";
        case ECS_STATUS_INVALID_CONTEXT:           return "Invalid `struct ecs_context`";
        case ECS_STATUS_INVALID_COMPONENT:          return "Invalid `struct ecs_component`";
        case ECS_STATUS_ENTITY_MALLOC:              return "Memory allocation failure for IDs array";
        case ECS_STATUS_COMPONENT_MALLOC:           return "Memory allocation failure for components arrays";
        case ECS_STATUS_COMPONENT_COUNT_MALLOC:     return "Memory allocation failure for component counts array";
    }
}

size_t ecs_context_entity_count(const struct ecs_context *const p_context) {
    return p_context->entry_count;
}
#pragma endregion
