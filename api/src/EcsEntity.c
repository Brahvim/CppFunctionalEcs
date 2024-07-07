#include "Ecs.h"
#include "EcsEntityInternals.h"

#pragma region // API Implementation.
enum ecs_status ecs_entity_create(struct ecs_context *const p_context, struct ecs_entity *const p_entity) {
    // ecs_context_print_table(p_context);

    if (!ecs_context_ensure_space(p_context, p_context->next_id))
        return ECS_STATUS_MALLOC;

    const size_t id = p_context->next_id;

    p_context->table.entities.array[p_context->next_id].id = id;
    p_context->table.components.darray[id] = NULL; // Setting it like this because the wild pointer already in-place COULD be valid! That's corrupting our stuff!
    p_context->table.counts.array[id] = 0;

    if (p_entity)
        p_entity->id = id;

    // We have reserved our space, dear threads in crime!:
    ++(p_context->next_id);
    ++(p_context->entry_count);
    // (Yeah, I know I'm telling them about it late...)

    return ECS_STATUS_OKAY;
}

enum ecs_status ecs_entity_destroy(struct ecs_context *const p_context, const struct ecs_entity p_entity) {
    size_t i = 0;

    // TODO Replace with map when that happens, else a cache-aware search!:
    for (; i < p_context->entry_count; ++i)
        if (p_context->table.entities.array[i].id == p_entity.id)
            break;

    // Remember - `entry_count` is itself out-of-bounds. It is the upper limit:
    // if (i == p_context->entry_count)
    //     return ECS_STATUS_INVALID_ENTITY;

    p_context->table.components.darray[i] = p_context->table.components.darray[p_context->entry_count - 1];
    p_context->table.counts.array[i] = p_context->table.counts.array[p_context->entry_count - 1];
    --(p_context->entry_count);
    // p_entity->id = 0;

    return ECS_STATUS_OKAY;
}
#pragma endregion
