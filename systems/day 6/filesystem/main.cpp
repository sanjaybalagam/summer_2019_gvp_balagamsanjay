#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"filesystem.h"
#include<string.h>

int str_equal(char *str1, char *str2)
{
	if (str1 == NULL || str2 == NULL)
		return 0;
	int i = 0;
	for (; str1[i] != '\0' && str1[i] == str2[i]; i++)
	{
	}
	if (str1[i] == str2[i])
		return 1;
	return 0;
}

int parse_and_execute(char *diskfile,char *str)
{
	char *querry = _strlwr(str);
	char *readfile, *writefile;
	querry = strtok(querry, " ");
	if (str_equal(querry, "format") == 1)
	{
		format(diskfile);
	}
	else if (str_equal(querry, "ls") == 1)
	{
		print_files(diskfile);
	}
	else if (str_equal(querry, "copyfromhdd")==1)
	{
		readfile = strtok(NULL, " ");
		writefile = strtok(NULL, " ");
		copyfromhdd(diskfile, readfile, writefile);
	}
	else if (str_equal(querry,"copytohdd")==1)
	{
		readfile = strtok(NULL, " ");
		writefile = strtok(NULL, " ");
		insertintohdd(diskfile, readfile, writefile);
	}
	else if (str_equal(querry, "exit") == 1)
	{
		exit(0);
	}
	else{
		printf("wrong command\n");
	}
}




int main()
{
	char diskfile[20];
	printf("enter harddisk file:\n");
	scanf("%s", diskfile);
	FILE *hdd = fopen(diskfile, "r+");
	if (hdd == NULL)
	{
		printf("hdd doesnot exist");
		return 0;
	}
	fclose(hdd);
	char input[40];
	while (1)
	{
		printf(">>");
		fflush(stdin);
		scanf("%[^\n]s", input);
	parse_and_execute(diskfile,input);
	}
	return 0;
}