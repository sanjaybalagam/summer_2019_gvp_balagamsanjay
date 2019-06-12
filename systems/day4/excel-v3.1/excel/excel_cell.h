#ifndef __excel_cell_h

#define __excel_cell_h

struct excel_cell
{
	int row, col;
	int val;
	int flag;
	struct cell_expression *exp;
};

struct cell_expression{
	struct cell_expression * exp1;
	struct excel_cell *cell_1;
	char exp_opertaor;
	int data;
};

struct excel_cell *createcell();
struct excel_cell ***create_sheet(int ,int );

struct cell_expression * createexp();

#endif