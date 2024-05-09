#pragma once

#include "EcsEnums.hpp"

namespace ecs {

    struct component_type final {

        // using component_creation_function = enum component_status(*)(struct entity *entity, struct component **component_id_storage);
        using component_destruction_function = enum component_status(*)(struct entity *entity);

        // ecs::component_type::component_creation_function creation_function;
        ecs::component_type::component_destruction_function destruction_function;


    };

}
