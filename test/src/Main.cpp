#include <iostream>

#include "Entity.hpp"
#include "PositionComponent.hpp"

int main() {
    struct ecs::entity e;
    const enum ecs::entity_error e_err = ecs::create_entity(&e);

    ecs::component *position = nullptr;
    const auto c_err = static_cast<const enum ecs::components::position::status>(ecs::components::position::create(e, &position));
    ecs::entity_attach_component(e, position);
}
