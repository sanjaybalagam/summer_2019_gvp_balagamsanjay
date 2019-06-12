#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>


char* reducestr(char *string)
{
	int read, count = 1,write=0,itercount;
	char count1[10];
	for (read = 0; string[read] != '\0';read++)
	{
		count = 1;
		string[write++] = string[read];
		while (string[read] == string[read + 1])
		{
			read++;
			count++;
		}
		if (count!= 1)
		{
			sprintf(count1, "%d", count);
			for (itercount = 0; count1[itercount] != '\0';itercount++)
				string[write++] =count1[itercount];
		}
	}
	string[write] = '\0';
	return string;

}

int main()
{
	
	int num,num0;
	printf("enter number of strings");
	scanf_s("%d", &num);
	fflush(stdin);
	char string[200];
	
	for (num0 = 0; num0 < num; num0++)
	{
		scanf("%[^\n]s", string);
		fflush(stdin);
		printf("%s\n", reducestr(string));
	}
	
	return 0;
}