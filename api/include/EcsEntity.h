#pragma once

#include <stddef.h>
#include <stdbool.h>

#include "EcsComponent.h"
#include "EcsComponentType.h"

struct ecs_entities_table {

    size_t capacity;
    struct ecs_entity *ids;
    size_t *component_counts;
    struct ecs_component **components;

};

struct ecs_instance {

    size_t length;
    struct ecs_entities_table table;

};

struct ecs_entity {

    size_t id;

};

enum ecs_status {

    ECS_STATUS_OKAY = 1,

    ECS_STATUS_MALLOC = 2,

    ECS_STATUS_ID_MALLOC = 4,

    ECS_STATUS_INVALID_ENTITY = 8,

    ECS_STATUS_INVALID_INSTANCE = 16,

    ECS_STATUS_COMPONENTS_MALLOC = 32,

    ECS_STATUS_INVALID_COMPONENT = 64,

    ECS_STATUS_COMPONENT_COUNTS_MALLOC = 128,

};

enum ecs_status ecs_create(struct ecs_instance** instance);
enum ecs_status ecs_destroy(struct ecs_instance* instance);

const char* const ecs_status_to_string(enum ecs_status status);
