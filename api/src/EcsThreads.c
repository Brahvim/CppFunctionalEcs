#include "EcsThreads.h"

struct ecs_thread {

#ifdef ECS_THREADING_BACKEND_POSIX
    pthread_t thread;
#endif

};
