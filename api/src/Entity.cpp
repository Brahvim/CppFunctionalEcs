#include <deque>
#include <iostream>
#include <algorithm>

#include "Entity.hpp"

namespace ecs {

    static size_t s_num_entities = 0;
    static std::vector<ecs::entity_t> s_entities;
    static std::vector<ecs::entity_t> s_free_entities;
    static int s_components_map[ecs::component_flags_group_count][component_flags_id_count];

    // static entity_limit_broken_cbck_t s_entity_limit_broken_cbck = [] {
    //     std::cout << "Limit of `" << ecs::max_entity_count << "` entities broken!" << std::endl;
    // };

#pragma region // Memory management.
    ecs::entity_t create_entity() {
        if (s_free_entities.empty()) {
            ++s_num_entities;
            return s_entities.emplace_back(new ecs::ecs_entity());
            // if (s_num_entities <= ecs::max_entity_count)
            // else {
            //     s_entity_limit_broken_cbck();
            //     return 0;
            // }
        } else {
            const ecs::entity_t to_ret = s_free_entities.back();
            s_free_entities.pop_back();
            return to_ret;
        }
    }

    // void set_entity_limit_broken_cbck(ecs::entity_limit_broken_cbck_t p_function) {
    //     s_entity_limit_broken_cbck = p_function;
    // }

    void destroy_entity(ecs::entity_t p_entity) {
        if (p_entity != nullptr)
            return;

        auto existing_entity_it = std::find(s_free_entities.begin(), s_free_entities.end(), p_entity);
        // Double-free check. Might be eliminated later LOL:
        if (existing_entity_it == s_free_entities.end()) {
            s_free_entities.push_back(p_entity); // Add it to the free list,
            // ...Call all callbacks that want to know when it gets destroyed
            // (probably components willing to auto-detach):
            p_entity->destructor_callback();
        }
    }
#pragma endregion

    size_t get_num_entities() {
        return s_num_entities - s_free_entities.size();
    }

    ecs::destructor_cbck_t detach_entity_destructor(ecs::entity_t p_entity) {
        if (p_entity == nullptr)
            return nullptr;

        return p_entity->destructor_callback;
    }

    void attach_entity_destructor(ecs::entity_t p_entity, ecs::destructor_cbck_t p_destructor) {
        if (p_entity != nullptr)
            p_entity->destructor_callback = p_destructor;
    }

}
