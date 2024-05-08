#include "EcsEnums.hpp"

namespace ecs {

    enum entity_status operator~(enum entity_status value) {
        return static_cast<enum entity_status>(~static_cast<size_t>(value));
    }

    enum entity_status operator&(enum entity_status lhs, enum entity_status rhs) {
        return static_cast<enum entity_status>(static_cast<size_t>(lhs) & static_cast<size_t>(rhs));
    }

    enum entity_status operator|(enum entity_status lhs, enum entity_status rhs) {
        return static_cast<enum entity_status>(static_cast<size_t>(lhs) | static_cast<size_t>(rhs));
    }

    enum component_status operator~(enum component_status value) {
        return static_cast<enum component_status>(~static_cast<size_t>(value));
    }

    enum component_status operator&(enum component_status lhs, enum component_status rhs) {
        return static_cast<enum component_status>(static_cast<size_t>(lhs) & static_cast<size_t>(rhs));
    }

    enum component_status operator|(enum component_status lhs, enum component_status rhs) {
        return static_cast<enum component_status>(static_cast<size_t>(lhs) | static_cast<size_t>(rhs));
    }

}
