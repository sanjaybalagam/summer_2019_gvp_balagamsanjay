#include<stdio.h>
#ifndef __filesystem_h

#define __filesystem_h

#define MB (1024*1024)
#define SIZE (1024*1024*100)
#define BLOCK_SIZE (16*1024)
#define META_BLOCK_END 3
#define FILE_BLOCK_START (META_BLOCK_END +1)
#define FILE_BLOCKS_END 6400
#define NUM_OF_RECORDS 32



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
int write_block(int block, void *ptr_to_mem);
void *read_block(int block);
int find_free(struct metadata *meta, int num);


int debug();


//disk checking
int disk_check();
void format_disk();



//helper functionss
int str_equal1(char *str1, char *str2);


#endif