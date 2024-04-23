#pragma once
#include "Entity.hpp"

namespace ecs {
    namespace components {
        namespace floating {

#pragma region // Memory management.
            void attach(ecs::entity entity);
            void detach(ecs::entity entity);
            void attach(ecs::entity entity, float value);
#pragma endregion

#pragma region // Getting and setting!...
            float get(ecs::entity entity);
            void set(ecs::entity entity, float value);
            void update(ecs::entity entity, float value);
#pragma endregion

        }
    }
}
