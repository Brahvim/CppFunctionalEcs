#include <cstdlib>

#include "Entity.hpp"
#include "EcsEnums.hpp"

namespace ecs {

    struct entity final {

        size_t id;

    };

    static size_t s_num_entities;
    static struct entity *s_entities;
    static struct entity **s_free_entities;

    static size_t s_num_entity_allocations;
    static size_t *s_entity_component_counts;
    static struct component **s_entity_component_pointers_list;

    // ...Whatever:
    enum entity_status create_entity(struct entity** p_entity_storage) {
        return ecs::entity_status::OK;
    }

    enum entity_status destroy_entity(struct entity* p_entity) {
        return ecs::entity_status::OK;
    }

    // Could this use a base type...? No `virtual`s though, please.
    enum entity_status entity_attach_component(struct entity *p_entity, struct component *p_component) {

        if (!(p_entity && p_component))
            return entity_status::NULL_ENTITY & entity_status::NULL_COMPONENT;

        // entity->components += p_component; // Add it there.
        return ecs::entity_status::OK;
    };

    template<class component_t>
        requires std::derived_from<component_t, ecs::component>
    component_t* entity_get_component(struct entity const *p_entity) {
        component_t *component = nullptr;
        const size_t max = s_entity_component_counts[p_entity->id];

        for (size_t i = 0; i < max; ++i)
            if ((component = static_cast<component_t*>(&s_entity_component_pointers_list[i])))
                break;

        return component;
    }

}
