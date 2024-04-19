#include <unordered_map>

#include "FloatingComponent.hpp"

namespace ecs {
    namespace components {
        namespace floating {

            static std::unordered_map<ecs::entity_t, float> s_mappings;

#pragma region // Memory management.
            inline void attach(ecs::entity_t p_entity) {
                s_mappings[p_entity] = 0;
            }

            inline void detach(ecs::entity_t p_entity) {
                s_mappings.erase(p_entity);
            }

            inline void attach(ecs::entity_t p_entity, float p_value) {
                s_mappings[p_entity] = p_value;
            }
#pragma endregion

#pragma region // Getting and setting!...
            inline float get(ecs::entity_t p_entity) {
                return s_mappings[p_entity];
            }

            inline void set(ecs::entity_t p_entity, float p_value) {
                s_mappings[p_entity] = p_value;
            }
#pragma endregion

        }
    }
}
