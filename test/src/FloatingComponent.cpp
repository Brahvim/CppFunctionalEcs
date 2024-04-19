#include <unordered_map>

#include "FloatingComponent.hpp"

namespace ecs {
    namespace components {
        namespace floating {

            static std::unordered_map<ecs::entity_t, float> s_mappings;

#pragma region // Memory management.
            void attach(ecs::entity_t p_entity) {
                s_mappings[p_entity] = 0;
            }

            void detach(ecs::entity_t p_entity) {
                s_mappings.erase(p_entity);
            }

            void attach(ecs::entity_t p_entity, float p_value) {
                s_mappings[p_entity] = p_value;
            }
#pragma endregion

#pragma region // Getting and setting!...
            float get(ecs::entity_t p_entity) {
                return s_mappings[p_entity];
            }

            void set(ecs::entity_t p_entity, float p_value) {
                s_mappings[p_entity] = p_value;
            }

            void update(ecs::entity_t p_entity, float p_value) {
                s_mappings[p_entity] += p_value;
            }
#pragma endregion

        }
    }
}
