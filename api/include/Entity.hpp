#pragma once

#include <concepts>

#include "Component.hpp"
#include "EcsApiStatusEnums.hpp"

namespace ecs {

    using entity = size_t;

    enum ecs::entity_status destroy_entity(ecs::entity entity);
    enum ecs::entity_status create_entity(ecs::entity *entity_storage);
    struct ecs::component* entity_get_component(const ecs::entity entity, ecs::component_type *type);
    enum ecs::entity_status entity_attach_component(const ecs::entity entity, const struct ecs::component *component);

}
