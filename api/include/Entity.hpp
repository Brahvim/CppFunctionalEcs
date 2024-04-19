#include <stddef.h>

namespace Ecs {

    using entity_t = size_t;

#pragma region // Memory management:
    entity_t create_entity();
    void destroy_entity(entity_t entity);
#pragma endregion

    inline size_t get_num_entities();

}
