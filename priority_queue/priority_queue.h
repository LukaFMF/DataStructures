#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEF_PRIORITY_QUEUE(NAME,TYPE)																\
typedef struct priority_queue_##NAME																\
{																									\
	size_t start;																					\
	size_t size;																					\
	size_t capacity;																				\
	f32 *priorities;																				\
	TYPE *data;																						\
} priority_queue_##NAME;																			\
\
void priority_queue_##NAME##_init(priority_queue_##NAME *pq)										\
{																									\
	pq->start = 0;																					\
	pq->size = 0;																					\
	pq->capacity = 4;																				\
	pq->priorities = malloc(pq->capacity*sizeof(f32));												\
	pq->data = malloc(pq->capacity*sizeof(TYPE));													\
}																									\
\
void priority_queue_##NAME##_expand(priority_queue_##NAME *pq)										\
{																									\
	pq->capacity *= 2;																				\
	pq->priorities = realloc(pq->priorities,pq->capacity*sizeof(f32));								\
	pq->data = realloc(pq->data,pq->capacity*sizeof(TYPE));											\
}																									\
\
void priority_queue_##NAME##_shrink(priority_queue_##NAME *pq)										\
{																									\
	pq->capacity /= 2;																				\
	pq->priorities = realloc(pq->priorities,pq->capacity*sizeof(TYPE));								\
	pq->data = realloc(pq->data,pq->capacity*sizeof(TYPE));											\
}																									\
\
void priority_queue_##NAME##_prioritized_insert(priority_queue_##NAME *pq,f32 priority,TYPE value)	\
{																									\
	size_t insert_inx = pq->start;																	\
	bool found = false;																				\
	const size_t last_inx = pq->start + pq->size;													\
	for(;insert_inx < last_inx;insert_inx++)														\
	{																								\
		if(priority <= pq->priorities[insert_inx])													\
		{																							\
			found = true;																			\
			break;																					\
		}																							\
	}																								\
																									\
	if(last_inx == pq->capacity)																	\
		priority_queue_##NAME##_expand(pq);															\
																									\
	/* move other elements to make space for the new one */											\
	if(found)																						\
	{																								\
		f32 *priprity_ptr = pq->priorities + insert_inx;											\
		TYPE *data_ptr = pq->data + insert_inx;														\
		const size_t num_elements = pq->size - insert_inx;											\
		memmove(priprity_ptr + 1,priprity_ptr,num_elements*sizeof(f32));							\
		memmove(data_ptr + 1,data_ptr,num_elements*sizeof(TYPE));									\
	}																								\
																									\
	pq->priorities[insert_inx] = priority;															\
	pq->data[insert_inx] = value;																	\
	pq->size++;																						\
}																									\
\
TYPE priority_queue_##NAME##_pop(priority_queue_##NAME *pq)											\
{																									\
	if(pq->size == 0)																				\
	{																								\
		printf("Tried removing an element from empty priority queue, exiting!\n");					\
		exit(-1);																					\
	}																								\
																									\
	const TYPE removed = pq->data[pq->start];														\
	pq->start++;																					\
	pq->size--;																						\
																									\
	/* move the queue to the start of the array to not waste space */								\
	if(pq->start != 0 && pq->start > pq->size)														\
	{																								\
		memcpy(pq->priorities,pq->data + pq->start,pq->size*sizeof(f32));							\
		memcpy(pq->data,pq->data + pq->start,pq->size*sizeof(TYPE));								\
		pq->start = 0;																				\
	}																								\
																									\
	/* if more than two thirds of allocated space is unused we shrik it	*/							\
	if(pq->capacity > 4 && pq->start + pq->size < pq->capacity/3)									\
		priority_queue_##NAME##_shrink(pq);															\
																									\
	return removed;																					\
}																									\
\
void priority_queue_##NAME##_cleanup(priority_queue_##NAME *pq)										\
{																									\
	pq->start = 0;																					\
	pq->size = 0;																					\
	pq->capacity = 0;																				\
	free(pq->priorities);																			\
	free(pq->data);																					\
}																									\
\
void priority_queue_##NAME##_reset(priority_queue_##NAME *pq)										\
{																									\
	priority_queue_##NAME##_cleanup(pq);															\
	priority_queue_##NAME##_init(pq);																\
}
