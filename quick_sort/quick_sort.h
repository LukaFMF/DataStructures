#define DEF_QUICK_SORT(NAME,TYPE)																	\
void swap_##NAME(TYPE *a,TYPE *b)																	\
{																									\
	TYPE placeholder = *a;																			\
	*a = *b;																						\
	*b = placeholder;																				\
}																									\
\
void quick_sort_##NAME(TYPE *arr,size_t n,bool (*cmp)(TYPE,TYPE))									\
{																									\
	TYPE *beg = arr;																				\
	while(n > 1)																					\
	{																								\
		/* pick middle element as pivot, better for sorted arrays */								\
		TYPE *mid = beg + n/2; 																		\
		TYPE *pivot = beg + n - 1;																	\
		swap_##NAME(mid,pivot);																		\
																									\
		TYPE *swap_ptr = beg;																		\
		for(size_t i = 0;i < n - 1;i++)																\
		{																							\
			if(cmp(*(beg+i),*pivot))																\
			{																						\
				swap_##NAME(swap_ptr,beg+i);														\
				swap_ptr++;																			\
			}																						\
		}																							\
																									\
		swap_##NAME(swap_ptr,pivot); /* swap pivot into its place */								\
																									\
		const size_t left_size = swap_ptr - beg;													\
		const size_t right_size = n - left_size - 1;												\
		if(left_size > right_size)																	\
		{																							\
			quick_sort_##NAME(swap_ptr+1,right_size,cmp);											\
			/* beg stays the same */																\
			n = left_size; 																			\
		}																							\
		else																						\
		{																							\
			quick_sort_##NAME(beg,left_size,cmp);													\
			beg = swap_ptr+1;																		\
			n = right_size;																			\
		}																							\
	}																								\
}		

// void quick_sort_naive(i32 *arr,size_t n,bool (*cmp)(i32,i32))
// {
// 	if(n <= 2)
// 	{
// 		if(n == 2 && *(arr+1) < *arr)
// 			swap(arr,arr+1);
// 		return;
// 	}

// 	i32 *mid = arr + n/2;
// 	i32 *pivot = arr + n - 1;
// 	swap(mid,pivot); // pick middle element, helps when array is already sorted

// 	i32 *swap_ptr = arr;
// 	while(swap_ptr != pivot)
// 	{
// 		// move pointer forward, if needed
// 		if(cmp(*swap_ptr,*pivot))
// 		{
// 			swap_ptr++;
// 		}
// 		else
// 		{
// 			swap(swap_ptr,pivot);
// 			swap(pivot-1,swap_ptr);
// 			pivot--;
// 		}
// 	}

// 	const size_t first_size = swap_ptr - arr;
// 	quick_sort_naive(arr,first_size,cmp);
// 	quick_sort_naive(pivot + 1,n - first_size - 1,cmp);
// }