#include <iostream>

#include "Entity.hpp"
#include "FloatingComponent.hpp"

int main() {
    ecs::entity_t e = ecs::create_entity();
    std::cout << "Number of entities: `" << ecs::get_num_entities() << "`." << std::endl;

    ecs::components::floating::attach(e, 9);
    std::cout << ecs::components::floating::get(e) << std::endl;

    ecs::components::floating::update(e, 1);

    std::cout << ecs::components::floating::get(e) << std::endl;
    ecs::components::floating::detach(e);

    ecs::destroy_entity(e);
    std::cout << "Number of entities: `" << ecs::get_num_entities() << "`." << std::endl;
}
