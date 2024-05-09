#pragma once

#include <concepts>

#include "Component.hpp"
#include "EcsApiStatusEnums.hpp"

namespace ecs {

    struct entity; // Opaque type.

    enum ecs::entity_status destroy_entity(struct ecs::entity *entity);
    enum ecs::entity_status create_entity(struct ecs::entity **entity_storage);
    struct ecs::component* entity_get_component(struct ecs::entity const *p_entity);
    enum ecs::entity_status entity_attach_component(struct ecs::entity const *entity, struct ecs::component const *component);

}
