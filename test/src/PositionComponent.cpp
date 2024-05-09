#include "PositionComponent.hpp"

namespace ecs {

	namespace components {

		namespace position {

			static size_t s_component_allocations;
			static size_t s_num_position_components;
			static size_t s_num_free_position_components;

			static struct entity *s_position_component_entities; // Same size as `s_position_components`. Used for mapping!
			static struct position_component *s_position_components;
			static struct position_component *s_free_position_components;

			static struct component_type s_position_component_type = {
				.creation_function = ecs::components::position::create,
				.destruction_function = nullptr,
			};

			struct position_component : public component {

				float x = 0;

				float y = 0;

				float z = 0;

				position_component() : component(&s_position_component_type) { }

			};

			// There will be error handling too...
			enum component_status create(struct entity *entity, struct component **storage) {
				// if (s_num_position_components < s_component_allocations)
				//     struct position_component *to_attach = nullptr; // Allocate one!

				*storage = static_cast<struct component*>(new position_component());
				struct component *to_attach = *storage; // Allocate for this first

				// s_position_component_entities[(to_attach - static_cast<struct component*>(s_position_components)) / sizeof(struct position_component)] = entity;
				ecs::entity_attach_component(entity, *storage);
				*storage = to_attach;

				return component_status::OK; // Return a pointer to it.
			}

			float get_x(struct entity* entity) {
				const ecs::components::position::position_component
					*to_read = ecs::entity_get_component<ecs::components::position::position_component>(entity);
				return to_read ? to_read->x : 0;
			}

		}

	}

}

