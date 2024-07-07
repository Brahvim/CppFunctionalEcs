#pragma once

#include <stddef.h>

struct ecs_entity;
struct ecs_context;
struct ecs_component;

typedef int ecs_component_status; // `enum`s are `int`s for at least GCC.

typedef ecs_component_status(ecs_component_detacher_t)(struct ecs_component *const component);
typedef const char *const(ecs_component_status_to_string_t) (ecs_component_status status);
typedef ecs_component_status(ecs_component_parent_getter_t)(const struct ecs_component *const component, struct ecs_entity *const storage);
typedef ecs_component_status(ecs_component_attacher_t)(struct ecs_context *const context, struct ecs_entity entity, struct ecs_component *const storage);

struct ecs_component_type {

    const size_t instances_per_entity;
    ecs_component_attacher_t *attacher;
    ecs_component_detacher_t *detacher;
    ecs_component_parent_getter_t *parent_getter;
    ecs_component_status_to_string_t *error_to_string;

};
