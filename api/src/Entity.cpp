#include <memory>

#include "Entity.hpp"

namespace Ecs {

    static size_t s_num_entities = 0;

    // Free list management:
    static size_t s_num_free_entities = 0;
    static size_t *s_free_entities_list_length = 0;
    static Ecs::entity_t *s_free_entities_list = (Ecs::entity_t*)std::calloc(24, sizeof(Ecs::entity_t));

#pragma region // Memory management:
    inline Ecs::entity_t create_entity() {
        if (s_num_free_entities == 0);
    }

    inline void destroy_entity(const Ecs::entity_t p_entity) {

    }
#pragma endregion

    inline size_t get_num_entities() {
        return s_num_entities;
    }

}
