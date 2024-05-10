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

            extern const struct ecs::component_type position_component_type;

            struct position_component : public ecs::component {

                float x = 0;

                float y = 0;

                float z = 0;

                position_component() : component(&position_component_type) { }

            };

            enum ecs::components::position::status operator~(enum ecs::components::position::status value);
            enum ecs::components::position::status operator&(enum ecs::components::position::status lhs, enum ecs::components::position::status rhs);
            enum ecs::components::position::status operator|(enum ecs::components::position::status lhs, enum ecs::components::position::status rhs);

            size_t destroy(const ecs::entity entity);
            size_t create(const ecs::entity entity, struct ecs::component **storage);

        }

    }

}
