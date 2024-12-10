#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../utils/types.h"
#include "quick_sort.h"

void print_arr(i32 *nums,size_t n)
{
	for(size_t i = 0;i < n;i++)
		printf("%d ",*(nums+i));
	printf("\n");
}

bool less_than(i32 a,i32 b)
{
	return a < b;
}

DEF_QUICK_SORT(i32,i32)
i32 main()
{
	srand(time(0));
	const size_t arr_size = 10000000; 
	// const size_t arr_size = 10; 
	i32 *numbers1 = malloc(arr_size*sizeof(i32));

	for(size_t i = 0;i < arr_size;i++)
		*(numbers1+i) = rand() % arr_size + 1;
	// print_arr(numbers,arr_size);

	// size_t num_test_nums = 11;
	// i32 test_nums[] = { 5,3,5,76,2,3,8,9,4,12,43};
	// quick_sort_naive(test_nums,num_test_nums,less_than);
	// print_arr(test_nums,num_test_nums);
	
	struct timespec start,end;
	// naive no cmp
	clock_gettime(CLOCK_MONOTONIC,&start);

	quick_sort_i32(numbers1,arr_size,less_than);

	clock_gettime(CLOCK_MONOTONIC,&end);
	printf("%.3f ms to sort %lld ints\n",(end.tv_sec - start.tv_sec) * 1000.f + (end.tv_nsec - start.tv_nsec) / 1000000.f,arr_size);

	// for(size_t i = 0;i < arr_size;i++)
	// {
	// 	if(numbers1[i] != numbers2[i])
	// 	{
	// 		printf("Difference at index %d!\n",i);
	// 		break;
	// 	}
	// }

	// print_arr(numbers,arr_size);
	free(numbers1);

	return 0;
}