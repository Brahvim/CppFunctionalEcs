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

    enum entity_status operator~(enum entity_status value);
    enum entity_status operator&(enum entity_status lhs, enum entity_status rhs);
    enum entity_status operator|(enum entity_status lhs, enum entity_status rhs);

    enum component_status operator~(enum component_status value);
    enum component_status operator&(enum component_status lhs, enum component_status rhs);
    enum component_status operator|(enum component_status lhs, enum component_status rhs);

}
