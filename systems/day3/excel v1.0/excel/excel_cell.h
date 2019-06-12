#ifndef __excel_h

#define __excel_h


struct cell_expression;

struct excel_cell
{
	int val;
	int flag;
	struct cell_expression;
};

typedef excel_cell cell;

struct cell_expression
{
	struct cell_expression *expression1, *expression2;
};

typedef cell_expression expression;


#endif