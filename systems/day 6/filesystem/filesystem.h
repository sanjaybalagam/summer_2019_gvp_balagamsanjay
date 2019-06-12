#include<stdio.h>
#ifndef __filesystem_h

#define __filesystem_h


struct filerecord{
	char filename[16];
	unsigned int offset, length;
	//	char flag;
};

//main functions
void print_files(char *diskfile);
int copyfromhdd(char *diskfile,char *readfile, char *output);
void format(char *diskfile);
int insertintohdd(char *diskfile,char *readfile, char *writefile);

int readmetadata(FILE *ptrhdd, unsigned int *numberofrecords, unsigned int *available);
unsigned int size_of_file(FILE *fptr);
int writedata(FILE *readptr, FILE *writeptr, int offset, int sizeoffile);


//helper functionss
int str_equal1(char *str1, char *str2);


#endif