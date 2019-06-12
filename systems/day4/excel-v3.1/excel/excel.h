#ifndef __excel__h

#define __excel_h

#include"excel_cell.h"


int set_excel(struct excel_cell ***);
int get_excel(struct excel_cell ***, char *);
int print_excel(struct excel_cell ***,int ,int);


char* import_excel(struct excel_cell ***, int, int);
char *import_excel_from_file(char *input, struct excel_cell ***excel, int rows, int cols);


char* export_excel(struct excel_cell ***excel, int rows, int cols);
char* export_excel_to_file(char *output, struct excel_cell ***excel, int rows, int cols);

char *removespaces(char *);
char *removespacesfrom(char* str, int occurance);

int set_excel_cell_val(struct excel_cell *cell1, int val);
int set_excel_cell_by_exp(struct excel_cell ***excel, int row, int col, char *str)


struct cell_expression* get_expression(struct excel_cell ***excel,char *str);
struct cell_expression * set_expression(struct excel_cell ***excel,char *str);

int applyoperation(int a, int b, char op);

int excel_eval(struct excel_cell ***excel, struct cell_expression *exp);
char *get_excel_expression(struct excel_cell* cell1);
int set_excel_cell(struct excel_cell ***excel, char *str,int row,int col);

char *get_postfix(char *string);

int conatinsalpha(char *str);

int get_excel_value(struct excel_cell*** excel, int row, int col);

void free_exp(struct cell_expression *);

int exp_loop(struct excel_cell ***excel, int row, int col, struct cell_expression *exp);

#endif

