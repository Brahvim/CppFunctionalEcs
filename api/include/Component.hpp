#pragma once

#include "ComponentType.hpp"
#include "EcsApiStatusEnums.hpp"

namespace ecs {

    struct component {

        const struct ecs::component_type *type;

        // I very much hope, I very much pray,
        // May calls to this, be optimized away!
        explicit component(const struct ecs::component_type *type);

    };

}
