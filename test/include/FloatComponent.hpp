#pragma once
#include "Entity.hpp"

#ifdef _ECS_MACROS_H_
#define ECS_COMPONENT_FLOATING floating
#endif

namespace ecs {
    namespace components {
        namespace floating {

            using ecs_component_floating_t = size_t;
            static inline const ecs::components::floating::ecs_component_floating_t null = 0;

#pragma region // Memory management.
            void create(ecs::entity_t entity);
            void destroy(ecs::entity_t entity);
#pragma endregion

#pragma region // Getting and setting!...
            void set(ecs::entity_t entity);
            float get(ecs::entity_t entity);
#pragma endregion

        }
    }
}
