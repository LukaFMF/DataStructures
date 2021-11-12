#include "dyn_array.h"

#include <time.h>

DEF_DYN_ARRAY(i32,i32)

void print_arr(const struct dyn_array_i32 *a)
{
	for(u32 i = 0u;i < a->size;i++)
		printf("%d ",a->data[i]);
	printf("-- %d\n",a->capacity);
}

i32 main(void)
{
	srand(time(0));
	struct dyn_array_i32 a;
	dyn_array_i32_init(&a,0u);

	for(u32 n = 0;n < 100;n++)
	{
		for(u32 i = 0;i < 100;i++)
			dyn_array_i32_insert(&a,rand() % (a.size + 1),rand() % 100 + 1);

		//print_arr(&a);
		dyn_array_i32_reset(&a,0);
	}

	return 0;
}