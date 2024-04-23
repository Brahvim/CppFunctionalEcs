#include <unordered_map>

#include "FloatingComponent.hpp"

namespace ecs {
    namespace components {
        namespace floating {

            static std::unordered_map<ecs::entity, float> s_mappings;

#pragma region // Memory management.
            void attach(ecs::entity p_entity) {
                ecs::components::floating::attach(p_entity, 0);
            }

            void detach(ecs::entity p_entity) {
                s_mappings.erase(p_entity);
            }

            void attach(ecs::entity p_entity, float p_value) {
                s_mappings[p_entity] = p_value;
                ecs::add_entity_destructor(p_entity, [](ecs::entity_t p_destroyed) {
                    ecs::components::floating::detach(p_destroyed);
                });
            }
#pragma endregion

#pragma region // Getting and setting!...
            float get(ecs::entity p_entity) {
                return s_mappings[p_entity];
            }

            void set(ecs::entity p_entity, float p_value) {
                s_mappings[p_entity] = p_value;
            }

            void update(ecs::entity p_entity, float p_value) {
                s_mappings[p_entity] += p_value;
            }
#pragma endregion

        }
    }
}
