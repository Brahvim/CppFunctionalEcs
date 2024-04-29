#pragma once
#include <bitset>
#include <cstddef>

namespace ecs {

    class ecs_entity;

    using entity_t = ecs_entity*;
    using destructor_cbck_t = void(*)();
    static inline const size_t component_flags_bits = 8;
    static inline const size_t component_flags_id_count = ecs::component_flags_bits / 2;
    static inline const size_t component_flags_group_count = ecs::component_flags_bits - ecs::component_flags_id_count;
    // typedef void(*destructor_cbck_t)(ecs::ecs_entity ecs_entity);
    // using destructor_cbck_t = void(*)(ecs::ecs_entity ecs_entity); // Memorize this, Brahvim! Memorize this!!1
    // 
    // typedef void(*entity_limit_broken_cbck_t)();
    // static const ecs::ecs_entity max_entity_count = __SIZE_MAX__;

#pragma region // Memory management:
    ecs::entity_t create_entity();
    void destroy_entity(entity_t ecs_entity);
    // void set_entity_limit_broken_cbck(entity_limit_broken_cbck_t function);
#pragma endregion

    size_t get_num_entities();

#pragma region // Callback management.
    ecs::destructor_cbck_t detach_entity_destructor(ecs::entity_t ecs_entity);
    void attach_entity_destructor(ecs::entity_t ecs_entity, ecs::destructor_cbck_t destructor);
#pragma endregion

    class ecs_entity {

    public:
        std::bitset<ecs::component_flags_bits> component_flags;

    private:
        friend ecs::entity_t ecs::create_entity();
        friend void ecs::destroy_entity(entity_t ecs_entity);
        friend ecs::destructor_cbck_t detach_entity_destructor(ecs::entity_t ecs_entity);
        friend void ecs::attach_entity_destructor(ecs::entity_t ecs_entity, ecs::destructor_cbck_t destructor);

        ecs::destructor_cbck_t destructor_callback;

        ecs_entity() { }

    };

}
