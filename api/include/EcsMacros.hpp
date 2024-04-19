#ifndef _ECS_MACROS_H_
#define _ECS_MACROS_H_ 1

#define ECS_COMPONENT_CREATE(p_entity, p_component_type) ecs::components::p_component_type::create(p_entity)

#endif