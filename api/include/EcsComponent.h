#pragma once

#include <stddef.h>

#include "EcsComponentType.h"

struct ecs_component {

    size_t id;
    struct ecs_component_type *type;

};

struct ecs_components_table {

    size_t num_components;
    struct ecs_component *components;
    struct ecs_entity *parent_enitities;
    struct ecs_component_type *component_type;

};
