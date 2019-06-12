
#define _CRT_SECURE_NO_WARNINGS

#include"excel.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"excel_cell.h"
#include"stack.h"


char *removespaces(char *str)
{
	int iter1 = 0, iter2 = 0;
	for (; str[iter1] != '\0'; iter1++)
	{
		if (str[iter1] != ' ')
		{
			str[iter2++] = str[iter1];
		}
	}
	str[iter2] = '\0';
	return str;
}

char *removespacesfrom(char *str,int occurance)
{
	
	int iter1 = 0, iter2 = 0,count=0;
	for (; str[iter1] != '\0'; iter1++)
	{
		if (str[iter1] == ' ')
		{
			count++;
		}
		if (count == occurance)
			break;
	}
	if (str[iter1] == '\0')
		return str;
	iter1++;
	//start from last position
	for (iter2=iter1; str[iter1] != '\0'; iter1++)
	{
		if (str[iter1] != ' ')
		{
			str[iter2++] = str[iter1];
		}
	}
	str[iter2] = '\0';
	return str;
}




int conatinsalpha(char * buf)
{
	int iter = 0, flag = 0;

	for (iter = 0; buf[iter] != '\0'; iter++)
	{
		if (buf[iter]<'0' || buf[iter]>'9')
		{
			flag = 1;
			break;
		}
	}
	return flag;
}

void remexistingstr(struct excel_cell *cell1)
{
	if (cell1->flag == 1)
	{
		cell1->flag = 0;
		free(cell1->exp);
		cell1->exp = NULL;
	}
}


int set_excel_cell_val(struct excel_cell *cell1,int val)
{
	cell1->val = val;
	return 0;
}

int isoperator(char str)
{
	if (str == '+' || str == '-' || str == '*' || str == '//' || str == '%')
		return 1;
	else
		return 0;
}

int presidence(char ch1,char str2)
{
	return 1;
}
char *get_postfix(char *str)
{
	char stack[60], result[60], val;
	int top = -1,iter=0,res_i=0;
	for (iter = 0; str[iter] != '\0'; iter++)
	{
		if (str[iter] == '(')
		{
			chr_stack_push(stack, &top, str[iter]);
		}
		else if (str[iter] == ')')
		{
			while ((val = chr_stack_pop(stack, &top)) != '(')
			{
				result[res_i++] = val;
				result[res_i++] = ' ';
			}
		}
		else if (isoperator(str[iter])==1)
		{
			if (presidence(top_chr_stack(stack, &top), str[iter]) == 1)
			{
				chr_stack_push(stack, &top, str[val]);
			}

		}
		else 
		{
			while (isoperator(str[iter])==0 && str[iter] != '(' && str[iter] != ')')
			{
				result[res_i++] = str[iter++];
			}
			result[res_i++] = ' ';
		}
	}
	while (top > 0)
	{
		result[res_i++] = chr_stack_pop(stack, &top);
		result[res_i++] = ' ';
	}
	return result;
}

struct cell_expression *get_expression(char *str1)
{
	int stack = 0;
	if (str1 == NULL)
		return NULL;
	char * str2 = get_postfix(str1);
	struct cell_expression *exp= (struct cell_expression*)malloc(sizeof(struct cell_expression));
	if (str2==NULL)				//no sub expressions
	{
		
	}
	return exp;
}


int set_excel_cell(struct excel_cell *cell1, char* val)
{
	remexistingstr(cell1);
	if (conatinsalpha(val) == 1)
	{
		cell1->flag = 1;
		cell1->exp = get_expression(val);
	}
	else
	{
		sscanf(val, "%d", &cell1->val);
	}
	return 0;
}

int set_excel(struct excel_cell ***excel)
{
	char *buf = strtok(NULL, " ");
	char *buf1 = strtok(NULL, " ");
	if (buf1 != NULL)
	{
		printf("incorrect command\n");
	}
	else
	{
		buf1 = strchr(buf, '=');
		int col = buf[0] - 'a',row,val;
		buf += 1;
		sscanf(buf, "%d=", &row);
		buf1 += 1;
		
		set_excel_cell(excel[row][col], buf1);
	}
	return 0;
}

char *get_excel_expression(struct excel_cell* cell1)
{
	char *str = (char *)malloc(sizeof(char)*15);
	struct cell_expression* exp = cell1->exp;
	if (exp->cell_1 == NULL)
	{
		sprintf(str, "%d", exp->data);
		return str;
	}if (exp->cell_2 == NULL)
	{
		sprintf(str,"exp: %c%d=%c%d%c%d",cell1->col+'a',cell1->row+1,exp->cell_1->col+'a',exp->cell_1->row+1,exp->exp_opertaor,exp->data);
	}
	else
	{
		sprintf(str, "exp: %c%d=%c%d%c%c%d", cell1->col + 'a', cell1->row + 1, exp->cell_1->col + 'a', exp->cell_1->row + 1, exp->exp_opertaor, exp->cell_2->col+'a',exp->cell_2->row+1);
	}
	return str;
}

int get_excel_value(struct excel_cell* cell1)
{
	struct cell_expression* exp = cell1->exp;
	if (cell1->flag == 0){
		return cell1->val;
	}
	if (exp->cell_1 == NULL)
	{
		int k = exp->data;
		cell1->flag = 0;
		cell1->exp = NULL;
		free(exp);
		return k;
	}
	exp->cell_1->val = get_excel_value(exp->cell_1);
	if (exp->cell_2 == NULL)
	{
		exp->cell_2->val = get_excel_value(exp->cell_2);
		switch (exp->exp_opertaor)
		{
		case '+':{
			cell1->val = exp->cell_1->val + exp->cell_2->val;
			break;
		}
		case '*':{
			cell1->val = exp->cell_1->val * exp->cell_2->val;
			break;
		}
		case '-':{
			cell1->val = exp->cell_1->val - exp->cell_2->val;
			break;
		}
		case '//':{
			cell1->val = exp->cell_1->val / exp->cell_2->val;
			break;
		}
		case '%':{
			cell1->val = exp->cell_1->val % exp->cell_2->val;
			break;
		}
		}
	}
	else
	{
		switch (exp->exp_opertaor)
		{
		case '+':{
			cell1->val = exp->cell_1->val + exp->data;
			break;
		}
		case '*':{
			cell1->val = exp->cell_1->val * exp->data;
			break;
		}
		case '-':{
				cell1->val = exp->cell_1->val - exp->data;
				break;
		}
		case '//':{
			cell1->val = exp->cell_1->val / exp->data;
			break;
		}
		case '%':{
			cell1->val = exp->cell_1->val % exp->cell_2->val;
			break;
		}
		}
	}
	return cell1->val;
}



struct excel_cell* get_excel(struct excel_cell ***excel, char *val)
{
	char *buf = val;
	if (val == NULL)
	{
		buf = strtok(NULL, " ");
		char *buf1 = strtok(NULL, " ");
		if (buf1 != NULL)
		{
			printf("incorrect command\n");
			return NULL;
		}
	}
	int col = buf[0] - 'a', row;
	buf += 1;
	sscanf(buf, "%d", &row);
	return excel[row - 1][col];
}

int print_excel(struct excel_cell ***excel, int rows, int cols)
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
			printf("%d   ", get_excel_value(excel[row][col]));
			if (excel[row][col]->flag == 1)
			{
				printf("%s|", get_excel_expression(excel[row][col]));
			}
		}
		printf("\n___");
		for (col = 0; col < cols; col++)
			printf("_____");
		printf("\n");
	}
	return 0;
}

char *import_excel_from_file(char *input, struct excel_cell ***excel, int rows, int cols)
{
	FILE *input_file = fopen(input, "r");
	char *buf;

	int row, col;
	char readinput[200];
	for (row = 0; row < rows; row++)
	{
		col = 0;
		fscanf(input_file, "%s", &readinput);
		buf = strtok(readinput, ",");
		while (buf != NULL)
		{
			if (conatinsalpha(buf))
				set_excel_cell_by_exp(excel[row][col++],buf);
			else
			{
					int val;
					sscanf(buf, "%d", &val);
					set_excel_cell_val(excel[row][col++], val);
			}
			buf = strtok(NULL, ",");
		}
	}
	fclose(input_file);
	return input;
}

	
char* import_excel(struct excel_cell ***excel, int rows, int cols)
{
	char *buf = strtok(NULL, " ");
	char *buf1 = strtok(NULL, " ");
	if (buf1 != NULL)
	{
		printf("incorrect command\n");
		return NULL;
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
	return import_excel_from_file(input, excel, rows, cols);
}

char* export_excel_to_file(char *output, struct excel_cell ***excel, int rows, int cols)
{
	FILE *outfile = fopen(output, "w");
	int row, col;
	for (row = 0; row < rows; row++)
	{
		col = 0;
		for (col = 1; col < cols; col++)
		{
			if (excel[row][col]->flag == 1)
				fprintf(outfile, ",%s", get_excel_expression(excel[row][col]));
			else
				fprintf(outfile, ",%s", excel[row][col]->val);
		}
		fprintf(outfile, "\n");
	}
	fclose(outfile);
	return output;
}
	
char* export_excel(struct excel_cell ***excel, int rows, int cols)
{
	char *buf = strtok(NULL, " ");
	char *buf1 = strtok(NULL, " ");
	if (buf1 != NULL)
	{
		printf("incorrect command\n");
		return NULL;
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
	export_excel_to_file(output, excel, rows, cols);
	return output;
	
}