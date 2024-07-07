#pragma once

#include <stddef.h>
#include <stdbool.h>

enum ecs_status {

    ECS_STATUS_OKAY = 0,

    ECS_STATUS_MALLOC = 1,

    ECS_STATUS_ENTITY_MALLOC = 2,

    ECS_STATUS_INVALID_ENTITY = 4,

    ECS_STATUS_INVALID_CONTEXT = 8,

    ECS_STATUS_COMPONENT_MALLOC = 16,

    ECS_STATUS_INVALID_COMPONENT = 32,

    ECS_STATUS_COMPONENT_COUNT_MALLOC = 64,

};

// Context creation/destruction:
enum ecs_status ecs_context_create(struct ecs_context **context);
enum ecs_status ecs_context_destroy(struct ecs_context *context);

// Allocation statistics:
size_t ecs_context_trim(struct ecs_context *context);
bool ecs_context_ensure_space(struct ecs_context *const context, const size_t entity_count);

// Utilities:
void ecs_context_print_table(const struct ecs_context *context);
const char* const ecs_context_status_to_string(enum ecs_status status);
size_t ecs_context_entity_count(const struct ecs_context *const context);
