#pragma once
#include <bitset>
#include <cstddef>

namespace ecs {

    class entity;

    using destructor_cbck_t = void(*)(ecs::entity *p_destroyed);
    static inline const size_t component_flags_bits = 8;
    static inline const size_t component_flags_id_count = ecs::component_flags_bits / 2;
    static inline const size_t component_flags_group_count = ecs::component_flags_bits - ecs::component_flags_id_count;
    // typedef void(*destructor_cbck_t)(ecs::entity ecs_entity);
    // using destructor_cbck_t = void(*)(ecs::entity ecs_entity); // Memorize this, Brahvim! Memorize this!!1
    //
    // typedef void(*entity_limit_broken_cbck_t)();
    // static const ecs::entity max_entity_count = __SIZE_MAX__;

#pragma region // Memory management.
    ecs::entity* create_entity();
    void destroy_entity(ecs::entity *entity);
    // void set_entity_limit_broken_cbck(entity_limit_broken_cbck_t function);
#pragma endregion

    size_t get_num_entities();

#pragma region // Callback management.
    ecs::destructor_cbck_t detach_entity_destructor(ecs::entity *entity);
    void attach_entity_destructor(ecs::entity *entity, ecs::destructor_cbck_t destructor);
#pragma endregion

}
