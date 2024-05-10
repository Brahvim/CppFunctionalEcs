#include <memory>
#include <cstdlib>

#include "Entity.hpp"

namespace ecs {

#pragma region // `ecs::entity_status` operators.
    enum ecs::entity_status operator~(enum ecs::entity_status p_value) {
        return static_cast<enum ecs::entity_status>(~static_cast<size_t>(p_value));
    }

    enum ecs::entity_status operator&(enum ecs::entity_status p_lhs, enum ecs::entity_status p_rhs) {
        return static_cast<enum ecs::entity_status>(static_cast<size_t>(p_lhs) & static_cast<size_t>(p_rhs));
    }

    enum ecs::entity_status operator|(enum ecs::entity_status p_lhs, enum ecs::entity_status p_rhs) {
        return static_cast<enum ecs::entity_status>(static_cast<size_t>(p_lhs) | static_cast<size_t>(p_rhs));
    }
#pragma endregion

#pragma region // Entity data arrays.
    static size_t s_num_entities;
    static ecs::entity *s_entities;
    static ecs::entity **s_free_entities;

    static size_t s_num_entity_allocations;
    static size_t *s_entity_component_counts;
    static struct ecs::component **s_entity_component_pointers_list;
#pragma endregion

    // ...Whatever:
    enum ecs::entity_status destroy_entity(ecs::entity) {
        return ecs::entity_status::OK;
    }

    enum ecs::entity_status create_entity(ecs::entity *p_storage) {
        try {
            *p_storage = 0ULL;
        } catch (std::bad_alloc&) {
            return ecs::entity_status::MALLOC;
        }

        return ecs::entity_status::OK;
    }

    struct ecs::component* entity_get_component(const ecs::entity p_entity, const ecs::component_type *p_type) {
        struct ecs::component *component = nullptr;
        const size_t max = s_entity_component_counts[p_entity];

        for (size_t i = 0; i < max; ++i)
            if ((component = s_entity_component_pointers_list[i])->type == p_type)
                break;

        return component;
    }

    // Could this use a base type...? No `virtual`s though, please.
    enum ecs::entity_status entity_attach_component(const ecs::entity p_entity, const struct ecs::component *p_component) {
        if (!(p_entity && p_component))
            return ecs::entity_status::NULL_ENTITY & ecs::entity_status::NULL_COMPONENT;

        // entity->components += p_component; // Add it there.
        return ecs::entity_status::OK;
    };

}
