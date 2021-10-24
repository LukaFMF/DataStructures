#include <stdlib.h>
#include <stdio.h>
#include "../utils/types.h"

typedef struct stack
{
	u32 size;
	u32 capacity;
	i32 *data;
} stack;

// first_time_init must be set only if this is the first time 
// initializinig or if stack cleanup has been called on that particular stack  
void stack_init(stack *s,bool first_time_init)  
{
	if(!first_time_init)
		free(s->data);
	s->size = 0u;
	s->capacity = 8u;
	s->data = malloc(s->capacity*sizeof(i32));
}

bool stack_is_empty(stack *s)
{
	return s->size == 0u ? true : false;
}

void stack_push(stack *s,i32 value)
{
	if(s->size == s->capacity)
	{
		s->capacity *= 2u;
		s->data = realloc(s->data,s->capacity*sizeof(i32));
	}
	s->data[s->size] = value;
	s->size++;
}

i32 stack_pop(stack *s)
{
	if(!stack_is_empty(s))
	{
		s->size--;
		return s->data[s->size];
	}
	printf("Tried removing an element from empty stack, exiting!\n");
	exit(-1);
}

void stack_cleanup(stack *s)
{
	s->size = 0u;
	s->capacity = 0u;
	free(s->data);
}