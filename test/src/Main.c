#include <stdio.h>
#include <stdlib.h>

#include "Ecs.h"
#include "PositionComponent.h"

#define LOG_ECS_CALL(call)  \
printf("`" #call "` (line `%d`): %s.\n", __LINE__, ecs_context_status_to_string(call))
// printf("ECS `" #call "` call status [" __FILE__ ": %d ]: %s.\n", __LINE__, ecs_context_status_to_string(call))

static struct ecs_context *s_ecs;
static const size_t s_entity_count = 1000;

int main() {
    LOG_ECS_CALL(ecs_context_create(&s_ecs));

    struct ecs_entity *const entities = calloc(sizeof(struct ecs_entity), s_entity_count);

    if (!entities) {
        perror("Couldn't allocate `entities`.");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < s_entity_count; i++) {
        // printf("Allocating entity `%zu`.\n", i);
        // LOG_ECS_CALL(
        ecs_entity_create(s_ecs, &(entities[i])) // )
            ;
    }

    printf("ECS entity count: `%zu`.\n", ecs_context_entity_count(s_ecs));
    printf("ECS trimmed. Memory recovered: `%zu` bytes.\n", ecs_context_trim(s_ecs));

    for (size_t i = 0; i < s_entity_count; ++i) {
        if (i % 1000 == 0)
            printf("Deallocating entity `%zu`.\n", i);
        ecs_entity_destroy(s_ecs, entities[i]);
    }

    printf("ECS entity count: `%zu`.\n", ecs_context_entity_count(s_ecs));
    printf("ECS trimmed. Memory recovered: `%zu` bytes.\n", ecs_context_trim(s_ecs));
    printf("ECS trimmed. Memory recovered: `%zu` bytes.\n", ecs_context_trim(s_ecs));
    printf("ECS trimmed. Memory recovered: `%zu` bytes.\n", ecs_context_trim(s_ecs));

    LOG_ECS_CALL(ecs_context_destroy(s_ecs));
}
