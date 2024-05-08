#include <iostream>

#include "Entity.hpp"
#include "PositionComponent.hpp"

int main() {
    ecs::entity *e = nullptr;
    ecs::create_entity(&e);

    ecs::component *position = nullptr;
    ecs::components::position::create(e, &position);
    ecs::entity_attach_component(e, position);
}
