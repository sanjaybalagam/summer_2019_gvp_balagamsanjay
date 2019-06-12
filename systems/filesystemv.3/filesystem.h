#include<stdio.h>
#ifndef __filesystem_h

#define __filesystem_h


struct filerecord{
	char filename[20];
	unsigned int start,blocks, length;
	//	char flag;
};

struct metadata{
	int magicnumber;
	struct filerecord records[32];
	int numberoffiles;
	char bitvector[6400];
};


//main functions
int copyfromhdd(char *readfile, char *output);
int copytohdd(char *readfile, char *writefile);
int deletefromhdd(char *filename);

struct metadata* readmetadata();
int setmetadata(struct metadata *meta);
unsigned int size_of_file(FILE *fptr);


//blocks functions
int find_free(struct metadata *meta, int num);


int debug();


//disk checking
int disk_check();
void format();
int init(char *diskname, int blocksize);


//helper functionss
int str_equal1(char *str1, char *str2);


#endif