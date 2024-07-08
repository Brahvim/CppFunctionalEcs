#pragma once

#include "Ecs.h"

#define ECS_THREADING_BACKEND_POSIX

#ifdef ECS_THREADING_BACKEND_POSIX
#include "pthread.h"

void a() {

}

// #define ecs_thread_local
#else
#error "Please choose a threading backend for the ECS!"
#endif

struct ecs_thread;
