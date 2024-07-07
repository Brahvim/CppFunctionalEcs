#pragma once

#include <stdlib.h>

// ## Entities Table Layout
/*
    / ------------------------------------------------------------------ \
    |  IDs  | Component Arrays | Component Counts | Component Capacities |
    | ------------------------------------------------------------------ |
[0] |   0   | [..............] |        0         |           4          |
[1] |   6   | [..#...........] |        1         |           3          |
[2] |   2   | [..#..#........] |        2         |           2          |
[3] |   3   | [..#..#..#.....] |        3         |           1          |
[4] |   9   | [..#..#..#..#..] |        4         |           0          |
    \ ------------------------------------------------------------------ /

- Each column - each heading - each top-down region of the table, represents an array.

- The vertically-placed square brackets on the left show array indices.
  They show that each row of the table - each left-right region, represents an entry in each of these arrays, and thus, an entry in the table.

- Components are stored in a "sparse" manner.
  Only the ID, and some *type information* (see the use of `struct ecs_component_type` in `struct ecs_component`) is stored by the elements
  of the "Component Arrays" (`struct ecs_components_darray`).

- Each column's corresponding *actual array* is stored as a `struct` so its length may be tracked:

/ -------------------------------------------------------------- \
| Column Name             : Code Representation                  |
| -------------------------------------------------------------- |
| IDs                     : `struct ecs_entities_array`,         |
| Component Arrays        : `struct ecs_components_darray`,      |
| Component Counts        : `struct ecs_component_counts_array`, |
| Component Capacities    : `struct ecs_caps_array`.             |
\ -------------------------------------------------------------- /

- Each table's `struct` stores the "actual array `struct`s" as **direct members** and not pointers - this disallows further re-direction.
*/

// `struct`s.
struct ecs_component_counts_array {

    size_t capacity;
    size_t *array;

};

struct ecs_component_caps_array {

    size_t capacity;
    size_t *array;

};

struct ecs_components_darray {

    size_t capacity;
    struct ecs_component **darray;

};

struct ecs_entities_array {

    size_t capacity;
    struct ecs_entity *array;

};

struct ecs_context_table {

    struct ecs_entities_array entities;
    struct ecs_component_caps_array caps;
    struct ecs_components_darray components;
    struct ecs_component_counts_array counts;

};

struct ecs_context {

    size_t next_id;
    size_t entry_count;
    struct ecs_context_table table;

};
