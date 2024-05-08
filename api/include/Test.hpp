#include <cstdlib>
#include <concepts>
#include <utility>

// Opaque!:
struct entity; // May need not be opaque at all.
struct component { }; // Marker! ...Uhh, Miss Performance, are you still around?
struct component_type;
struct position_component;

enum struct entity_status : size_t {

	OK = 0,

	MALLOC = 1,

	NULL_ENTITY = 2,

	NULL_COMPONENT = 4,

};

entity_status operator&(entity_status lhs, entity_status rhs) {
	return static_cast<entity_status>(static_cast<size_t>(lhs) & static_cast<size_t>(rhs));
}

entity_status operator|(entity_status lhs, entity_status rhs) {
	return static_cast<entity_status>(static_cast<size_t>(lhs) | static_cast<size_t>(rhs));
}

entity_status operator~(entity_status value) {
	return static_cast<entity_status>(~static_cast<size_t>(value));
}

enum class component_status : size_t {

	OK = 0,

	MALLOC = 1,

	NULL_ENTITY = 2,

	NULL_COMPONENT = 4,

};

component_status operator&(component_status lhs, component_status rhs) {
	return static_cast<component_status>(static_cast<size_t>(lhs) & static_cast<size_t>(rhs));
}

component_status operator|(component_status lhs, component_status rhs) {
	return static_cast<component_status>(static_cast<size_t>(lhs) | static_cast<size_t>(rhs));
}

component_status operator~(component_status value) {
	return static_cast<component_status>(~static_cast<size_t>(value));
}

struct entity {

	size_t num_components;
	struct component *components;

};

struct component_type {

	using component_creation_function
		= enum component_status(*)(struct entity *entity, struct component **component_id_storage);
	using component_destruction_function
		= enum component_status(*)(struct entity *entity);

	component_creation_function creation_function;
	component_destruction_function destruction_function;

};


static size_t s_num_entities;
static struct entity *s_entities;
static struct entity *s_free_entities;
static size_t s_num_entity_allocations;

// ...Whatever:
enum entity_status create_entity(struct entity**) {
	return entity_status::OK;
}

enum entity_status destroy_entity(struct entity* entity) {
	return entity_status::OK;
}

// Could this use a base type...? No `virtual`s though, please.
enum entity_status entity_attach_component(struct entity *entity, struct component *component_handle) {

	if (!(entity && component_handle))
		return entity_status::NULL_ENTITY & entity_status::NULL_COMPONENT;

	// entity->components += component_handle; // Add it there.
	return entity_status::OK;
};

template<typename component_t>
	requires std::derived_from<component_t, component>
component_t* entity_get_component(struct entity* entity) {
	component_t* component = nullptr;
	const size_t max = entity->num_components;

	for (size_t i = 0; i < max; ++i) {
		component = static_cast<component_t*>(&entity->components[i]);
		if (component)
			break;
	}

	return component;
}

struct position_component : public component {

	float x;

	float y;

	float z;

};

static size_t s_component_allocations;
static size_t s_num_position_components;
static size_t s_num_free_position_components;


static struct entity *s_position_component_entities; // Same size as `s_position_components`. Used for mapping!
static struct position_component *s_position_components;
static struct position_component *s_free_position_components;

// There will be error handling too...
enum component_status position_component_create(struct entity *entity, struct component **storage) {
	// if (s_num_position_components < s_component_allocations)
	//     struct position_component *to_attach = nullptr; // Allocate one!

	*storage = static_cast<struct component*>(new position_component);
	struct component *to_attach = *storage; // Allocate for this first!

	s_position_component_entities[(to_attach - static_cast<struct component*>(s_position_components)) / sizeof(struct position_component)];
	entity_attach_component(entity, *storage);
	*storage = to_attach;

	return component_status::OK; // Return a pointer to it.
}

static struct component_type s_position_component_type = {
	.creation_function = position_component_create,
	.destruction_function = nullptr,
};

float position_component_get_x(struct entity* entity) {
	const struct position_component* to_read = entity_get_component<struct position_component>(entity);
	return to_read ? to_read->x : 0;
}

void ecs_test_main() {
	struct entity *e = nullptr;
	create_entity(&e);

	struct component *position = nullptr;
	position_component_create(e, &position);
	entity_attach_component(e, position);
}
