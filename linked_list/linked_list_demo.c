#include "../utils/types.h"
#include "linked_list.h"

DEF_LINKED_LIST(i32,i32)

void linked_list_i32_print(const linked_list_i32 l)
{
	printf("HEAD ");
	link_node_i32 *curr = l.head;
	while(curr != NULL)
	{
		printf("--> %d ",curr->data);
		curr = curr->next;
	}
	printf("--> NULL\n");
}

i32 main(void)
{
	linked_list_i32 l;
	linked_list_i32_init(&l);
	printf("Empty linked list:\n");
	linked_list_i32_print(l);

	printf("Linked list with 3 elements:\n");
	linked_list_i32_insert(&l,3,0);
	linked_list_i32_insert(&l,6,1);
	linked_list_i32_insert(&l,9,2);
	linked_list_i32_print(l);

	printf("Linked list after removing the second element:\n");
	linked_list_i32_delete(&l,1);
	linked_list_i32_print(l);

	linked_list_i32_cleanup(&l);
	// Benchmark
	// for(size_t i = 0;i < 1000;i++)
	// {
	// 	printf("---%d---\n",i);
	// 	linked_list_init(&l);
	// 	for(size_t j = 0;j < 1000;j++)
	// 		linked_list_insert(&l,(i32)i,l.size);
		
	// 	for(size_t j = 0;j < 500;j++)
	// 		linked_list_delete(&l,l.size - 1);

	// 	linked_list_cleanup(&l);
	// }

	return 0;
}