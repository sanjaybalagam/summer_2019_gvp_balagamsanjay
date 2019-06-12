#define _CRT_SECURE_NO_WARNINGS
#include"excel.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int set_excel(int **excel)
{
	char *buf = strtok(NULL, " ");
	char *buf1 = strtok(NULL, " ");
	if (buf1 != NULL)
	{
		printf("incorrect command\n");
	}
	else
	{
		int col = buf[0] - 'a',row,val;
		buf += 1;
		sscanf(buf, "%d=%d", &row,&val);
		excel[row-1][col] = val;
	}
	return 0;
}

int get_excel(int **excel)
{
	char *buf;
	buf = strtok(NULL, " ");
	char *buf1 = strtok(NULL, " ");
	if (buf1 != NULL)
	{
		printf("incorrect command\n");
		return -1;
	}
	int col = buf[0] - 'a',row;
	buf += 1;
	sscanf(buf, "%d", &row);
	printf("%d\n",excel[row-1][col]);
	return excel[row - 1][col];
}


int print_excel(int **excel, int rows,int cols)
{
	char *buf = strtok(NULL, "");
	if (buf != NULL)
		return -1;
	int row, col;
	printf("   ");
	for (col = 0; col < cols; col++)
		printf("%c   |", col + 'A');
	printf("\n");
	for (row = 0; row < rows; row++)
	{
		printf("%d  ", row + 1);
		for (col = 0; col < cols; col++)
		{
			printf("%d   |", excel[row][col]);
		}
		printf("\n___");
		for (col = 0; col < cols; col++)
			printf("_____");
		printf("\n");
	}
	return 0;
}

int import_excel(int **excel, int rows, int cols)
{

	char *buf = strtok(NULL, " ");
	char *buf1 = strtok(NULL, " ");
	if (buf1 != NULL)
	{
		printf("incorrect command\n");
		return -1;
	}
	char *input = (char *)malloc(sizeof(buf) + 5);
	int iter;
	for (iter = 0; buf[iter] != '\0'; iter++)
	{
		input[iter] = buf[iter];
	}
	input[iter++] = '.';
	input[iter++] = 'c';
	input[iter++] = 's';
	input[iter++] = 'v';
	input[iter++] = '\0';

	FILE *input_file = fopen(input, "r");
	
	int row, col;
	char readinput[200];
	for (row = 0; row < rows; row++)
	{
		col = 0;
		fscanf(input_file, "%s", &readinput);
		buf = strtok(readinput,",");
		while (buf != NULL)
		{
			sscanf(buf, "%d", &excel[row][col++]);
			buf = strtok(NULL, ",");
		}
	}
	fclose(input_file);
	return 0;
}

int export_excel(int **excel, int rows, int cols)
{
	char *buf = strtok(NULL, " ");
	char *buf1 = strtok(NULL, " ");
	if (buf1 != NULL)
	{
		printf("incorrect command\n");
		return -1;
	}
	char *output = (char *)malloc(sizeof(buf) + 5);
	int iter;
	for (iter = 0; buf[iter] != '\0'; iter++)
	{
		output[iter] = buf[iter];
	}
	output[iter++] = '.';
	output[iter++] = 'c';
	output[iter++] = 's';
	output[iter++] = 'v';

	FILE *outfile = fopen(output, "w");

	int row, col;
	for (row = 0; row < rows; row++)
	{
		col = 0;
		fprintf(outfile, "%d",excel[row][col] );
		for (col = 1; col < cols; col++)
		{
			fprintf(outfile, ",%d", excel[row][col]);
		}
		fprintf(outfile, "\n");
	}
	fclose(outfile);
	return 0;
}


