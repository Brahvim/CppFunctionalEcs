#pragma once

#include <concepts>

#include "Component.hpp"
#include "EcsApiStatusEnums.hpp"

namespace ecs {

    using entity = size_t;

    // Numeric, statistical queries:
    size_t get_num_entities();
    size_t get_num_free_entities();

    // Allocation queries:
    enum ecs::entity_status destroy_entity(const ecs::entity entity);
    enum ecs::entity_status create_entity(ecs::entity *entity_storage);
    enum ecs::entity_status ensure_allocations_for(size_t entity_count);

    // Getters and setters:
    struct ecs::component* entity_get_component(const ecs::entity entity, const ecs::component_type *type);
    enum ecs::entity_status entity_attach_component(const ecs::entity entity, const struct ecs::component *component);
    enum ecs::entity_status entity_detach_component(const ecs::entity entity, const struct ecs::component *component);

}
