#include <stdlib.h>
#include <stdio.h>

#define DEF_STACK(NAME,TYPE)																		\
typedef struct stack_##NAME																			\
{																									\
	size_t size;																					\
	size_t capacity;																				\
	TYPE *data;																						\
} stack_##NAME;																						\
\
void stack_##NAME##_init(stack_##NAME *s)															\
{																									\
	s->size = 0;																					\
	s->capacity = 4;																				\
	s->data = malloc(s->capacity*sizeof(TYPE));														\
}																									\
\
void stack_##NAME##_expand(stack_##NAME *s)															\
{																									\
	s->capacity *= 2;																				\
	s->data = realloc(s->data,s->capacity*sizeof(TYPE));											\
}																									\
\
void stack_##NAME##_shrink(stack_##NAME *s)															\
{																									\
	s->capacity /= 2;																				\
	s->data = realloc(s->data,s->capacity*sizeof(TYPE));											\
}																									\
\
void stack_##NAME##_push(stack_##NAME *s,TYPE value)												\
{																									\
	if(s->size == s->capacity)																		\
		stack_##NAME##_expand(s);																	\
																									\
	s->data[s->size] = value;																		\
	s->size++;																						\
}																									\
\
TYPE stack_##NAME##_pop(stack_##NAME *s)															\
{																									\
	if(s->size == 0)																				\
	{																								\
		printf("Tried removing an element from empty stack, exiting!\n");							\
		exit(-1);																					\
	}																								\
																									\
	if(3*s->size < s->capacity)																		\
		stack_##NAME##_shrink(s);																	\
																									\
	s->size--;																						\
	return s->data[s->size];																		\
}																									\
\
void stack_##NAME##_cleanup(stack_##NAME *s)														\
{																									\
	s->size = 0;																					\
	s->capacity = 0;																				\
	free(s->data);																					\
}																									\
\
void stack_##NAME##_reset(stack_##NAME *s)															\
{																									\
	stack_##NAME##_cleanup(s);																		\
	stack_##NAME##_init(s);																			\
}
