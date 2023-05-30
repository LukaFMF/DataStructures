#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../utils/types.h"

#define DEF_QUEUE(NAME,TYPE)																		\
typedef struct queue_##NAME																			\
{																									\
	size_t start;																					\
	size_t size;																					\
	size_t capacity;																				\
	TYPE *data;																						\
} queue_##NAME;																						\
\
void queue_##NAME##_init(queue_##NAME *q)															\
{																									\
	q->start = 0;																					\
	q->size = 0;																					\
	q->capacity = 4;																				\
	q->data = malloc(q->capacity*sizeof(TYPE));														\
}																									\
\
void queue_##NAME##_expand(queue_##NAME *q)															\
{																									\
	q->capacity *= 2;																				\
	q->data = realloc(q->data,q->capacity*sizeof(TYPE));											\
}																									\
\
void queue_##NAME##_shrink(queue_##NAME *q)															\
{																									\
	q->capacity /= 2;																				\
	q->data = realloc(q->data,q->capacity*sizeof(TYPE));											\
}																									\
\
void queue_##NAME##_push(queue_##NAME *q,TYPE value)												\
{																									\
	const size_t push_index = q->start + q->size;													\
	if(push_index == q->capacity)																	\
		queue_##NAME##_expand(q);																	\
																									\
	q->data[push_index] = value;																	\
	q->size++;																						\
}																									\
\
TYPE queue_##NAME##_pop(queue_##NAME *q)															\
{																									\
	if(q->size == 0)																				\
	{																								\
		printf("Tried removing an element from empty queue, exiting!\n");							\
		exit(-1);																					\
	}																								\
																									\
	const TYPE removed = q->data[q->start];															\
	q->start++;																						\
	q->size--;																						\
																									\
	/* move the queue to the start of the array to not waste space */								\
	if(q->start != 0 && q->start > q->size)															\
	{																								\
		memcpy(q->data,q->data + q->start,q->size*sizeof(TYPE));									\
		q->start = 0;																				\
	}																								\
																									\
	/* if more than two thirds of allocated space is unused we shrik it	*/							\
	if(q->capacity > 4 && q->start + q->size < q->capacity/3)										\
		queue_##NAME##_shrink(q);																	\
																									\
	return removed;																					\
}																									\
\
void queue_##NAME##_cleanup(queue_##NAME *q)														\
{																									\
	q->start = 0;																					\
	q->size = 0;																					\
	q->capacity = 0;																				\
	free(q->data);																					\
}																									\
\
void queue_##NAME##_reset(queue_##NAME *q)															\
{																									\
	queue_##NAME##_cleanup(q);																		\
	queue_##NAME##_init(q);																			\
}														
