#pragma once

#include "EcsComponent.h"

struct position_component {

    float x;

    float y;

    float z;

};

enum position_component_status {

    POSITION_COMPONENT_STATUS_OKAY = 1,

    POSITION_COMPONENT_STATUS_MALLOC = 2,

};

extern const struct ecs_component_type position_component_type;

size_t position_component_count();
struct ecs_entity* position_component_parents();

struct position_component* position_component_get_data(struct ecs_component *component);
ecs_component_status position_component_create(struct ecs_entity entity, struct ecs_component **storage);
ecs_component_status position_component_destroy(struct ecs_entity entity, struct ecs_component *component);

ecs_component_status position_component_add(struct ecs_component to, struct ecs_component from);
ecs_component_status position_component_dist(struct ecs_component to, struct ecs_component from);
ecs_component_status position_component_dist_sq(struct ecs_component to, struct ecs_component from);
