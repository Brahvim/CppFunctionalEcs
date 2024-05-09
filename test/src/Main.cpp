#include <iostream>

#include "Entity.hpp"
#include "PositionComponent.hpp"

int main() {
    ecs::entity e = 0;
    ecs::create_entity(&e);

    ecs::component *position = nullptr;
    ecs::components::position::create(e, &position);
    ecs::entity_attach_component(e, position);
}
