#include <string.h>
#include "stack.h"

// evaluates an expression of positive numbers and operators(+,-,*,/) as integers, 
// there must also be () ['(' are optional] around every sub expression, 
// ex1. ((2 * 3) + ((3 - 1) - 4)), ex2. 2 * 3) + 3 - 1) - 4)) [optional '(']
i32 evaluate_expression(char *expr)
{
	stack numbers,operators;
	stack_init(&numbers,true);
	stack_init(&operators,true);

	char *curr = expr;
	char number_buf[16];
	for(;*curr != '\0';curr++)
	{
		if(*curr == ')')
		{
			if(stack_is_empty(&numbers))
				goto error;
			i32 right = stack_pop(&numbers);

			if(stack_is_empty(&operators))
				goto error;
			i32 operator = stack_pop(&operators);

			if(stack_is_empty(&numbers))
				goto error;
			i32 left = stack_pop(&numbers);

			i32 subexpression_value;
			switch(operator)
			{
				case (i32)'+':
					subexpression_value = left + right;
					break;
				case (i32)'-':
					subexpression_value = left - right;
					break;
				case (i32)'*':
					subexpression_value = left * right;
					break;
				case (i32)'/':
					subexpression_value = left / right;
					break;
				default:
					goto error;
			}
			stack_push(&numbers,subexpression_value);
		}
		else if(*curr >= '0' && *curr <= '9')
		{
			number_buf[0] = *curr;
			u32 number_inx = 1;

			while(*(curr + 1) >= '0' && *(curr + 1) <= '9')
			{
				curr++;
				number_buf[number_inx] = *curr;
				number_inx++;
			}
			number_buf[number_inx] = '\0';

			stack_push(&numbers,atoi(number_buf));
		}
		else if(*curr >= '*' && *curr <= '/')
			stack_push(&operators,(i32)*curr);
		else if(*curr == ' ' || *curr == '(')
			continue;
		else
			goto error;
	}
	
	if(numbers.size != 1u || operators.size != 0u)
		goto error;
	i32 expr_value = stack_pop(&numbers);

	stack_cleanup(&numbers);
	stack_cleanup(&operators);

	return expr_value;

	error:
	printf("Expression is invalid, exiting!\n");
	exit(-1);
}

i32 main(void)
{
	const u32 max_input_size = 101;

	char input[max_input_size];
	printf("Expresion to evaluate: ");
	fgets(input,max_input_size,stdin);
	input[strcspn(input,"\n")] = '\0'; // remove \n
	
	printf("%d\n",evaluate_expression(input));

	return 0;
}