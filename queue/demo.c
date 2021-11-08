#include "queue.h"

DEF_QUEUE(i32,i32)

i32 main(void)
{
	queue_i32 q;
	queue_init_i32(&q);

	for(u32 i = 0u;i < 1000;i++)
		queue_push_i32(&q,i);
	
	for(u32 i = 0u;i < 1000;i++)
		queue_pop_i32(&q);

	queue_cleanup_i32(&q);

	return 0;
}