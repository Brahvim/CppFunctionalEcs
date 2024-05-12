#pragma once

#include <concepts>

#include "Component.hpp"

namespace ecs {

    using entity = size_t;

    enum class entity_error : char {

        NONE = 0,

        MALLOC = 1,

        INVALID_ENTITY = 2,

        INVALID_COMPONENT = 4,

    };

    // `ecs::entity_error` operators:
    enum ecs::entity_error operator~(enum ecs::entity_error value);
    enum ecs::entity_error operator&(enum ecs::entity_error lhs, enum ecs::entity_error rhs);
    enum ecs::entity_error operator|(enum ecs::entity_error lhs, enum ecs::entity_error rhs);

    // Statistical queries:
    size_t get_entity_count();
    size_t get_free_entities_count();
    size_t get_entity_allocations_count();

    // Allocation queries:
    bool is_valid(const ecs::entity entity);
    enum ecs::entity_error destroy_entity(const ecs::entity entity);
    enum ecs::entity_error create_entity(ecs::entity *entity_storage);
    enum ecs::entity_error ensure_allocations_for(const size_t entity_count);

    // Getters and setters:
    struct ecs::component* entity_get_component(const ecs::entity entity, const ecs::component_type *type);
    enum ecs::entity_error entity_attach_component(const ecs::entity entity, const struct ecs::component *component);
    enum ecs::entity_error entity_detach_component(const ecs::entity entity, const struct ecs::component_type *component_type);

}
