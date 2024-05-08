// Forward declarations:
struct entity;
struct component_type_info;
struct position_component; // Example component.

// Definitions (these are in their own files):
struct entity {

    size_t *component_ids; // Stores component IDs.
    struct component_type_info **component_types; // Stores a pointer to type info at the same index.
    size_t *component_count; // Length of both aforementioned arrays.

};

struct component_type_info {

    // More could go here. Anyway:
    void (*create)(struct entity*);
    void (*destroy)(struct entity);

};

struct position_component {

    float x, y, z; // Could use some vector type. Anyway.

};

// Entities API implementation file:
static size_t s_entities_array_length;
static struct entity *s_entities_array;

struct entity* create_entity() {
    /* ... */
    return NULL;
}

// "Common components API" implementation file:
static size_t s_typed_component_ids_length;
static struct size_t *s_typed_component_ids; // These are non-unique.

size_t map_to_unique_id(size_t non_unique_component_id) {

    // This stores the passed parameter in `s_typed_component_ids`, and returns the index where it was stored.

    return 0;
}

size_t map_to_typed_id(size_t unique_component_id) {
    return s_typed_component_ids[unique_component_id];
}

// Position component API implementation file:
static size_t s_num_position_components;
static struct position_component *s_position_components;
static struct component_type_info s_position_component_type = {
    .create = position_component_create,
    .destroy = position_component_destroy
};

void position_component_create(struct entity *entity) {

    size_t id = 0;
    // An allocation for a new `struct position_component` is made in `s_position_components`,
    // the index of which is stored in `id`.

    // `id` is passed into `map_to_unique_id()`:
    size_t unique_id = map_to_unique_id(id);

    entity_attach_component(unique_id, s_position_component_type);
    // ^^^ This, is equivalent to:
    // entity->component_ids[some_index] = unique_id;
    // entity->component_types[some_index] = s_position_component_type;
    // Note how the index is the same.
    // Storing a mapping to the component's type in the entity itself is something that I just... did.
    // This could just have been done in the common components API instead.

}

void position_component_destroy(size_t id) {
    // ...You know the drill!...
}

// Say no to this!:

// static struct component_type_info s_position_component_type = {
//     .create = position_component_create,
//     .destroy = position_component_destroy,
//     .get_float = position_component_get_float,
// };
//
// float position_component_get_float(struct entity *entity, size_t axis) {
//     struct position_component *component;
//
//     for (size_t i = 0; i < entity->component_ids; ++i) {
//         entity->component_types[i] == s_position_component_type;
//         component = s_position_components[map_to_typed_id(entity->component_ids)];
//     }
//
//
//     switch (axis) {
//
//         case POSITION_COMPONENT_X: {
//             return component->x;
//         } break;
//
//         case POSITION_COMPONENT_Y: {
//             return component->y;
//         } break;
//
//         case POSITION_COMPONENT_Z: {
//             return component->z;
//         } break;
//
//     }
// }
//

// Compile-time polymorphism is the way to go:
float position_component_get_x(struct entity *entity) {
    struct position_component *component;

    // This could use binary search, ...but apparently cache can make linear searches faster!:
    for (size_t i = 0; i < entity->component_ids; ++i) {
        if (entity->component_types[i] == s_position_component_type) {
            component = s_position_components[map_to_typed_id(entity->component_ids)];
            break;
        }
    }

    // THIS:
    // for (size_t i = 0; i < entity->component_ids; ++i) {
    //     component = entity->component_ids[i];
    //     if (component > s_position_components
    //         && component < s_position_component_type
    //         + (s_num_position_components * sizeof(struct position_component)))
    //         break;
    // }
    // CACHE USAGE. NO FUNCTION CALL.
    // (Okay, compilers know how to eliminate function prologues, but hey! Not looking into another array BENEFITS Mr. Cache!)
    // There won't be a need for a "common components API" at all!
    // LET'S DO THIS.

    if (component == NULL)
        // Something-something error-enum!
        ;

    return component->x;
}
