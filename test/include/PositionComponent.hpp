#pragma once

#include "Entity.hpp"
#include "Component.hpp"
#include "ComponentType.hpp"

namespace ecs {

    namespace components {

        namespace position {

            enum class status : char {

                NONE = 0,

                MALLOC = 1,

                INVALID_ENTITY = 2,

                INVALID_COMPONENT = 4,

            };

            extern const struct ecs::component_type position_component_type;

            struct position_component {

                float x = 0;

                float y = 0;

                float z = 0;

            };

            enum ecs::components::position::status operator~(enum ecs::components::position::status value);
            enum ecs::components::position::status operator&(enum ecs::components::position::status lhs, enum ecs::components::position::status rhs);
            enum ecs::components::position::status operator|(enum ecs::components::position::status lhs, enum ecs::components::position::status rhs);

            size_t destroy(const struct ecs::entity entity);
            size_t create(const struct ecs::entity entity, struct ecs::component **storage);

        }

    }

}
