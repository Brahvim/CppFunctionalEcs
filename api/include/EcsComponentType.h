#pragma once

#include <stddef.h>

struct ecs_entity;
struct ecs_component;

typedef int ecs_component_status;

typedef void* (ecs_component_data_getter_t) (struct ecs_component *component);
typedef ecs_component_status(ecs_component_destructor_t)(struct ecs_entity entity, struct ecs_component *component);
typedef ecs_component_status(ecs_component_constructor_t)(struct ecs_entity entity, struct ecs_component **storage);

struct ecs_component_type {

    const size_t instance_limit;
    ecs_component_data_getter_t *getter;
    ecs_component_destructor_t *destructor;
    ecs_component_constructor_t *constructor;

};
