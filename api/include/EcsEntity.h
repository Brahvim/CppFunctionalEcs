#pragma once

#include <stddef.h>
#include <stdbool.h>

#include "EcsComponent.h"
#include "EcsComponentType.h"

enum entity_status {

    ENTITY_STATUS_OKAY = 1,

    ENTITY_STATUS_MALLOC = 2,

    ENTITY_STATUS_INVALID_ENTITY = 4,

    ENTITY_STATUS_INVALID_COMPONENT = 8,

};

struct ecs_entity {

    size_t offset;

};

size_t entity_get_count();
// size_t entity_get_allocations_count();
// No `size_t entity_get_free_count()` here; free lists should remain an implementation detail.

bool entity_is_valid();
enum entity_status entity_ensure_allocations_for(size_t count);

enum entity_status entity_destroy(struct ecs_entity entity);
enum entity_status entity_create(struct ecs_entity *storage);

// Getters and setters:
size_t entity_get_component_type_count(const struct ecs_entity entity, const struct ecs_component_type *type);
struct ecs_component* entity_get_components(const struct ecs_entity entity, const struct ecs_component_type *type);
enum entity_status entity_attach_component(const struct ecs_entity entity, const struct ecs_component *component);
enum entity_status entity_detach_component(const struct ecs_entity entity, const struct ecs_component_type *component_type);
