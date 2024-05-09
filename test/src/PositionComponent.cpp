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
			static size_t s_num_position_components;
			static size_t s_num_free_position_components;

			static ecs::entity *s_position_component_entities; // Same size as `s_position_components`. Used for mapping!
			static struct ecs::components::position::position_component *s_position_components;
			static struct ecs::components::position::position_component *s_free_position_components;

			static struct component_type s_position_component_type = {
				// .creation_function = ecs::components::position::create,
				.destruction_function = ecs::components::position::destroy,
			};
#pragma endregion

			struct position_component : public ecs::component {

				float x = 0;

				float y = 0;

				float z = 0;

				position_component() : component(&s_position_component_type) { }

			};

#pragma region // Methods!
			float get_x(const ecs::entity p_entity) {
				const auto *to_read = static_cast<struct ecs::components::position::position_component*>(
					ecs::entity_get_component(p_entity, &s_position_component_type));
				return to_read ? to_read->x : 0;
			}

			size_t destroy(const ecs::entity p_entity) {
				delete ecs::entity_get_component(p_entity, &s_position_component_type);
				return static_cast<size_t>(ecs::components::position::status::OK);
			}

			size_t create(const ecs::entity p_entity, struct ecs::component **p_storage) {
				// if (s_num_position_components < s_component_allocations)
				//     struct ecs::components::position::position_component *to_attach = nullptr; // Allocate one!

				*p_storage = static_cast<struct component*>(new struct ecs::components::position::position_component);
				// s_position_component_entities[(to_attach - static_cast<struct component*>(s_position_components)) / sizeof(struct ecs::components::position::position_component)] = entity;
				ecs::entity_attach_component(p_entity, *p_storage);

				return static_cast<size_t>(ecs::components::position::status::OK);
			}
#pragma endregion


		}

	}

}
