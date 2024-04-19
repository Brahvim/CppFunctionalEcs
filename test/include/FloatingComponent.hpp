#pragma once
#include "Entity.hpp"

namespace ecs {
    namespace components {
        namespace floating {

            // using ecs_component_floating_t = size_t;
            // static const ecs::components::floating::ecs_component_floating_t null = 0;

#pragma region // Memory management.
            void attach(ecs::entity_t entity);
            void detach(ecs::entity_t entity);
            void attach(ecs::entity_t entity, float value);
#pragma endregion

#pragma region // Getting and setting!...
            float get(ecs::entity_t entity);
            void set(ecs::entity_t entity, float value);
#pragma endregion

        }
    }
}
