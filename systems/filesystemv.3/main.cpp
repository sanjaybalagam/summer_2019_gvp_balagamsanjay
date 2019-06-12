#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"filesystem.h"
#include<string.h>
#include"diskio.h"

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

int parse_and_execute(char *str)
{
	char *querry = _strlwr(str);
	char *readfile, *writefile=NULL,*disk=NULL,*size=NULL;
	querry = strtok(querry, " ");
	//unsigned int size_int;
	/*
	if (str_equal(querry, "mount") == 1)
	{
		disk = strtok(NULL, " ");
		size = strtok(NULL, " ");
		sscanf(size,"%u", &size_int);
		init(disk, size_int);
	}
	else if (str_equal(querry,"unmount" ) == 1)
	{
		init(NULL, 0);
	}
	else if (str_equal(querry, "read") == 1)
	{

		readfile = strtok(NULL, " ");
		sscanf(readfile,"%d", &size_int);
		read_block(size_int);
	}
	else if (str_equal(querry, "write") == 1)
	{
		readfile = strtok(NULL, " ");
		(readfile, "%d", &size_int);
		char *writefile=(char *)read_block(size_int);
		printf("%s", writefile);
	}
	else if (str_equal(querry, "exit") == 1)
	{
		exit(0);
	}
	else
	{
		printf("wrong command\n");
	}
	*/




	if (str_equal(querry, "format") == 1)
	{
		format();
	}
	else if (str_equal(querry, "ls") == 1||str_equal(querry,"debug"))
	{
		debug();
	}
	else if (str_equal(querry, "copyfromfs")==1)
	{
		readfile = strtok(NULL, " ");
		writefile = strtok(NULL, " ");
		copyfromhdd(readfile, writefile);
	}
	else if (str_equal(querry,"copytofs")==1)
	{
		readfile = strtok(NULL, " ");
		writefile = strtok(NULL, " ");
		copytohdd(readfile, writefile);
	}
	else if (str_equal(querry, "del") == 1)
	{
		readfile = strtok(NULL, " ");
		deletefromhdd(readfile);
	}
	else if (str_equal(querry, "exit") == 1)
	{
		exit(0);
	}
	else{
		printf("wrong command\n");
	}
	return 0;
}


int main()
{	
	
	//disk_check();
	
	
	
	char input[40];
	while (1)
	{
		printf("\n>>");
		fflush(stdin);
		scanf("%[^\n]s", input);
	parse_and_execute(input);
	}
	return 0;
}

