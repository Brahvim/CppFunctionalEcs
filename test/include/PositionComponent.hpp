#pragma once

#include "Entity.hpp"
#include "Component.hpp"
#include "ComponentType.hpp"

namespace ecs {

    namespace components {

        namespace position {

            float get_x(const struct ecs::entity *entity);
            enum ecs::component_status create(const struct ecs::entity *entity, struct ecs::component **storage);

        }

    }

}
