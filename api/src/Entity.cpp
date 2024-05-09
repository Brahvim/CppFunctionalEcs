#include <memory>
#include <cstdlib>

#include "Entity.hpp"
#include "EcsEnums.hpp"

namespace ecs {

    struct entity final {

        size_t id;

    };

    static size_t s_num_entities;
    static struct ecs::entity *s_entities;
    static struct ecs::entity **s_free_entities;

    static size_t s_num_entity_allocations;
    static size_t *s_entity_component_counts;
    static struct component **s_entity_component_pointers_list;

    // ...Whatever:
    enum ecs::entity_status create_entity(struct ecs::entity **p_entity_storage) {
        try {
            *p_entity_storage = new struct ecs::entity;
        } catch (std::bad_alloc&) {
            return ecs::entity_status::MALLOC;
        }

        return ecs::entity_status::OK;
    }

    enum ecs::entity_status destroy_entity(struct ecs::entity *p_entity) {
        delete p_entity;
        return ecs::entity_status::OK;
    }

    struct ecs::component* entity_get_component(struct ecs::entity const *p_entity) {
        struct ecs::component *component = nullptr;
        const size_t max = s_entity_component_counts[p_entity->id];

        for (size_t i = 0; i < max; ++i)
            if ((component = s_entity_component_pointers_list[i]))
                break;

        return component;
    }

    // Could this use a base type...? No `virtual`s though, please.
    enum ecs::entity_status entity_attach_component(struct ecs::entity *p_entity, struct component *p_component) {
        if (!(p_entity && p_component))
            return ecs::entity_status::NULL_ENTITY & ecs::entity_status::NULL_COMPONENT;

        // entity->components += p_component; // Add it there.
        return ecs::entity_status::OK;
    };

}
