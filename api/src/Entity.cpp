#include <deque>
#include <iostream>
#include <algorithm>

#include "Entity.hpp"

namespace ecs {

    static size_t s_num_entities = 0;
    static std::deque<ecs::entity_t> s_free_entities;
    static entity_limit_broken_cbck_t s_entity_limit_broken_cbck = [] {
        std::cout << "Limit of `" << ecs::max_entity_count << "` entities broken!" << std::endl;
    };

#pragma region // Memory management.
    ecs::entity_t create_entity() {
        if (s_free_entities.empty()) {
            if (s_num_entities <= ecs::max_entity_count)
                return ++s_num_entities;
            else {
                s_entity_limit_broken_cbck();
                return 0;
            }
        } else {
            const ecs::entity_t to_ret = s_free_entities.back();
            s_free_entities.pop_back();
            return to_ret;
        }
    }

    void set_entity_limit_broken_cbck(ecs::entity_limit_broken_cbck_t p_function) {
        s_entity_limit_broken_cbck = p_function;
    }

    void destroy_entity(ecs::entity_t p_entity) {
        auto existing_entity_it = std::find(s_free_entities.begin(), s_free_entities.end(), p_entity);
        // Double-free check. Might be eliminated later LOL:
        if (existing_entity_it == s_free_entities.end())
            s_free_entities.push_back(p_entity);
    }
#pragma endregion

    ecs::entity_t get_num_entities() {
        return s_num_entities - s_free_entities.size();
    }

}
