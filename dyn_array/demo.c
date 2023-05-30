#include "dyn_array.h"

#include <time.h>

DEF_DYN_ARRAY(i32,i32)

void print_arr(const struct dyn_array_i32 *a)
{
	for(size_t i = 0;i < a->size;i++)
		printf("%d ",a->data[i]);
	printf("-- %llu\n",a->capacity);
}

i32 main(void)
{
	srand(time(0));
	struct dyn_array_i32 a;
	dyn_array_i32_init(&a,0);

	for(size_t n = 0;n < 100;n++)
	{
		for(size_t i = 0;i < 100;i++)
			dyn_array_i32_insert(&a,rand() % (a.size + 1),rand() % 100 + 1);

		//print_arr(&a);
		dyn_array_i32_reset(&a,0);
	}

	return 0;
}