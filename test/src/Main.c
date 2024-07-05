#include <stdio.h>

#include "Ecs.h"
#include "PositionComponent.h"

struct ecs_instance *g_ecs;

#define LOG_ECS_CALL(call) \
printf("ECS `" #call "` call status [" __FILE__ ": %d ]: %s.\n", __LINE__, ecs_status_to_string(call))

int main() {
    LOG_ECS_CALL(ecs_create(&g_ecs));
    LOG_ECS_CALL(ecs_destroy(g_ecs));
}
