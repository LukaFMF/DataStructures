
#include "priority_queue.h"

i32 main(void)
{
	queue q;
	queue_init(&q,true);

	for(u32 i = 0u;i < 2000;i++)
		queue_push(&q,i);
	
	for(u32 i = 0u;i < 200;i++)
		printf("%d\n",queue_pop(&q));

	printf("%d\n",q.capacity);

	queue_cleanup(&q);
}