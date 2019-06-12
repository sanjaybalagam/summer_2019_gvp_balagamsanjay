#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>


int ** transpose(int  **mat, int rows, int cols)
{
	int **trans,row,col;
	trans= (int**)malloc(sizeof(int *)*cols);
	for (row = 0; row < cols; row++)
	{
		trans[row] = (int *)malloc(sizeof(int)*rows);
	}
	for (row = 0; row < cols ; row++)
	{
		for (col = 0; col < rows; col++)
			trans[row][col] = mat[col][row];
	}
	return trans;
}

int main(void)
{
	int rows, cols;
	printf("enter rows and columns\n");
	scanf_s("%d%d", &rows, &cols);
	printf("enter values\n");
	
	int row,col;
	
	int **matrix = (int **)malloc(sizeof(int *) * rows);	
	for (row = 0; row < rows; row++)
	{
		matrix[row] = (int *)malloc(sizeof(int) * cols);
		for (col = 0; col < cols; col++)
		{
			scanf("%d",&matrix[row][col]);
		}
	}
	int ** transmat = transpose(matrix, rows, cols);

	//now rows= n(cols),,, cols=n(rows)...
	for (row = 0; row < cols; row++)
	{
		for (col = 0; col < rows; col++)
			printf("%d ", transmat[row][col]);
		printf("\n");
	}

	return 0;
}

