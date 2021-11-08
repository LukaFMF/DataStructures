#include <string.h>

#include "stack.h"

DEF_STACK(i32,i32)
DEF_STACK(char,char)

// evaluates an expression of positive numbers and operators(+,-,*,/) as integers, 
// there must also be () ['(' are optional] around every sub expression, 
// ex1. ((2 * 3) + ((3 - 1) - 4)), ex2. 2 * 3) + 3 - 1) - 4)) [optional '(']
i32 evaluate_expression(char *expr)
{
	stack_i32 numbers;
	stack_char operators;
	
	stack_i32_init(&numbers);
	stack_char_init(&operators);

	char *curr = expr;
	char number_buf[16];
	for(;*curr != '\0';curr++)
	{
		if(*curr == ')')
		{
			if(numbers.size == 0u)
				goto error;
			i32 right = stack_i32_pop(&numbers);

			if(operators.size == 0u)
				goto error;
			char operator = stack_char_pop(&operators);

			if(numbers.size == 0u)
				goto error;
			i32 left = stack_i32_pop(&numbers);

			i32 subexpression_value;
			switch(operator)
			{
				case '+':
					subexpression_value = left + right;
					break;
				case '-':
					subexpression_value = left - right;
					break;
				case '*':
					subexpression_value = left * right;
					break;
				case '/':
					subexpression_value = left / right;
					break;
				default:
					goto error;
			}
			stack_i32_push(&numbers,subexpression_value);
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

			stack_i32_push(&numbers,atoi(number_buf));
		}
		else if(*curr >= '*' && *curr <= '/')
			stack_char_push(&operators,*curr);
		else if(*curr == ' ' || *curr == '(')
			continue;
		else
			goto error;
	}
	
	if(numbers.size != 1u || operators.size != 0u)
		goto error;
	i32 expr_value = stack_i32_pop(&numbers);

	stack_i32_cleanup(&numbers);
	stack_char_cleanup(&operators);

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