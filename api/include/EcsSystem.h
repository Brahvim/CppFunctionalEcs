#pragma once

#include <stddef.h>

struct ecs_system;
struct ecs_systems_round;
struct ecs_component_type;
struct ecs_systems_pipeline;

typedef void(ecs_system_update_t)(void);

struct ecs_system {

    ecs_system_update_t *update;
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
void run_round(struct ecs_systems_round *round);

// Runs `ecs_systems_pipeline::rounds::update`s in serial order:
void run_pipeline(struct ecs_systems_pipeline *pipeline);
