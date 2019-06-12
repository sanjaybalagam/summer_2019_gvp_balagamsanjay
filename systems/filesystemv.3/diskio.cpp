#define _CRT_SECURE_NO_WARNINGS
#include"diskio.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char DISK[15];
static FILE *hdd = fopen("hardDisk.hdd","rb+");
static unsigned int BLOCK_SIZE=16*1024;
static unsigned int NUMBER_OF_BLOCKS=6400;

int write_block(int block, void *ptr_to_mem)
{
	if (hdd == NULL)		
	{
		printf("file not initialized or no file mounted\n");
		return -1;
	}						
	fseek(hdd, block* (BLOCK_SIZE), SEEK_SET);
	fwrite(ptr_to_mem, BLOCK_SIZE, 1, hdd);
	return 0;
}

void *read_block(int block)
{
	if (hdd == NULL)
	{
		printf("file not initialized or no file mounted\n");
		return NULL;
	}
	void *mem = malloc(BLOCK_SIZE);
	fseek(hdd, block *BLOCK_SIZE, SEEK_SET);
	fread(mem, BLOCK_SIZE, 1, hdd);
	return mem;
}



unsigned int init_disk(char *disk,int blocksize)
{
	if (disk == NULL && blocksize == 0)		//(NULL,0)  unmount
	{
		fclose(hdd);
		DISK[0] = '\0';
		return 0;
	}										// (NULL,size) reinitialise disk
	if (hdd	!= NULL)
	{
		strcpy(DISK, disk);
		hdd = fopen(disk, "rb+");
		if (hdd == NULL)
		{
			printf("hardisk file doesnt exist\n");
			return -1;
		}
	}
	else
	{

	}
	fseek(hdd, 0, SEEK_END);
	NUMBER_OF_BLOCKS=ftell(hdd);
	BLOCK_SIZE = blocksize;
	return NUMBER_OF_BLOCKS/BLOCK_SIZE;
}