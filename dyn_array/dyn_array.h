#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// dyn_array_T_expand and dyn_array_T_shrink
// should NOT be called manually
#define DEF_DYN_ARRAY(NAME,TYPE)																	\
typedef struct dyn_array_##NAME																		\
{																									\
	size_t size;																					\
	size_t capacity;																				\
	TYPE *data;																						\
} dyn_array_##NAME;																					\
\
void dyn_array_##NAME##_init(dyn_array_##NAME *a,size_t init_cap)									\
{																									\
	size_t curr_cap = 4;																			\
	while(curr_cap < init_cap)																		\
		curr_cap *= 2;																				\
																									\
	a->size = 0;																					\
	a->capacity = curr_cap;																			\
	a->data = malloc(curr_cap*sizeof(TYPE));														\
}																									\
\
void dyn_array_##NAME##_expand(dyn_array_##NAME *a)													\
{																									\
	a->capacity *= 2;																				\
	a->data = realloc(a->data,a->capacity*sizeof(TYPE));											\
}																									\
\
void dyn_array_##NAME##_shrink(dyn_array_##NAME *a)													\
{																									\
	a->capacity /= 2;																				\
	a->data = realloc(a->data,a->capacity*sizeof(TYPE));											\
}																									\
\
void dyn_array_##NAME##_insert(dyn_array_##NAME *a,size_t index,TYPE value)							\
{																									\
	if(a->size < index)																				\
	{																								\
		printf("Can not insert an element to index %llu,"											\
		"when array is of size %llu. Exiting!\n",index,a->size);									\
		exit(-1);																					\
	}																								\
																									\
	if(a->size == a->capacity)																		\
		dyn_array_##NAME##_expand(a);																\
																									\
	TYPE *move_ptr = a->data + index;																\
	const size_t move_section_size = (a->size - index)*sizeof(TYPE);								\
	memmove(move_ptr + 1,move_ptr,move_section_size);												\
	a->data[index] = value;																			\
	a->size++;																						\
}																									\
\
void dyn_array_##NAME##_delete(dyn_array_##NAME *a,size_t index)									\
{																									\
	if(a->size == 0)																				\
	{																								\
		printf("Can not remove an element from empty array. Exiting!\n");							\
		exit(-1);																					\
	}																								\
																									\
	if(3*a->size < a->capacity && a->size > 4)														\
		dyn_array_##NAME##_shrink(a);																\
																									\
	TYPE *move_ptr = a->data + index;																\
	const size_t move_section_size = (a->size - index)*sizeof(TYPE);								\
	memmove(move_ptr,move_ptr + 1,move_section_size);												\
	a->size--;																						\
}																									\
\
void dyn_array_##NAME##_append(dyn_array_##NAME *a,TYPE value)										\
{																									\
	dyn_array_##NAME##_insert(a,a->size,value);														\
}																									\
\
void dyn_array_##NAME##_cleanup(dyn_array_##NAME *a)												\
{																									\
	a->size = 0;																					\
	a->capacity = 0;																				\
	free(a->data);																					\
}																									\
\
void dyn_array_##NAME##_reset(dyn_array_##NAME *a,size_t init_cap)									\
{																									\
	dyn_array_##NAME##_cleanup(a);																	\
	dyn_array_##NAME##_init(a,init_cap);															\
}
