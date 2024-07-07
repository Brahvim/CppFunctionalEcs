#include <stdio.h>
#include <stdlib.h>

#include "Ecs.h"
#include "PositionComponent.h"

static struct ecs_context *s_ecs;
static const size_t s_entity_count = 500;

#define LOG_ECS_CALL(call)  \
printf("`" #call "` (line `%d`): %s.\n", __LINE__, ecs_status_to_string(call))
// printf("ECS `" #call "` call status [" __FILE__ ": %d ]: %s.\n", __LINE__, ecs_status_to_string(call))

int main() {
    LOG_ECS_CALL(ecs_context_create(&s_ecs));

    struct ecs_entity *const entities = calloc(sizeof(struct ecs_entity), s_entity_count);

    if (!entities) {
        perror("Couldn't allocate `entities`.");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < s_entity_count; i++) {
        printf("Allocating entity `%zu`: ", i);
        LOG_ECS_CALL(ecs_entity_create(s_ecs, &(entities[i])));
    }

    for (size_t i = 0; i < s_entity_count; i++) {
        struct ecs_entity e = entities[i];
        // printf("Entity ID `%zu` exists.\n", e.id);
        ecs_entity_destroy(s_ecs, &e);
    }

    // ecs_print_table(s_ecs);
    printf("ECS trimmed. Memory recovered: `%zu` bytes.\n", ecs_trim(s_ecs));

    LOG_ECS_CALL(ecs_context_destroy(s_ecs));
}
