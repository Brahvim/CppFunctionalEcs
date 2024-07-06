#include "EcsEntity.h"
#include "PositionComponent.h"

const struct ecs_component_type position_component_type = {

    .instances_per_entity = __SIZE_MAX__,
    .destructor = position_component_destroy,
    .constructor = position_component_create,

};

static struct ecs_components_table s_components;

ecs_component_status position_component_create(struct ecs_entity entity, struct ecs_component **storage) {
    return POSITION_COMPONENT_STATUS_OKAY;
}

ecs_component_status position_component_destroy(struct ecs_entity entity, struct ecs_component *component) {
    return POSITION_COMPONENT_STATUS_OKAY;
}
