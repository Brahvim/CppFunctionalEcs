#pragma once
#include "Entity.hpp"

namespace ecs {
    namespace components {
        namespace floating {

#pragma region // Memory management.
            void attach(ecs::entity_t entity);
            void detach(ecs::entity_t entity);
            void attach(ecs::entity_t entity, float value);
#pragma endregion

#pragma region // Getting and setting!...
            float get(ecs::entity_t entity);
            void set(ecs::entity_t entity, float value);
            void update(ecs::entity_t entity, float value);
#pragma endregion

        }
    }
}
