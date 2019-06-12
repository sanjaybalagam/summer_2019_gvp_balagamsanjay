#include"stack.h"
#include<stdio.h>
#include<stdlib.h>



int chr_stack_push(char *stack, int *top,char val)
{
	stack[*top] = val;
	*top = *top + 1;
	return 0;
}

int chr_stack_pop(char *stack, int *top)
{
	if (*top == 0)
		return -1;
	*top = *top - 1;
	return stack[*top];
}

int top_chr_stack(char *stack, int *top)
{
	if (*top == 0)
		return -1;
	return stack[*top-1];
}

long  int long_stack_push(long int *stack, int *top, long int val)
{
	*top = *top + 1;
	stack[*top] = val;
	return 0;
}

long int long_stack_pop(long int *stack, int *top)
{
	if (*top == -1)
		return -1;
	*top = *top - 1;
	return stack[*(top)+1];
}

long int long_stack_top(long int *stack, int *top)
{
	if (*top == -1)
		return -1;
	return stack[*top - 1];
}
