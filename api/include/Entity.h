#pragma once

#include <stddef.h>

#include "Component.h"
#include "ComponentType.h"

enum entity_status {

    ENTITY_STATUS_MALLOC,

    ENTITY_STATUS_INVALID_ENTITY,

    ENTITY_STATUS_INVALID_COMPONENT,

};

struct entity {

    size_t offset;

};

size_t entity_get_count();
// size_t entity_get_allocations_count();
// No `size_t entity_get_free_count()` here; free lists should remain an implementation detail.

bool entity_is_valid();
enum entity_status entity_ensure_allocations_for(size_t count);

enum entity_status entity_destroy(struct entity entity);
enum entity_status entity_create(struct entity *storage);

// Getters and setters:
size_t entity_get_component_type_count(const struct entity entity, const component_type *type);
struct component* entity_get_components(const struct entity entity, const component_type *type);
enum entity_status entity_attach_component(const struct entity entity, const struct component *component);
enum entity_status entity_detach_component(const struct entity entity, const struct component_type *component_type);
