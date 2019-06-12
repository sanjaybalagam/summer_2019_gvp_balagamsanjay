#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"excel.h"
#include<string.h>
#include<stdlib.h>

int main()
{
	int **excel= (int**)malloc(sizeof(int*)*10);
	int iter = 0;
	for (iter = 0; iter < 10; iter++)
	{
		excel[iter] = (int*)calloc(10, sizeof(int*));
	}
	char input[200],*buf;
	while(1)
	{
		printf(">");
		fflush(stdin);
		scanf("%[^\n]s", &input);

		buf = _strlwr(input);
		buf = strtok(buf, " ");
		
		if (strcmp(buf, "exit") == 0){
			return 0;
		}
		else{
			if (strcmp(buf, "set") == 0)
			{
				set_excel(excel);
			}
			else if (strcmp(buf, "get") == 0)
			{
				get_excel(excel);
			}
			else if (strcmp(buf, "print") == 0)
			{
				if (print_excel(excel, 10, 10) == -1)
				{
					printf("wrong command\n");
				}
			}
			else if (strcmp(buf, "export") == 0)
			{
				export_excel(excel,10,10);
			}
			else if (strcmp(buf, "import") == 0)
			{
				import_excel(excel,10,10);
				
			}
			else
			{
				printf("incorrect command\n");
			}
		}
	}
	return 0;
}