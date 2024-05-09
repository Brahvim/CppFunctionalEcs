#pragma once

#include <concepts>

#include "EcsEnums.hpp"
#include "Component.hpp"

namespace ecs {

    struct entity;

    enum entity_status destroy_entity(struct entity *entity);
    enum entity_status create_entity(struct entity **entity_storage);
    enum entity_status entity_attach_component(struct entity *entity, struct component *component_handle);

    template<class component_t>
        requires std::derived_from<component_t, ecs::component>
    component_t* entity_get_component(struct entity *entity);

}
