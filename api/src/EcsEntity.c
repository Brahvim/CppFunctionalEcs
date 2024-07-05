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
    to_ret->length = ECS_INITIAL_ENTITY_CAPACITY;
    to_ret->table.capacity = ECS_INITIAL_ENTITY_CAPACITY;
    to_ret->table.ids = calloc(ECS_INITIAL_ENTITY_CAPACITY, sizeof(struct ecs_entity));
    to_ret->table.components = calloc(ECS_INITIAL_ENTITY_CAPACITY, sizeof(struct ecs_component*));

    // Checks:
    if (!to_ret->table.ids) {
        *p_instance = to_ret;
        return ECS_STATUS_ID_MALLOC;
    }

    if (!to_ret->table.components) {
        *p_instance = to_ret;
        return ECS_STATUS_COMPONENTS_MALLOC;
    }

    *p_instance = to_ret;
    return ECS_STATUS_OKAY;
}

enum ecs_status ecs_destroy(struct ecs_instance *p_instance) {
    if (!p_instance)
        return ECS_STATUS_INVALID_INSTANCE;

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
    }
}
#pragma endregion
