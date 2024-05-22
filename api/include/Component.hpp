#pragma once

#include "ComponentType.hpp"

namespace ecs {

    struct component {

        size_t offset;
        struct component_type *type;

        explicit component(struct ecs::component_type *type);

    };

}
