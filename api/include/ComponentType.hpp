#pragma once

#include "EcsApiStatusEnums.hpp"

namespace ecs {

    struct component;
    using entity = size_t;

    using component_update_function_t = size_t(*)();
    using component_destruction_function_t = size_t(*)(const ecs::entity entity);
    // using component_creation_function = size_t(*)(const ecs::entity entity, struct ecs::component *component_storage);

    struct component_type final {

        // ecs::component_update_function_t update_function;
        // ecs::component_creation_function_t creation_function;
        ecs::component_destruction_function_t destruction_function;

    };

}
