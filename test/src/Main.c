#include <stdio.h>

#include "Ecs.h"
#include "PositionComponent.h"

struct ecs_instance *g_ecs;

#define LOG_ECS_CALL(call) \
printf("`" #call "` (line `%d`): %s.\n", __LINE__, ecs_status_to_string(call))
// printf("ECS `" #call "` call status [" __FILE__ ": %d ]: %s.\n", __LINE__, ecs_status_to_string(call))

int main() {
    LOG_ECS_CALL(ecs_create(&g_ecs));

    // I have done the table-spaces-sorting thing before, but I'm not doing it this time...
    // puts("ECS entities table (format):");
    // puts("------------------------------------------------");
    // puts("| Index | Entity ID | Components Array Address |");
    // puts("------------------------------------------------");
    // puts("Table data:");
    // puts("------------------------------------------------");
    // for (size_t i = 0; i < g_ecs->entry_count; ++i) {
    //     printf("| %zu | %zu | %p |\n",
    //         i,
    //         g_ecs->table.entities.array[i].id,
    //         g_ecs->table.components.darray);
    // }
    // puts("------------------------------------------------");

    LOG_ECS_CALL(ecs_destroy(g_ecs));
}
