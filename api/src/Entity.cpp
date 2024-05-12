#include <memory>
#include <cstdlib>

#include "Entity.hpp"

namespace ecs {

#pragma region // `ecs::entity_status` operators.
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
    static size_t s_count = 0;
    static size_t s_free_count = 0;
    static size_t s_allocs_count = 8;
    static size_t s_free_allocs_count = 0;

    // If these fail, well, we're screwed! Crash guaranteed. ...Alright:
    static size_t *s_component_counts = static_cast<size_t*>(std::calloc(s_allocs_count, sizeof(size_t)));
    static ecs::entity *s_free_list = static_cast<ecs::entity*>(std::calloc(s_free_allocs_count, sizeof(ecs::entity)));
    static struct ecs::component **s_components_list = static_cast<ecs::component**>(std::calloc(s_allocs_count, sizeof(struct ecs::component*)));
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

    bool is_valid(const ecs::entity p_entity) {
        if (p_entity < 1 || p_entity > s_count)
            return false;

        for (size_t i = 0; i < s_free_count; ++i)
            if (s_free_list[i] == p_entity)
                return false;

        return true;
    }

    enum ecs::entity_error create_entity(ecs::entity *p_storage) {
        if (!p_storage)
            return ecs::entity_error::INVALID_ENTITY;

        try {
            *p_storage = 0ULL;
        } catch (std::bad_alloc&) {
            return ecs::entity_error::MALLOC;
        }

        return ecs::entity_error::NONE;
    }

    // ...Whatever:
    enum ecs::entity_error destroy_entity(const ecs::entity p_entity) {
        if (ecs::is_valid(p_entity)) // Is the ID valid?
            return ecs::entity_error::INVALID_ENTITY;

        if (++s_free_count >= s_free_allocs_count) {
            s_free_allocs_count *= 2;
            s_free_list = static_cast<ecs::entity*>(std::realloc(s_free_list, s_free_allocs_count * sizeof(ecs::entity)));

            if (!s_free_list)
                std::exit(EXIT_FAILURE);
        }

        s_components_list[p_entity] = nullptr;
        s_component_counts[p_entity] = 0;
        return ecs::entity_error::NONE;
    }

    enum ecs::entity_error ensure_allocations_for(const size_t p_count) {
        if (s_allocs_count > p_count)
            return ecs::entity_error::NONE;

        if (++s_count >= s_allocs_count) {
            s_allocs_count *= 2;

            auto new_component_counts = static_cast<ecs::entity*>(std::realloc(s_component_counts, p_count * sizeof(ecs::entity)));
            auto new_components_list = static_cast<ecs::component**>(std::realloc(s_components_list, p_count * sizeof(ecs::component*)));

            if (new_component_counts || new_components_list) {
                s_component_counts = new_component_counts;
                s_components_list = new_components_list;
            } else {
                s_allocs_count /= 2;
                return ecs::entity_error::MALLOC;
            }
        }

        return ecs::entity_error::NONE;
    }

    // If you get `nullptr`, you know it wasn't attached. No error code needed.
    struct ecs::component* entity_get_component(const ecs::entity p_entity, const ecs::component_type *p_type) {
        struct ecs::component *component = nullptr;
        const size_t max = s_component_counts[p_entity];

        for (size_t i = 0; i < max; ++i)
            if ((component = s_components_list[i])->type == p_type)
                break;

        return component;
    }

    enum ecs::entity_error entity_detach_component(const ecs::entity p_entity, const struct ecs::component_type *p_type) {
        if (ecs::is_valid(p_entity))
            return ecs::entity_error::INVALID_ENTITY;

        auto a = s_components_list[p_entity];
        const size_t max = s_component_counts[p_entity];

        for (size_t i = 0; i < max; i++) {
            auto b = a;
            if (b->type == p_type)
                a = nullptr;
        }

        return ecs::entity_error::NONE;
    }

    // Could this use a base type...? No `virtual`s though, please.
    enum ecs::entity_error entity_attach_component(const ecs::entity p_entity, const struct ecs::component *p_component) {
        if (!(ecs::is_valid(p_entity) && p_component))
            return ecs::entity_error::INVALID_ENTITY & ecs::entity_error::INVALID_COMPONENT;

        // entity->components += p_component; // Add it there.
        return ecs::entity_error::NONE;
    };
#pragma endregion

}
