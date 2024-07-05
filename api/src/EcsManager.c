#include <stdlib.h>

#include "Ecs.h"

// Welcome to the ECS's internals!

extern void ecs_entity_init();

#pragma region // Declaration for this file.
void ecs_register_for_cleanup(ecs_cleanup_callback_t *callback_function);
size_t check_overflow_calloc_style(const size_t count, const size_t element_size);
#pragma endregion

#pragma region // Management.
static size_t s_len;
static size_t s_allocs;
static ecs_cleanup_callback_t **s_cleanup_callbacks = NULL;

void ecs_init() {
    ecs_entity_init();
}

void ecs_cleanup() {
    for (size_t i = 0; i < s_len; ++i) {
        ecs_cleanup_callback_t *const fxn = s_cleanup_callbacks[i];
        if (fxn)
            fxn();
    }
}

void ecs_register_for_cleanup(ecs_cleanup_callback_t *p_fxn) {
    if (s_len >= s_allocs) {
        const size_t new_allocs_as_count = s_allocs == 0 ? 1 : check_overflow_calloc_style(s_allocs, 2);
        const size_t new_allocs_as_bytes = check_overflow_calloc_style(new_allocs_as_count, sizeof(ecs_cleanup_callback_t*));

        if (!new_allocs_as_bytes)
            abort();

        ecs_cleanup_callback_t **new_array = realloc(s_cleanup_callbacks, new_allocs_as_bytes);

        if (!new_array)
            abort();

        s_allocs = new_allocs_as_count;
        s_cleanup_callbacks = new_array;
    }

    // Add the new callback to the array
    s_cleanup_callbacks[s_len++] = p_fxn;
}
#pragma endregion

#pragma region // Utilities.
size_t check_overflow_calloc_style(const size_t p_count, const size_t p_element_size) {
    return (p_element_size != 0 && p_count > __SIZE_MAX__ / p_element_size) ? p_count * p_element_size : 0;
}
#pragma endregion
