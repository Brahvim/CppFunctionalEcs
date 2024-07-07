#include "Ecs.h"
#include "EcsInternals.h"

size_t check_overflow_calloc_style(const size_t p_count, const size_t p_element_size) {
    const size_t to_ret =
        (p_element_size != 0 && p_count > __SIZE_MAX__ / p_element_size)
        ? 0
        : p_count * p_element_size;
    return to_ret;
}
