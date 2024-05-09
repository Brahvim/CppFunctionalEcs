#pragma once

#include "Entity.hpp"
#include "Component.hpp"
#include "ComponentType.hpp"

namespace ecs {

    namespace components {

        namespace position {

            enum class status : size_t {

                OK = 0,

                MALLOC = 1,

                NULL_ENTITY = 2,

                NULL_COMPONENT = 4,

            };

            enum ecs::components::position::status operator~(enum ecs::components::position::status value);
            enum ecs::components::position::status operator&(enum ecs::components::position::status lhs, enum ecs::components::position::status rhs);
            enum ecs::components::position::status operator|(enum ecs::components::position::status lhs, enum ecs::components::position::status rhs);

            float get_x(const ecs::entity entity);
            size_t destroy(const ecs::entity entity);
            size_t create(const ecs::entity entity, struct ecs::component **storage);

        }

    }

}
