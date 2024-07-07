#include "Ecs.h"
#include "PositionComponent.h"

struct position_component_positions_array {

    size_t capacity;
    float *array; // One 64-bit cache-line can fit 16 `float`s - nearly `5.3` positions - 5 complete 3D vectors, plus one's `x`.

};

struct position_component_table {

    struct ecs_components_table ecs_table;
    struct position_component_positions_array positions;

};

const struct ecs_component_type position_component_type = {

    .instances_per_entity = __SIZE_MAX__,
    .detacher = position_component_detach,
    .attacher = position_component_attach,

};

static struct position_component_table s_component_data = {

    .ecs_table.entry_count = 0,
    .ecs_table.handles = {.array = NULL, .capacity = 0},
    .ecs_table.parents = {.array = NULL, .capacity = 0},

    .positions = {.array = NULL, .capacity = 0},

};

ecs_component_status position_component_attach(struct ecs_context *const context, struct ecs_entity entity, struct ecs_component *const storage) {
    return POSITION_COMPONENT_STATUS_OKAY;
}

ecs_component_status position_component_detach(struct ecs_component *component) {
    return POSITION_COMPONENT_STATUS_OKAY;
}
