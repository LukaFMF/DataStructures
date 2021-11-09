#include "priority_queue.h"

DEF_PRIORITY_QUEUE(i32,i32)
i32 main(void)
{
	priority_queue_i32 pq;
	priority_queue_i32_init(&pq);

	
	priority_queue_i32_prioritized_insert(&pq,43,4);
	priority_queue_i32_prioritized_insert(&pq,-2,2);
	priority_queue_i32_prioritized_insert(&pq,-43,1);
	priority_queue_i32_prioritized_insert(&pq,5,3);
	
	while(pq.size != 0u)
		printf("%d\n",priority_queue_i32_pop(&pq));

	priority_queue_i32_cleanup(&pq);

	return 0;
}