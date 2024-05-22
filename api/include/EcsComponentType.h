#pragma once

#include <stddef.h>

struct ecs_entity;
struct ecs_component;

typedef int ecs_component_status;

typedef ecs_component_status(component_destructor_t)(struct ecs_entity *entity, struct ecs_component component);
typedef ecs_component_status(component_constructor_t)(struct ecs_entity *entity, struct ecs_component *storage);

struct ecs_component_type {

    const size_t instance_limit;
    component_destructor_t *destructor;
    component_constructor_t *constructor;

};
