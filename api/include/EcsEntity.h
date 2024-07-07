#pragma once

#include <stddef.h>
#include <stdbool.h>

#include "EcsComponent.h"
#include "EcsComponentType.h"

// ...Still keeping the SoA structure:
struct ecs_context;

struct ecs_entity {

    size_t id;

};

enum ecs_status {

    ECS_STATUS_OKAY = 1,

    ECS_STATUS_MALLOC = 2,

    ECS_STATUS_ENTITY_MALLOC = 4,

    ECS_STATUS_INVALID_ENTITY = 8,

    ECS_STATUS_INVALID_CONTEXT = 16,

    ECS_STATUS_COMPONENT_MALLOC = 32,

    ECS_STATUS_INVALID_COMPONENT = 64,

    ECS_STATUS_COMPONENT_COUNT_MALLOC = 128,

};

// Context creation/destruction:
enum ecs_status ecs_create_context(struct ecs_context **context);
enum ecs_status ecs_destroy_context(struct ecs_context *context);

// Utilities:
size_t ecs_trim(struct ecs_context *context);
void ecs_print_table(const struct ecs_context *context);
const char* const ecs_status_to_string(enum ecs_status status);
bool ecs_ensure_space(struct ecs_context *const context, size_t entity_count);

size_t ecs_get_entity_component_count(struct ecs_context *context, struct ecs_entity entity);

// Entity creation/destruction:
enum ecs_status ecs_create_entity(struct ecs_context *const context, struct ecs_entity *entity);
enum ecs_status ecs_destroy_entity(struct ecs_context *const context, struct ecs_entity *entity);

enum ecs_status ecs_entity_add_component(struct ecs_context *const context, struct ecs_component *component);
enum ecs_status ecs_entity_remove_component(struct ecs_context *const context, struct ecs_component *component);
