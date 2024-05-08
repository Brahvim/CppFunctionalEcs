#include <cstdlib>

#include "Entity.hpp"
#include "EcsEnums.hpp"

namespace ecs {

    struct entity {

        size_t num_components;
        struct component *components;

    };

    static size_t s_num_entities;
    static struct entity *s_entities;
    static struct entity *s_free_entities;
    static size_t s_num_entity_allocations;

    // ...Whatever:
    enum entity_status create_entity(struct entity**) {
        return ecs::entity_status::OK;
    }

    enum entity_status destroy_entity(struct entity* entity) {
        return ecs::entity_status::OK;
    }

    // Could this use a base type...? No `virtual`s though, please.
    enum entity_status entity_attach_component(struct entity *entity, struct component *component_handle) {

        if (!(entity && component_handle))
            return entity_status::NULL_ENTITY & entity_status::NULL_COMPONENT;

        // entity->components += component_handle; // Add it there.
        return ecs::entity_status::OK;
    };

    template<class component_t>
        requires std::derived_from<component_t, ecs::component>
    component_t* entity_get_component(struct entity* entity) {
        component_t* component = nullptr;
        const size_t max = entity->num_components;

        for (size_t i = 0; i < max; ++i) {
            component = static_cast<component_t*>(&entity->components[i]);
            if (component)
                break;
        }

        return component;
    }

}
