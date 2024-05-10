#include "ComponentType.hpp"

namespace ecs {

    static size_t s_count = 0;
    static size_t s_allocs_count = 8;
    static struct ecs::component_type *s_list = static_cast<ecs::component_type*>((std::calloc(s_allocs_count, sizeof(struct ecs::component_type))));

    ecs::component_type::component_type(
            // const ecs::component_update_function_t &p_update_function,
            // const ecs::component_creation_function_t &p_creation_function,
            const ecs::component_destruction_function_t &p_destruction_function)
        : destruction_function(p_destruction_function) {
        // Allocate if needed:

        if (++s_count >= s_allocs_count) {
            s_allocs_count *= 2;
            auto new_list = static_cast<ecs::component_type*>(std::realloc(s_list, s_allocs_count * sizeof(struct ecs::component_type)));

            if (!new_list)
                std::exit(EXIT_FAILURE);

            s_list = new_list;
        }

    };

}
