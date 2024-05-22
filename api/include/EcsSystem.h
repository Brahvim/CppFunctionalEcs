#pragma once

#include <stddef.h>

struct ecs_component_array;

typedef void(system_update_t)(struct ecs_component_array *components);

struct ecs_system {

    system_update_t *update;
    struct ecs_component_type *component_type;

};

struct ecs_systems_round {

    size_t num_systems;
    struct ecs_system *systems;

};

struct ecs_systems_pipeline {

    size_t num_rounds;
    struct ecs_systems_round *rounds;

};

// Assuming both `struct`'s `num_*` values are equal, this runs a round of `ecs_system::update`s in parallel:
void run_round(struct ecs_systems_round *round, struct ecs_component_array *component_arrays);

// Runs `ecs_systems_pipeline::rounds::update`s in serial order, given all component data:
void run_pipeline(struct ecs_systems_pipeline *pipeline, struct ecs_component_array **components);
