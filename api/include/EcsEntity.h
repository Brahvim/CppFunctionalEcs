#pragma once

#include <stddef.h>
#include <stdbool.h>

#include "EcsComponent.h"
#include "EcsComponentType.h"

#define ECS_NO_ERROR(x) !(x)
#define ECS_HAS_ERROR(x) (x)

// ...Still keeping the SoA structure:
struct ecs_context;

struct ecs_entity {

    size_t id;

};

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

// Utilities:
size_t ecs_trim(struct ecs_context *context);
void ecs_print_table(const struct ecs_context *context);
const char* const ecs_status_to_string(enum ecs_status status);
bool ecs_ensure_space(struct ecs_context *const context, size_t entity_count);

size_t ecs_entity_get_component_count(struct ecs_context *context, struct ecs_entity entity);

// Entity creation/destruction:
enum ecs_status ecs_entity_create(struct ecs_context *const context, struct ecs_entity *entity);
enum ecs_status ecs_entity_destroy(struct ecs_context *const context, struct ecs_entity *entity);

enum ecs_status ecs_entity_add_component(struct ecs_context *const context, struct ecs_component *component);
enum ecs_status ecs_entity_remove_component(struct ecs_context *const context, struct ecs_component *component);
