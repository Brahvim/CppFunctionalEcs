#pragma once
#include <cstddef>

namespace ecs {

    using entity = size_t;
    typedef void(*destructor_cbck_t)(ecs::entity entity);
    // typedef void(*entity_limit_broken_cbck_t)();

    static const ecs::entity null = 0;
    // static const ecs::entity_t max_entity_count = __SIZE_MAX__;

#pragma region // Memory management:
    entity create_entity();
    void destroy_entity(entity entity);
    // void set_entity_limit_broken_cbck(entity_limit_broken_cbck_t function);
#pragma endregion

    ecs::entity get_num_entities();

#pragma region // Callbacks.
    void add_entity_destructor(ecs::entity entity, ecs::destructor_cbck_t destructor);
    void remove_entity_destructor(ecs::entity entity, ecs::destructor_cbck_t destructor);
#pragma endregion

}
