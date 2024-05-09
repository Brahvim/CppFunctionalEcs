#pragma once

#include "EcsEnums.hpp"
#include "ComponentType.hpp"

namespace ecs {

    struct component {

        const struct component_type *type;

        // I very much hope, I very much pray,
        // May calls to this, be optimized away!
        explicit component(const struct component_type *type);

    };

}
