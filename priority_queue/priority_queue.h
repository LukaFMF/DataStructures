#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../utils/types.h"

typedef struct queue
{
	u32 start;
	u32 size;
	u32 capacity;
	i32 *data;
} queue;

// first_time_init must be set only if this is the first time 
// initializinig or if queue cleanup has been called on that particular queue
void queue_init(queue *q,bool first_time_init)
{
	if(!first_time_init)
		free(q->data);
	q->start = 0u;
	q->size = 0u;
	q->capacity = 4u;
	q->data = malloc(q->capacity*sizeof(i32));
}

bool queue_is_empty(queue *q)
{
	return q->size == 0 ? true : false;
}

void queue_push(queue *q,i32 value)
{
	if(q->start + q->size == q->capacity)
	{
		q->capacity *= 2u;
		q->data = realloc(q->data,q->capacity*sizeof(i32));
	}
	q->data[q->start + q->size] = value;
	q->size++;
}

i32 queue_pop(queue *q)
{
	if(!queue_is_empty(q))
	{
		// move the queue to the start of the array to not waste space
		if(q->start != 0u && q->start >= q->capacity/2u)
		{
			memcpy(q->data,q->data + q->start,q->size*sizeof(i32));
			q->start = 0u;
		}
		
		q->start++;
		q->size--;
		return q->data[q->start - 1u];
	}
	printf("Tried removing an element from empty queue, exiting!\n");
	exit(-1);
}

void queue_cleanup(queue *q)
{
	q->start = 0u;
	q->size = 0u;
	q->capacity = 0u;
	free(q->data);
}
