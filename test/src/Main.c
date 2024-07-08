#include <stdio.h>
#include <stdlib.h>

#include "Ecs.h"
#include "PositionComponent.h"

#define LOG_ECS_CALL(call)  \
printf("`" #call "` (line `%d`): %s.\n", __LINE__, ecs_context_status_to_string(call))
// printf("ECS `" #call "` call status [" __FILE__ ": %d ]: %s.\n", __LINE__, ecs_context_status_to_string(call))

static struct ecs_context *s_ecs;
static const size_t s_entity_count = 1000;

void print_count_and_trim_thrice() {
    printf("ECS entity count: `%zu`.\n", ecs_context_entity_count(s_ecs));

    const size_t one = ecs_context_trim(s_ecs);
    const size_t two = ecs_context_trim(s_ecs);
    const size_t three = ecs_context_trim(s_ecs);

    // The order of passing arguments isn't guaranteed!
    // Yan (*"The Cherno"*) had a video on this, remember?

    printf(
        "ECS trimmed THRICE! Memory recovered each iteration:"

        "\n\t1. `%zu` bytes,"
        "\n\t2. `%zu` bytes,"
        "\n\t3. `%zu` bytes.\n",

        one, two, three
    );
}

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

    print_count_and_trim_thrice();

    for (size_t i = 0; i < s_entity_count; ++i) {
        // printf("Deallocating entity `%zu`.\n", i);
        ecs_entity_destroy(s_ecs, entities[i]);
    }

    print_count_and_trim_thrice();
    LOG_ECS_CALL(ecs_context_destroy(s_ecs));
}
