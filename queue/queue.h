#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../utils/types.h"

#define DEF_QUEUE(NAME,TYPE)												\
typedef struct queue_##NAME													\
{																			\
	u32 start;																\
	u32 size;																\
	u32 capacity;															\
	TYPE *data;																\
} queue_##NAME;																\
\
void queue_init_##NAME(queue_##NAME *q)										\
{																			\
	q->start = 0u;															\
	q->size = 0u;															\
	q->capacity = 4u;														\
	q->data = malloc(q->capacity*sizeof(TYPE));								\
}																			\
\
void queue_expand_##NAME(queue_##NAME *q)									\
{																			\
	q->capacity *= 2u;														\
	q->data = realloc(q->data,q->capacity*sizeof(TYPE));					\
}																			\
\
void queue_shrink_##NAME(queue_##NAME *q)									\
{																			\
	q->capacity /= 2u;														\
	q->data = realloc(q->data,q->capacity*sizeof(TYPE));					\
}																			\
\
void queue_push_##NAME(queue_##NAME *q,TYPE value)							\
{																			\
	const u32 push_index = q->start + q->size;								\
	if(push_index == q->capacity)											\
		queue_expand_##NAME(q);												\
																			\
	q->data[push_index] = value;											\
	q->size++;																\
}																			\
\
TYPE queue_pop_##NAME(queue_##NAME *q)										\
{																			\
	if(q->size == 0)														\
	{																		\
		printf("Tried removing an element from empty queue, exiting!\n");	\
		exit(-1);															\
	}																		\
																			\
	const TYPE removed = q->data[q->start];									\
	q->start++;																\
	q->size--;																\
																			\
	/* move the queue to the start of the array to not waste space */		\
	if(q->start != 0u && q->start > q->size)								\
	{																		\
		memcpy(q->data,q->data + q->start,q->size*sizeof(TYPE));			\
		q->start = 0u;														\
	}																		\
																			\
	/* if more than two thirds of allocated space is unused we shrik it	*/	\
	if(q->capacity > 4u && q->start + q->size < q->capacity/3u)				\
		queue_shrink_##NAME(q);												\
																			\
	return removed;															\
}																			\
\
void queue_cleanup_##NAME(queue_##NAME *q)									\
{																			\
	q->start = 0u;															\
	q->size = 0u;															\
	q->capacity = 0u;														\
	free(q->data);															\
}																			\
\
void queue_reset_##NAME(queue_##NAME *q)									\
{																			\
	queue_cleanup_##NAME(q);												\
	queue_init_##NAME(q);													\
}														
