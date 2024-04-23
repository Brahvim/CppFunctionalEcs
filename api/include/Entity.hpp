#pragma once
#include <bitset>
#include <cstddef>

namespace ecs {

    class entity;

    using entity_t = entity*;
    using destructor_cbck_t = void(*)();
    // typedef void(*destructor_cbck_t)(ecs::entity entity);
    // using destructor_cbck_t = void(*)(ecs::entity entity); // Memorize this, Brahvim! Memorize this!!1

    // typedef void(*entity_limit_broken_cbck_t)();
    // static const ecs::entity max_entity_count = __SIZE_MAX__;

#pragma region // Memory management:
    ecs::entity_t create_entity();
    void destroy_entity(entity_t entity);
    // void set_entity_limit_broken_cbck(entity_limit_broken_cbck_t function);
#pragma endregion

    size_t get_num_entities();

#pragma region // Callback management.
    void attach_entity_destructor(ecs::entity_t entity, ecs::destructor_cbck_t destructor);
    void detach_entity_destructor(ecs::entity_t entity, ecs::destructor_cbck_t destructor);
#pragma endregion

    class entity {

    public:
        std::bitset<4> component_flags;

    private:
        friend ecs::entity_t ecs::create_entity();
        friend void ecs::destroy_entity(entity_t entity);
        friend void ecs::attach_entity_destructor(ecs::entity_t entity, ecs::destructor_cbck_t destructor);
        friend void ecs::detach_entity_destructor(ecs::entity_t entity, ecs::destructor_cbck_t destructor);

        ecs::destructor_cbck_t destructor;

        entity() { }

    };

}
