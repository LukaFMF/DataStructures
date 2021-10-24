#include "linked_list.h"

i32 main(void)
{
	linked_list l;
	linked_list_init(&l);
	printf("Empty linked list:\n");
	linked_list_print(l);

	printf("Linked list with 3 elements:\n");
	linked_list_insert(&l,3,0u);
	linked_list_insert(&l,6,1u);
	linked_list_insert(&l,9,2u);
	linked_list_print(l);

	printf("Linked list after removing the second element:\n");
	linked_list_delete(&l,1u);
	linked_list_print(l);

	linked_list_cleanup(&l);
	// Benchmark
	// for(u32 i = 0u;i < 1000;i++)
	// {
	// 	printf("---%d---\n",i);
	// 	linked_list_init(&l);
	// 	for(u32 j = 0u;j < 1000;j++)
	// 		linked_list_insert(&l,(i32)i,l.size);
		
	// 	for(u32 j = 0u;j < 500;j++)
	// 		linked_list_delete(&l,l.size - 1);

	// 	linked_list_cleanup(&l);
	// }

	return 0;
}