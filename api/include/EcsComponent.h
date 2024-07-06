#pragma once

#include <stddef.h>

#include "EcsComponentType.h"

struct ecs_component {

    size_t id;
    struct ecs_component_type *type;

};

struct ecs_parents_array {

    size_t capacity;
    struct ecs_entity *array;

};

struct ecs_component_array {

    size_t capacity;
    struct ecs_component *array;

};

// Component programmers would keep a `static struct my_component_data s_component_data` variable around.

struct ecs_components_table {

    size_t entry_count;
    struct ecs_parents_array parents;
    struct ecs_component_array handles;

};
