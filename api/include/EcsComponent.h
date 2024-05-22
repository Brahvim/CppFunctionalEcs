#pragma once

#include <stddef.h>

#include "EcsComponentType.h"

struct ecs_component {

    size_t offset;
    struct ecs_component_type *type;

};

struct ecs_component_array {

    size_t num_components;
    struct ecs_component *components;
    struct ecs_component_type *component_type;

};
