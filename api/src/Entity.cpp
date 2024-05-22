#include <memory>
#include <cstdlib>

#include "Entity.hpp"

namespace ecs {

#pragma region // `struct ecs::entity_status` operators.
    enum ecs::entity_error operator~(enum ecs::entity_error p_value) {
        return static_cast<enum ecs::entity_error>(~static_cast<size_t>(p_value));
    }

    enum ecs::entity_error operator&(enum ecs::entity_error p_lhs, enum ecs::entity_error p_rhs) {
        return static_cast<enum ecs::entity_error>(static_cast<size_t>(p_lhs) & static_cast<size_t>(p_rhs));
    }

    enum ecs::entity_error operator|(enum ecs::entity_error p_lhs, enum ecs::entity_error p_rhs) {
        return static_cast<enum ecs::entity_error>(static_cast<size_t>(p_lhs) | static_cast<size_t>(p_rhs));
    }
#pragma endregion

#pragma region // Entity data arrays.
    // How many free and under-use entities?:
    static size_t s_count = 0;
    static size_t s_free_count = 0;

    // Allocations for how many elements in each array?:
    static size_t s_allocs_count = 8;
    static size_t s_free_allocs_count = s_allocs_count;
    static size_t s_component_types_length = s_allocs_count;
    static size_t s_components_list_length = s_allocs_count;
    static size_t s_component_counts_length = s_allocs_count;

    // These are the arrays:
    static size_t *s_free_list = static_cast<size_t*>(std::calloc(s_free_allocs_count, sizeof(size_t)));
    static size_t *s_component_counts = static_cast<size_t*>(std::calloc(s_allocs_count, sizeof(size_t)));
    static auto s_components_list = static_cast<struct ecs::component**>(std::calloc(s_allocs_count, sizeof(struct ecs::component*)));
    static auto s_component_types = static_cast<struct ecs::component_type**>(std::calloc(s_allocs_count, sizeof(struct ecs::component_type*)));
#pragma endregion

#pragma region // API implementation.
    size_t get_entity_count() {
        return s_count;
    }

    size_t get_free_entities_count() {
        return s_free_count;
    }

    size_t get_entity_allocations_count() {
        return s_allocs_count;
    }

    bool is_valid(const struct ecs::entity p_entity) {
        if (p_entity.offset < 1 || p_entity.offset > s_count)
            return false;

        for (size_t i = 0; i < s_free_count; ++i)
            if (s_free_list[i] == p_entity.offset)
                return false;

        return true;
    }

    enum ecs::entity_error create_entity(struct ecs::entity *p_storage) {
        if (!p_storage)
            return ecs::entity_error::INVALID_ENTITY;

        try {
            p_storage->offset = 0ULL;
        } catch (std::bad_alloc&) {
            return ecs::entity_error::MALLOC;
        }

        return ecs::entity_error::NONE;
    }

    // ...Whatever:
    enum ecs::entity_error destroy_entity(const struct ecs::entity p_entity) {
        if (ecs::is_valid(p_entity)) // Is the ID valid?
            return ecs::entity_error::INVALID_ENTITY;

        if (++s_free_count >= s_free_allocs_count) {
            s_free_allocs_count *= 2;
            s_free_list = static_cast<size_t*>(std::realloc(s_free_list, s_free_allocs_count * sizeof(size_t)));

            if (!s_free_list)
                std::exit(EXIT_FAILURE);
        }

        s_components_list[p_entity.offset] = nullptr;
        s_component_counts[p_entity.offset] = 0;
        return ecs::entity_error::NONE;
    }

    enum ecs::entity_error ensure_allocations_for(const size_t p_count) {
        if (s_free_count >= p_count)
            return ecs::entity_error::NONE;

        const auto new_component_counts = static_cast<size_t*>(std::realloc(s_component_counts, p_count * sizeof(size_t)));
        const auto new_components_list = static_cast<ecs::component**>(std::realloc(s_components_list, p_count * sizeof(ecs::component*)));

        auto to_ret = ecs::entity_error::NONE;

        if (new_component_counts) {
            s_component_counts = new_component_counts;
            s_component_counts_length *= 2;
        } else to_ret = ecs::entity_error::MALLOC;

        if (new_components_list) {
            s_components_list = new_components_list;
            s_components_list_length *= 2;
        } else to_ret = ecs::entity_error::MALLOC;

        return to_ret;
    }

    // If you get `nullptr`, you know it wasn't attached. No error code needed.
    struct ecs::component* entity_get_component(const struct ecs::entity p_entity, const ecs::component_type *p_type) {
        struct ecs::component *component = nullptr;
        const size_t max = s_component_counts[p_entity.offset];

        for (size_t i = 0; i < max; ++i)
            if (s_component_types[i] == p_type) {
                component = s_components_list[i];
                break;
            }

        return component;
    }

    enum ecs::entity_error entity_detach_component(const struct ecs::entity p_entity, const struct ecs::component_type *p_type) {
        if (ecs::is_valid(p_entity))
            return ecs::entity_error::INVALID_ENTITY;

        // auto a = s_components_list[p_entity.offset];
        const size_t max = s_component_counts[p_entity.offset];

        for (size_t i = 0; i < max; i++) {
            // const auto b = a;
            // if (b.type == p_type)
            //     a = nullptr;
        }

        return ecs::entity_error::NONE;
    }

    // Could this use a base type...? No `virtual`s though, please.
    enum ecs::entity_error entity_attach_component(const struct ecs::entity p_entity, const struct ecs::component * p_component) {
        if (!(ecs::is_valid(p_entity) && p_component))
            return ecs::entity_error::INVALID_ENTITY & ecs::entity_error::INVALID_COMPONENT;

        // entity->components += p_component; // Add it there.
        return ecs::entity_error::NONE;
    };
#pragma endregion

}
