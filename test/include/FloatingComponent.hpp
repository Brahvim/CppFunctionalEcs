#pragma once

#include "Entity.hpp"

namespace ecs {
    namespace components {
        namespace floating {

#pragma region // Memory management.
            void attach(ecs::entity *ecs_entity);
            void detach(ecs::entity *ecs_entity);
            void attach(ecs::entity *ecs_entity, float value);
#pragma endregion

#pragma region // Getting and setting!...
            float get(ecs::entity *ecs_entity);
            void set(ecs::entity *ecs_entity, float value);
            void update(ecs::entity *ecs_entity, float value);
#pragma endregion

        }
    }
}
