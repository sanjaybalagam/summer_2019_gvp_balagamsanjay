#include<stdio.h>
#include"excel_cell.h"
#include<stdlib.h>

struct cell_expression *createexp()
{
	struct cell_expression *exp = (struct cell_expression*)malloc(sizeof(struct cell_expression));
	exp->exp1 = NULL;
	exp->cell_1 = NULL;
	exp->data = 0;
	exp->exp_opertaor = '0';
	return exp;
}

struct excel_cell * createcell()
{
	struct excel_cell* new_cell = (struct excel_cell*)malloc(sizeof(struct excel_cell));
	new_cell->val = 0;
	new_cell->flag = 0;
	new_cell->exp = NULL;
	return new_cell;
}

struct excel_cell *** create_sheet(int rows,int cols)
{
	struct excel_cell *** excel = (struct excel_cell***)malloc(sizeof(struct excel_cell**) * rows);
	int row = 0, col = 0;
	for (row = 0; row < rows; row++)
	{
		excel[row] = (struct excel_cell**)malloc(cols * sizeof(struct excel_cell*));
		for (col = 0; col < cols; col++)
		{
			excel[row][col] = createcell();
			excel[row][col]->row = row;
			excel[row][col]->col = col;

		}
	}
	return excel;
}
