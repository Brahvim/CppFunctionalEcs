#pragma once
#include <cstddef>

namespace ecs {

    using entity_t = size_t;
    typedef void(*destructor_cbck_t)(ecs::entity_t entity);
    // typedef void(*entity_limit_broken_cbck_t)();

    static const ecs::entity_t null = 0;
    // static const ecs::entity_t max_entity_count = __SIZE_MAX__;

#pragma region // Memory management:
    entity_t create_entity();
    void destroy_entity(entity_t entity);
    // void set_entity_limit_broken_cbck(entity_limit_broken_cbck_t function);
#pragma endregion

    ecs::entity_t get_num_entities();

#pragma region // Callbacks.
    void add_entity_destructor(ecs::entity_t entity, ecs::destructor_cbck_t destructor);
    void remove_entity_destructor(ecs::entity_t entity, ecs::destructor_cbck_t destructor);
#pragma endregion

}
