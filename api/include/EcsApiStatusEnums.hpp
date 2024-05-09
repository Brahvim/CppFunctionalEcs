#pragma once

#include <cstdlib>

namespace ecs {

#pragma region // Entities.
    enum class entity_status : size_t {

        OK = 0,

        MALLOC = 1,

        NULL_ENTITY = 2,

        NULL_COMPONENT = 4,

    };

    // `ecs::entity_status` operators:
    enum ecs::entity_status operator~(enum ecs::entity_status value);
    enum ecs::entity_status operator&(enum ecs::entity_status lhs, enum ecs::entity_status rhs);
    enum ecs::entity_status operator|(enum ecs::entity_status lhs, enum ecs::entity_status rhs);
#pragma endregion

}
