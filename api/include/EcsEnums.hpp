#include <cstdlib>

#pragma once

namespace ecs {

    enum class entity_status : size_t {

        OK = 0,

        MALLOC = 1,

        NULL_ENTITY = 2,

        NULL_COMPONENT = 4,

    };

    enum class component_status : size_t {

        OK = 0,

        MALLOC = 1,

        NULL_ENTITY = 2,

        NULL_COMPONENT = 4,

    };

    enum ecs::entity_status operator~(enum ecs::entity_status value);
    enum ecs::entity_status operator&(enum ecs::entity_status lhs, enum ecs::entity_status rhs);
    enum ecs::entity_status operator|(enum ecs::entity_status lhs, enum ecs::entity_status rhs);

    enum ecs::component_status operator~(enum ecs::component_status value);
    enum ecs::component_status operator&(enum ecs::component_status lhs, enum ecs::component_status rhs);
    enum ecs::component_status operator|(enum ecs::component_status lhs, enum ecs::component_status rhs);

}
