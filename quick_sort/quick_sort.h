#include "../utils/types.h"
//#include <stdio.h>

void swap(i32 *a,i32 *b)
{
	i32 placeholder = *a;
	*a = *b;
	*b = placeholder;

}

void quick_sort_naive(i32 *arr,u32 n,bool (*cmp)(i32,i32))
{
	if(n <= 1)
		return;

	i32 *first_marker = arr;
	i32 *pivot = arr + n - 1;

	i32 swap_placeholder;
	while(first_marker != pivot)
	{
		// move pointer forward, if needed
		if(cmp(*first_marker,*pivot))
		{
			first_marker++;
		}
		// swap pivot and an element before it, if needed
		else if(!cmp(*(pivot-1),*pivot))
		{
			swap(pivot-1,pivot);
			pivot--;
		}
		// when you can' do either swap the element on marker and one before pivot
		else
		{
			swap(first_marker,pivot-1);
		}
	}

	const u32 first_size = first_marker - arr;
	quick_sort_naive(arr,first_size,cmp);
	quick_sort_naive(pivot + 1,n - first_size - 1,cmp);
}

void quick_sort(i32 *arr,u32 n,bool (*cmp)(i32,i32))
{
	if(n <= 1)
		return;

	i32 *swap_ptr = arr;
	i32 *pivot = arr + n - 1;
	for(u32 i = 0u;i < n - 1;i++)
	{
		if(cmp(*(arr+i),*pivot))
		{
			swap(swap_ptr,arr+i);
			swap_ptr++;
		}
	}

	const u32 swapped_size = swap_ptr - arr;

	swap(swap_ptr,pivot);
	quick_sort(arr,swapped_size,cmp);
	quick_sort(swap_ptr+1,n - swapped_size - 1,cmp);
}