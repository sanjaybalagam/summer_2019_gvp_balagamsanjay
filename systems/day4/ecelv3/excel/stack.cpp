#include"stack.h"
#include<stdio.h>
#include<stdlib.h>


int chr_stack_push(char *stack, int *top,char val)
{
	*top += 1;
	stack[*top] = val;
	return 0;
}

int chr_stack_pop(char *stack, int *top)
{
	*top = *top - 1;
	return stack[*top+1];
}

int top_chr_stack(char *stack, int *top)
{
	return stack[*top];
}