#include "Entity.hpp"
#include <vector>

namespace Ecs {

    static size_t s_num_entities = 0;
    static std::vector<Ecs::entity_t> s_entities;
    static std::vector<Ecs::entity_t> s_free_entities;

    // Memory management:
    inline Ecs::entity_t create_entity() {
        if (s_free_entities.empty()) {
            // I have a really, REALLY good idea that eliminates this branch!
        } else {
            const Ecs::entity_t to_ret = s_free_entities.back();
            s_free_entities.pop_back();
            return to_ret;
        }
    }

    inline void destroy_entity(const Ecs::entity_t entity) {

    }

    inline size_t get_num_entities() {
        return s_num_entities;
    }

}
