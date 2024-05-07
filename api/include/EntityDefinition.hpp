#pragma once

#include "Entity.hpp"

namespace ecs {
    class entity {
    public:

#pragma region // Fields.
        ecs::destructor_cbck_t destructor_callback;
        std::bitset<ecs::component_flags_bits> component_flags;
#pragma endregion

        friend ecs::entity* ecs::create_entity();
        friend void ecs::destroy_entity(ecs::entity *entity);
        friend ecs::destructor_cbck_t ecs::detach_entity_destructor(ecs::entity *entity);
        friend void ecs::attach_entity_destructor(ecs::entity *entity, ecs::destructor_cbck_t destructor);

    };
}
