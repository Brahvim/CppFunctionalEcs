#include <stdio.h>
#include <stdlib.h>

#include "Ecs.h"
#include "PositionComponent.h"

static struct ecs_instance *s_ecs;
static const size_t s_entity_count = 1101; // Bug on 10th allocation!

#define LOG_ECS_CALL(call) \
printf("`" #call "` (line `%d`): %s.\n", __LINE__, ecs_status_to_string(call))
// printf("ECS `" #call "` call status [" __FILE__ ": %d ]: %s.\n", __LINE__, ecs_status_to_string(call))

int main() {
    LOG_ECS_CALL(ecs_create_instance(&s_ecs));

    // I have done the table-spaces-sorting thing before, but I'm not doing it this time...
    // puts("ECS entities table (format):");
    // puts("------------------------------------------------");
    // puts("| Index | Entity ID | Components Array Address |");
    // puts("------------------------------------------------");
    // puts("Table data:");
    // puts("------------------------------------------------");
    // for (size_t i = 0; i < s_ecs->entry_count; ++i) {
    //     printf("| %zu | %zu | %p |\n",
    //         i,
    //         s_ecs->table.entities.array[i].id,
    //         s_ecs->table.components.darray);
    // }
    // puts("------------------------------------------------");

    struct ecs_entity *const entities = calloc(sizeof(struct ecs_entity), s_entity_count);

    if (!entities) {
        perror("Couldn't allocate `entities`.");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < s_entity_count; i++)
        ecs_create_entity(s_ecs, &(entities[i]));

    for (size_t i = 0; i < s_entity_count; i++) {
        struct ecs_entity e = entities[i];
        printf("Entity ID `%zu` exists.\n", e.id);
        ecs_destroy_entity(s_ecs, &e);
    }

    LOG_ECS_CALL(ecs_destroy_instance(s_ecs));
}
