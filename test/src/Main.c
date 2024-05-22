#include "Ecs.h"
#include "PositionComponent.h"

int main() {

    struct ecs_entity e;
    const enum entity_status e_init_err = entity_create(&e);

    struct ecs_component *c;
    const enum entity_status c_init_err = position_component_create(e, &c);

    // `((struct position_component*) c->type->getter(c))->x = 4;`
    struct position_component *const data = position_component_get_data(c);
    data->x = 4;
    data->y = 5;
    data->z = 6;

}
