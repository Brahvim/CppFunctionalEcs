#pragma once

#include <cstdlib>
#include <functional>

namespace ecs {

    struct entity;

    // using component_update_function_t = std::function<size_t()>;
    using component_destruction_function_t = std::function<size_t(const struct ecs::entity entity)>;
    // using component_creation_function_t = std::function<size_t(const struct ecs::entity entity, struct ecs::component *component_storage)>;


    struct component_type {

        explicit component_type(
            // ecs::component_update_function_t update_function,
            // ecs::component_creation_function_t creation_function,
            const ecs::component_destruction_function_t &destruction_function);

        // ecs::component_update_function_t update_function;
        // ecs::component_creation_function_t creation_function;
        ecs::component_destruction_function_t destruction_function;

    };

}
