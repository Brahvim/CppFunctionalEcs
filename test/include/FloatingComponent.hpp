#pragma once
#include "Entity.hpp"

namespace ecs {
    namespace components {
        namespace floating {

#pragma region // Memory management.
            void attach(ecs::ecs_entity ecs_entity);
            void detach(ecs::ecs_entity ecs_entity);
            void attach(ecs::ecs_entity ecs_entity, float value);
#pragma endregion

#pragma region // Getting and setting!...
            float get(ecs::ecs_entity ecs_entity);
            void set(ecs::ecs_entity ecs_entity, float value);
            void update(ecs::ecs_entity ecs_entity, float value);
#pragma endregion

        }
    }
}
