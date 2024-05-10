#include "PositionComponent.hpp"

namespace ecs {

	namespace components {

		namespace position {

			struct position_component;

#pragma region // Error-type `enum class` operators.
			enum ecs::components::position::status operator~(enum ecs::components::position::status p_value) {
				return static_cast<enum ecs::components::position::status>(~static_cast<size_t>(p_value));
			}

			enum ecs::components::position::status operator&(enum ecs::components::position::status p_lhs, enum ecs::components::position::status p_rhs) {
				return static_cast<enum ecs::components::position::status>(static_cast<size_t>(p_lhs) & static_cast<size_t>(p_rhs));
			}

			enum ecs::components::position::status operator|(enum ecs::components::position::status p_lhs, enum ecs::components::position::status p_rhs) {
				return static_cast<enum ecs::components::position::status>(static_cast<size_t>(p_lhs) | static_cast<size_t>(p_rhs));
			}
#pragma endregion

#pragma region // `static` data.
			static size_t s_component_allocations;
			static size_t s_position_components_count;
			static size_t s_free_position_components_count;

			static ecs::entity *s_position_component_entities; // Same size as `s_position_components`. Used for mapping!
			static struct ecs::components::position::position_component *s_position_components;
			static struct ecs::components::position::position_component *s_free_position_components;

			const struct ecs::component_type position_component_type {
				// ecs::components::position::create,
				// ecs::components::position::update,
				ecs::components::position::destroy,
			};
#pragma endregion

#pragma region // Methods!
			size_t destroy(const ecs::entity p_entity) {
				delete ecs::entity_get_component(p_entity, &position_component_type);
				return static_cast<size_t>(ecs::components::position::status::NONE);
			}

			size_t create(const ecs::entity p_entity, struct ecs::component **p_storage) {
				// if (s_position_components_count < s_component_allocations)
				//     struct ecs::components::position::position_component *to_attach = nullptr; // Allocate one!

				// NOLINTNEXTLINE
				*p_storage = static_cast<struct component*>(std::malloc(sizeof(struct ecs::components::position::position_component)));
				// s_position_component_entities[(to_attach - static_cast<struct component*>(s_position_components)) / sizeof(struct ecs::components::position::position_component)] = entity;
				ecs::entity_attach_component(p_entity, *p_storage);

				return static_cast<size_t>(ecs::components::position::status::NONE);
			}
#pragma endregion


		}

	}

}
