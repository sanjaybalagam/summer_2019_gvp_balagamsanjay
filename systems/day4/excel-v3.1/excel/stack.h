#ifndef __stack_h


#define __stack_h

#include<stdio.h>
#include<stdlib.h>

int chr_stack_push(char *, int *top,char val);
int chr_stack_pop(char *, int *top);
int top_chr_stack(char *, int *top);



long int long_stack_push(long int *stack, int *top, long int val);
long int long_stack_pop(long int *stack, int *top);
long int long_stack_top(long int *stack, int *top);



#endif