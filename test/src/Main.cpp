#include <iostream>

#include "Entity.hpp"
#include "FloatingComponent.hpp"

int main() {
    ecs::entity_t e = ecs::create_entity();
    ecs::destroy_entity(e);

    ecs::components::floating::attach(e, 9);
    std::cout << ecs::components::floating::get(e);
    ecs::components::floating::detach(e);

    std::cout << ecs::get_num_entities();
}
