#include <stdlib.h>
#include <stdio.h>

#include "../utils/types.h"

#define DEF_STACK(NAME,TYPE)												\
typedef struct stack_##NAME													\
{																			\
	u32 size;																\
	u32 capacity;															\
	TYPE *data;																\
} stack_##NAME;																\
\
void stack_##NAME##_init(stack_##NAME *s)									\
{																			\
	s->size = 0u;															\
	s->capacity = 4u;														\
	s->data = malloc(s->capacity*sizeof(TYPE));								\
}																			\
\
void stack_##NAME##_expand(stack_##NAME *s)									\
{																			\
	s->capacity *= 2u;														\
	s->data = realloc(s->data,s->capacity*sizeof(TYPE));					\
}																			\
\
void stack_##NAME##_shrink(stack_##NAME *s)									\
{																			\
	s->capacity /= 2u;														\
	s->data = realloc(s->data,s->capacity*sizeof(TYPE));					\
}																			\
\
void stack_##NAME##_push(stack_##NAME *s,TYPE value)						\
{																			\
	if(s->size == s->capacity)												\
		stack_##NAME##_expand(s);											\
																			\
	s->data[s->size] = value;												\
	s->size++;																\
}																			\
\
TYPE stack_##NAME##_pop(stack_##NAME *s)									\
{																			\
	if(s->size == 0u)														\
	{																		\
		printf("Tried removing an element from empty stack, exiting!\n");	\
		exit(-1);															\
	}																		\
																			\
	if(3u*s->size < s->capacity)											\
		stack_##NAME##_shrink(s);											\
																			\
	s->size--;																\
	return s->data[s->size];												\
}																			\
\
void stack_##NAME##_cleanup(stack_##NAME *s)								\
{																			\
	s->size = 0u;															\
	s->capacity = 0u;														\
	free(s->data);															\
}																			\
\
void stack_##NAME##_reset(stack_##NAME *s)									\
{																			\
	stack_##NAME##_cleanup(s);												\
	stack_##NAME##_init(s);													\
}
