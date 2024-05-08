#pragma once

#include "Entity.hpp"
#include "Component.hpp"
#include "ComponentType.hpp"

namespace ecs {

    namespace components {

        namespace position {

            float get_x(struct entity* entity);
            enum component_status create(struct entity *entity, struct component **storage);

        }

    }

}
