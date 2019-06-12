#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"excel.h"
#include<string.h>
#include<stdlib.h>
#include"excel_cell.h"




int main()
{

	char st[100];
	while (1)
	{
		gets(st);
		puts(get_postfix(st));
	}
	/*struct excel_cell ***excel = create_sheet(10, 10);
	char input[200],*buf=NULL;
	char* filename=NULL;
	while(1)
	{
		printf(">");
		fflush(stdin);
		scanf("%[^\n]s", &input);

		buf = _strlwr(input);
		
		//buf=removespacesfrom(buf, 1);
		 
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
				struct excel_cell * temp=get_excel(excel,NULL);
				if (temp != NULL)
					if (temp->flag == 0)
						printf("%d\n",temp->val);
					else
						printf("%s\n",temp->exp);
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
				if (filename == NULL)
				{
					char *filename1 = export_excel(excel, 10, 10);
					if (filename1 != NULL)
					{
						free(filename);
						filename = filename1;
						filename1 = NULL;
					}
				}
				else
				{
					filename = export_excel_to_file(filename, excel, 10, 10);
				}
			}
			else if (strcmp(buf, "import") == 0)
			{
				if (filename == NULL)
				{
					char *filename1 = import_excel(excel, 10, 10);
					if (filename1 != NULL)
					{
						free(filename);
						filename = filename1;
						filename1 = NULL;
					}
				}
				else
				{
					filename = import_excel_from_file(filename,excel, 10, 10);
				}
			}
			else if (strcmp(buf, "exit") == 0)
			{
				exit(0);
			}
			else if (strcmp(buf, "save") == 0)
			{
				if (filename == NULL)
				{
					printf("no file to save\n");
				}
				else
				{
					export_excel_to_file(filename, excel, 10, 10);
				}
			}
			else
			{
				printf("incorrect command\n");
			}
		}
	}*/
	return 0;
}

