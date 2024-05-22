#pragma once

typedef void(component_destructor_t)(struct entity *entity, struct component *component);
typedef void(component_constructor_t)(struct entity *entity, struct component **storage);

struct component_type {

    component_destructor_t destructor;
    component_constructor_t constructor;

};
