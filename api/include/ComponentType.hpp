#pragma once

#include "EcsEnums.hpp"

namespace ecs {

    struct component_type {

        using component_destruction_function = enum component_status(*)(struct entity *entity);
        using component_creation_function = enum component_status(*)(struct entity *entity, struct component **component_id_storage);

        ecs::component_type::component_creation_function creation_function;
        ecs::component_type::component_destruction_function destruction_function;

    };

}
