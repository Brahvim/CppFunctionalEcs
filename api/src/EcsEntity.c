#include <memory.h>
#include <stdlib.h>

#include "Ecs.h"

extern size_t check_overflow_calloc_style(const size_t count, const size_t element_size);

#pragma region // Macros.
/**
 * This one *should be* casted to `size_t` before it's used in the ECS implementation.
 * The free list's size is half of this. By default, this value is `8`!
 */
#define ECS_INITIAL_ENTITY_CAPACITY 8

 /** Set any code you want run when initial allocations fail! */
#define ECS_INITIAL_ALLOCATION_FAILURE_CODE_BLOCK
#pragma endregion

#pragma region // Stuff used locally.
struct entity_components_soa {

    struct ecs_component ***data;
    size_t allocated_length;
    size_t used_length;

};

void destroy_entity_components_map(struct entity_components_soa *p_map) {
    if (!p_map)
        return;

    // Destroy all components in from entities:

    // for (size_t i = 0; i < p_map->used_length; ++i) {
    //     struct ecs_component *const component = p_map->data[i];
    //     const struct ecs_component_type *const type = component->type;
    //     const struct ecs_entity entity = type->entity_getter(component);
    //     type->destructor(entity, component);
    // }

    for (size_t i = 0; i < p_map->used_length; ++i) {
        struct ecs_component **typed_components = p_map->data[i];
        if (!typed_components)
            continue;

        for (size_t j = 0; j < p_map->allocated_length; ++j) {
            struct ecs_component *const component = typed_components[j];
            if (!component)
                continue;

            const struct ecs_component_type *const type = component->type;
            const struct ecs_entity entity = type->entity_getter(component);
            type->destructor(entity, component);
            free(component);
        }

        free(typed_components);
    }

    if (p_map->data)
        free(p_map->data);

    free(p_map);
}

struct entity_components_soa* create_entity_components(const size_t p_initial_capacity) {
    struct entity_components_soa *map = malloc(sizeof(struct entity_components_soa));
    if (!map)
        goto fail_no_free;

    const size_t alloc_size = check_overflow_calloc_style(p_initial_capacity, sizeof(struct ecs_component*));
    if (alloc_size == 0)
        goto fail;

    map->data = malloc(p_initial_capacity * sizeof(struct ecs_component**));

    if (!map->data)
        goto fail;

    map->allocated_length = p_initial_capacity;
    map->used_length = 0;

    return map;

fail:
    free(map);
fail_no_free:
    ECS_INITIAL_ALLOCATION_FAILURE_CODE_BLOCK;
    return NULL;
}
#pragma endregion

#pragma region // `static`s.
static size_t s_count = 0;
static size_t s_allocs = 0;

static struct entity_components_soa *s_entity_components_map;
#pragma endregion

// This is called in `EcsManager.c`'s `ecs_init()`:
void ecs_entity_init() {
    s_entity_components_map = create_entity_components(ECS_INITIAL_ENTITY_CAPACITY);
}

void ecs_entity_cleanup() {
    destroy_entity_components_map(s_entity_components_map);
}

#pragma region // API implementation.
size_t entity_get_count() {
    return s_count;
}

enum entity_status entity_destroy(struct ecs_entity p_entity) {
    return ENTITY_STATUS_OKAY;
}

enum entity_status entity_create(struct ecs_entity *p_storage) {
    if (s_count >= s_allocs) {
        const size_t new_capacity_as_count = s_allocs == 0 ? ECS_INITIAL_ENTITY_CAPACITY : check_overflow_calloc_style(s_allocs, 2);
        const size_t new_capacity_as_bytes = check_overflow_calloc_style(new_capacity_as_count, sizeof(struct ecs_entity));

        if (!new_capacity_as_bytes)
            return ENTITY_STATUS_MALLOC;

        s_allocs = new_capacity_as_count;
    }

    return ENTITY_STATUS_OKAY;
}

// enum entity_status entity_ensure_allocations_for(size_t p_count) {
//     return ENTITY_STATUS_OKAY;
// }

// size_t entity_get_component_type_count(const struct ecs_entity p_entity, const struct ecs_component_type *p_type) {
//     return 0;
// }

enum entity_status entity_ensure_allocations_for(size_t p_count) {
    // Ensure capacity for the requested number of entities
    if (p_count > s_allocs) {
        const size_t new_capacity_as_count = p_count;
        const size_t new_capacity_as_bytes = check_overflow_calloc_style(new_capacity_as_count, sizeof(struct ecs_entity));

        if (!new_capacity_as_bytes)
            return ENTITY_STATUS_MALLOC;

        s_allocs = new_capacity_as_count;
    }

    return ENTITY_STATUS_OKAY;
}

size_t entity_get_component_type_count(const struct ecs_entity p_entity, const struct ecs_component_type *p_type) {
    // Retrieve count of components of a specific type for an entity
    if (p_entity.id >= s_entity_components_map->used_length)
        return 0;

    struct ecs_component **components = s_entity_components_map->data[p_entity.id];
    if (!components)
        return 0;

    size_t count = 0;
    for (size_t i = 0; i < s_entity_components_map->used_length; ++i) {
        if (components[i] && components[i]->type == p_type) {
            count++;
        }
    }
    return count;
}

enum entity_status entity_attach_component(const struct ecs_entity p_entity, const struct ecs_component *p_component) {
    return ENTITY_STATUS_OKAY;
}

struct ecs_component* entity_get_components(const struct ecs_entity p_entity, const struct ecs_component_type *p_type) {
    return NULL;
}

enum entity_status entity_detach_component(const struct ecs_entity p_entity, const struct ecs_component_type *p_component_type) {
    return ENTITY_STATUS_OKAY;
}
#pragma endregion
