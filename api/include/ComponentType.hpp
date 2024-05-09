#pragma once

#include "EcsApiStatusEnums.hpp"

namespace ecs {

    struct entity;
    struct component;

    // using component_creation_function = enum ecs::component_status(*)(const struct ecs::entity *entity, struct ecs::component **component_id_storage);
    using component_destruction_function_t = enum ecs::component_status(*)(const struct ecs::entity *entity);

    struct component_type final {

        // ecs::component_creation_function creation_function;

        ecs::component_destruction_function_t destruction_function;


    };

}
