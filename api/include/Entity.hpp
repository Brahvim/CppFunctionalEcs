#include <stddef.h>

namespace Ecs {

    using entity_t = size_t;

    // Memory management:
    entity_t create_entity();
    void destroy_entity(entity_t entity);

}
