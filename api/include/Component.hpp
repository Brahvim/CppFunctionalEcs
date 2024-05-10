#pragma once

#include "ComponentType.hpp"

namespace ecs {

    // Okay - *this one* needs to be a `struct`, unlike `ecs::entity`, which turned into a `using`!

    struct component {

        const struct ecs::component_type *type;

        // I very much hope, I very much pray,
        // May calls to this, be optimized away!
        explicit component(const struct ecs::component_type *type);

    };

}
