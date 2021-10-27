#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "quick_sort.h"

void print_arr(i32 *nums,u32 n)
{
	for(u32 i = 0u;i < n;i++)
		printf("%d ",*(nums+i));
	printf("\n");
}

bool less_than_eq(i32 a,i32 b)
{
	return a < b;
}

i32 main()
{
	srand(time(0));
	const u32 arr_size = 100000u; 
	i32 *numbers = malloc(arr_size*sizeof(i32));

	for(u32 i = 0u;i < arr_size;i++)
		*(numbers+i) = rand() % 100 + 1;
	//print_arr(numbers,arr_size);

	struct timespec start,end;
	clock_gettime(CLOCK_MONOTONIC,&start);

	quick_sort(numbers,arr_size,less_than_eq);

	clock_gettime(CLOCK_MONOTONIC,&end);
	printf("%.3f ms to sort %d ints\n",(end.tv_sec - start.tv_sec) * 1000.f + (end.tv_nsec - start.tv_nsec) / 1000000.f,arr_size);

	//print_arr(numbers,arr_size);
	return 0;
}