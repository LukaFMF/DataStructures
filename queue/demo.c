#include "queue.h"

DEF_QUEUE(i32,i32)

i32 main(void)
{
	queue_i32 q;
	queue_i32_init(&q);

	for(size_t i = 0;i < 1000;i++)
		queue_i32_push(&q,i);
	
	for(size_t i = 0;i < 1000;i++)
		queue_i32_pop(&q);

	queue_i32_cleanup(&q);

	return 0;
}