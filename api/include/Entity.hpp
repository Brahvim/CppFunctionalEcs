#include <cstddef>

namespace ecs {


    using entity_t = size_t;
    inline const ecs::entity_t null_entity = 0;
    typedef void(*entity_limit_broken_cbck_t)();

#pragma region // Memory management:
    entity_t create_entity();
    void destroy_entity(entity_t entity);
    void set_entity_limit_broken_cbck(entity_limit_broken_cbck_t function);
#pragma endregion

    size_t get_num_entities();

}
