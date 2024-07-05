#pragma once

#include "EcsEntity.h"
#include "EcsSystem.h"

#include "EcsComponent.h"
#include "EcsComponentType.h"

/**
 * This one *should be* casted to `size_t` before it's used in the ECS implementation.
 * The free list's size is half of this. By default, this value is `8`!
 */
#define ECS_INITIAL_ENTITY_CAPACITY 8
