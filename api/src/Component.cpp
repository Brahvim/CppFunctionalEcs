#include "Component.hpp"

namespace ecs {

    ecs::component::component(const struct component_type *p_type) : type(p_type) { }

    enum ecs::component_status operator~(enum ecs::component_status value) {
        return static_cast<enum ecs::component_status>(~static_cast<size_t>(value));
    }

    enum ecs::component_status operator&(enum ecs::component_status lhs, enum ecs::component_status rhs) {
        return static_cast<enum ecs::component_status>(static_cast<size_t>(lhs) & static_cast<size_t>(rhs));
    }

    enum ecs::component_status operator|(enum ecs::component_status lhs, enum ecs::component_status rhs) {
        return static_cast<enum ecs::component_status>(static_cast<size_t>(lhs) | static_cast<size_t>(rhs));
    }

}
