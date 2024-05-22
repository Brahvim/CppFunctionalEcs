#pragma once

#include <stddef.h>

#include "ComponentType.h"

struct component {

    size_t offset;
    struct component_type *type;

};