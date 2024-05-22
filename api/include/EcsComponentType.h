#pragma once

#include <stddef.h>

typedef void(component_destructor_t)(struct ecs_entity *entity, struct ecs_component *component);
typedef void(component_constructor_t)(struct ecs_entity *entity, struct ecs_component **storage);

struct ecs_component_type {

    const size_t instance_limit;
    component_destructor_t destructor;
    component_constructor_t constructor;

};
