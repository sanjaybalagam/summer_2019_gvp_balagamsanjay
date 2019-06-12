
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

void free_exp(struct cell_expression *exp)
{
	if (exp == NULL)
		return;
	else{
		free_exp(exp->exp1);
		free(exp);
	}
}

void remexistingstr(struct excel_cell *cell1)
{
	if (cell1->flag == 1)
	{
		free_exp(cell1->exp);
		cell1->flag = 0;
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
	if (str == '+' || str == '-' || str == '*' || str == '/' || str == '%')
		return 1;
	else
		return 0;
}

int presidence(char ch1,char ch2)
{
	if (ch1 == -1)
		return 1;
	else
	{
		if (ch1 == '(')
			return 1;
		if (ch1 == '+' || ch1 == '-')
			return 1;
		else if (ch1 == '*' || ch1 == '/')
		{
			if (ch2 == '*' || ch2 == '/')
				return 1;
			else
				return 0;
		}
	}
	return 1;
}
char *get_postfix(char *str)
{
	char stack[60], val;
	char *result=(char*)malloc(30*sizeof(char));
	str = removespaces(str);
	int top = 0,iter=0,res_i=0;
	for (iter = 0; str[iter] != '\0'; )
	{
		if (str[iter] == '(')
		{
			chr_stack_push(stack, &top, str[iter++]);
		}
		else if (str[iter] == ')')
		{
			while ((val = chr_stack_pop(stack, &top)) != '(')
			{
				result[res_i++] = val;
				result[res_i++] = ' ';
				iter++;
			}
		}
		else if (isoperator(str[iter])==1)
		{
			if (presidence(top_chr_stack(stack, &top), str[iter]) == 1)
			{
				chr_stack_push(stack, &top, str[iter++]);
			}
			else
			{
				result[res_i++] = chr_stack_pop(stack, &top);
				result[res_i++] = ' ';
			}
		}
		else 
		{
			while (isoperator(str[iter])==0 && str[iter] != '(' && str[iter] != ')' &&str[iter]!='\0')
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
	result[res_i++] = '\0';
	return result;
}

struct excel_cell *parse_str(struct excel_cell ***excel,char *str)
{
	int row;
	char col;
	sscanf(str,"%c%d", &col, &row);
	col -= 'a';
	row -= 1;
	return excel[row][col];
}

struct cell_expression *set_expression(struct excel_cell ***excel, char *str,int flag_use_strtok)
{
	if (flag_use_strtok == 0)
	{
		str = strtok(str, " ");
	}
	if (str == NULL)
		return NULL;
	struct cell_expression * exp = createexp();
	if (isoperator(str[0]) == 1)
	{
		exp->exp_opertaor = str[0];
		exp->exp1 = set_expression(excel, NULL);
	}
	else if (conatinsalpha(str) == 1)
	{
		exp->cell_1=parse_str(excel,str);
		exp->exp1 = set_expression(excel, NULL);
	}
	else{
		sscanf(str, "%d", &exp->data);
		exp->exp1=set_expression(excel,NULL);
	}
	return exp;
}

struct cell_expression *get_expression(struct excel_cell *** excel,char *str1)
{
	int stack = 0;
	if (str1 == NULL)
		return NULL;
	str1 = _strlwr(str1);
	char * str2 = get_postfix(str1);
	struct cell_expression *exp= set_expression(excel,str2);
	free(str2);
	return exp;
}


int set_excel_cell_by_exp(struct excel_cell ***excel,int row,int col,char *str)
{
	char *str2 = str;
	str2 = strchr(str, ' ');
	if (str==NULL)
	struct cell_expression *exp = set_expression(excel, str);
	excel[row][col]->exp = exp;
	excel[row][col]->flag = 1;
	return 0;
}



int exp_loop(struct excel_cell ***excel, int row, int col, struct cell_expression *exp)
{
	if (exp==NULL)
		return 0;
	if (exp->cell_1 != NULL)
	{
		if ((exp->cell_1->row == row && exp->cell_1->col == col) || exp_loop(excel,row,col,exp->cell_1->exp)==1)
			return 1;
	}
	else
	{
		while (exp != NULL)
		{
			exp = exp->exp1;
			if (exp->cell_1 != NULL)
			{
				if (exp_loop(excel, row, col, exp)==1)
					return 1;
			}
		}
	}
	return 0;
}

int set_excel_cell(struct excel_cell ***excel, char* val,int row,int col)
{
	if (conatinsalpha(val) == 1)
	{
		struct cell_expression *exp = get_expression(excel, val);
		if (exp_loop(excel, row, col,exp)==1)
		{
			printf("loop found\n");
			free_exp(exp);
			return -1;
		}
		remexistingstr(excel[row][col]);
		excel[row][col]->flag = 1;
		excel[row][col]->exp =exp;
	}
	else
	{
		remexistingstr(excel[row][col]);
		sscanf(val, "%d", &excel[row][col]->val);
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
		char col;
		int row;
		sscanf(buf, "%c%d=",&col, &row);
		col -= 'a';
		row -= 1;
		buf1 += 1;
		
		set_excel_cell(excel, buf1,row,col);
	}
	return 0;
}
 

char *get_excel_expression(struct excel_cell* cell1)
{
	char *str = (char *)malloc(sizeof(char)*70);
	struct cell_expression *temp,* exp = cell1->exp;
	temp = exp;
	sprintf(str, "%c%d= ", cell1->col + 'a', cell1->row + 1);
	while(temp !=NULL)
	{
		if (temp->cell_1 != NULL)
		{
			sprintf(str, "%s%c%d ",str, temp->cell_1->col + 'a', temp->cell_1->row + 1);
		}
		else if (temp->exp_opertaor != 0)
		{
			sprintf(str, "%s%c ", str, temp->exp_opertaor);
		}
		else
		{
			sprintf(str, "%d ", str, temp->data);
		}
		temp = temp->exp1;
	}
	return str;
}

int applyoperation(int a, int b, char op)
{
	switch (op)
	{
	case '+':{
		return b + a;
	}
	case '*':{
		return b*a;
	}
	case '-':{
		return b - a;
	}
	case '/':{
		return b / a;
	}
	case '%':{
		return b%a;
	}
	}
	return 0;
}

int excel_eval(struct excel_cell ***excel, struct cell_expression *exp)
{
	long int stack[30] = { 0 };
	int top = -1;
	while (exp != NULL)
	{
		if (exp->cell_1 != NULL)
		{
			long_stack_push(stack, &top, get_excel_value(excel, exp->cell_1->row, exp->cell_1->col));
			exp = exp->exp1;
		}
		else if(exp->exp_opertaor=='0')
		{
			long_stack_push(stack, &top, exp->data);
			exp = exp->exp1;
		}
		else
		{
			long int a=long_stack_pop(stack, &top);
			long int b = long_stack_pop(stack, &top);
			long_stack_push(stack, &top, applyoperation(a, b, exp->exp_opertaor));
			exp = exp->exp1;
		}
	}
	return long_stack_pop(stack,&top);
}

int get_excel_value(struct excel_cell*** excel,int row,int col)
{
	struct cell_expression* exp = excel[row][col]->exp;
	if (excel[row][col]->flag == 0){
		return excel[row][col]->val;
	}
	else
	{
		excel[row][col]->val=excel_eval(excel, excel[row][col]->exp);
	}
	return excel[row][col]->val;
}



int get_excel(struct excel_cell ***excel, char *val)
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
	return get_excel_value(excel,row - 1,col);
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
			printf("%d   ", get_excel_value(excel,row,col));
			if (excel[row][col]->flag == 1)
			{
				char *str= get_excel_expression(excel[row][col]);
				printf(str);
				free(str);
			}
			else
				printf("   |");
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
			{
				char *buf1 = strchr(buf, '=');
				buf1[0] = '\0';
				buf1++;
				parse_str(excel, buf);
				set_excel_cell_by_exp(excel,row,col++, buf);
			}
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
