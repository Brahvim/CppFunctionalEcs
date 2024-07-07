#pragma once

#include <stddef.h>
#include <stdbool.h>

#include "EcsComponent.h"
#include "EcsComponentType.h"

#define ECS_NO_ERROR(x) !(x)
#define ECS_HAS_ERROR(x) (x)

struct ecs_entity {

    size_t id;

};

size_t ecs_entity_get_component_count(struct ecs_context *context, struct ecs_entity entity);

// Entity creation/destruction:
enum ecs_status ecs_entity_create(struct ecs_context *const context, struct ecs_entity *const entity);
enum ecs_status ecs_entity_destroy(struct ecs_context *const context, const struct ecs_entity entity);

// enum ecs_status ecs_entity_add_component(struct ecs_context *const context, struct ecs_component *component);
// enum ecs_status ecs_entity_remove_component(struct ecs_context *const context, struct ecs_component *component);
