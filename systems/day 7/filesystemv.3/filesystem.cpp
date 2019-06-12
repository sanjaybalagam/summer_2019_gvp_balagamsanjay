#define _CRT_SECURE_NO_WARNINGS
#include"filesystem.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DISK "hardDisk.hdd"

int write_block(int block,void *ptr_to_mem)
{
	FILE *fptr = fopen(DISK, "rb+");
	if (fptr == NULL)
	{
		printf("cannot open file");
		return -1;
	}
	fseek(fptr, block* (BLOCK_SIZE), SEEK_SET);
	fwrite(ptr_to_mem, BLOCK_SIZE, 1, fptr);
	fclose(fptr);
	return 0;
}

void *read_block(int block)
{
	FILE *hdd = fopen(DISK, "rb+");
	if (hdd == NULL)
	{
		printf("cannot open file");
		return NULL;
	}
	void *mem = malloc(BLOCK_SIZE);
	fseek(hdd, block *BLOCK_SIZE, SEEK_SET);
	fread(mem, BLOCK_SIZE, 1, hdd);
	fclose(hdd);
	return mem;
}

unsigned int size_of_file(FILE *fptr)
{
	if (fptr == NULL)
		return -1;
	fseek(fptr, 0, SEEK_END);
	unsigned int k=ftell(fptr);
	fseek(fptr, 0, SEEK_SET);
	return k;
}

struct metadata* readmetadata()
{
	void *read = read_block(0);
	struct metadata *meta = (struct metadata*)malloc(sizeof(struct metadata));
	memcpy(meta, read, sizeof(struct metadata));
	free(read);
	return meta;
}

int setmetadata(struct metadata *meta)
{
	void *write=malloc(sizeof(struct metadata));
	memcpy(write,meta, sizeof(struct metadata));
	write_block(0, write);
	free(write);
	return 0;
}



void format_disk()
{
	printf("formatting hdd..\n");
	struct metadata *meta = (struct metadata*)malloc(sizeof(metadata));
	memset(meta, 0, sizeof(struct metadata));
	meta->bitvector[0] = 1;
	meta->magicnumber = 0x444E524D;
	void *str = malloc(BLOCK_SIZE);
	memcpy(str, meta, sizeof(struct metadata));
	write_block(0, str);
	printf("formatiing completed\n");
}


int disk_check()
{
	struct metadata *meta = readmetadata();
	if (meta->magicnumber != 0x444E524D)
	{
		printf("disk is corrupted!\n Do you want to format[y/n]?");
		char choice;
		scanf("%c", &choice);
		if (choice == 'y' || choice == 'Y')
		{
			format_disk();
			free(meta);
			return 0;
		}
		free(meta);
		return -1;
	}
	free(meta);
	return 0;
}

int str_equal1(char *str1, char *str2)
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


int deletefromhdd(char *filename)
{
	struct metadata *meta = readmetadata();
	int i = 0,flag=0;
	printf("deleting files from hdd..\n");
	for (i = 0; i < meta->numberoffiles; i++)
	{
		if (str_equal1(filename, meta->records[i].filename) == 1)
		{
			flag = 1;
			int start = meta->records[i].start, bits = meta->records[i].start, end = meta->records[i].blocks;
			for (; bits-start < end; bits++)
			{
				meta->bitvector[bits] = 0;
			}
			memcpy(&(meta->records[i]), &(meta->records[meta->numberoffiles - 1]), sizeof(struct filerecord));
			meta->numberoffiles -= 1;
			break;			
		}
	}
	if (flag == 0)
	{
		printf("no files found %s\n", filename);
		return -1;
	}
	else
	{
		setmetadata(meta);
		printf("files deleted from hdd..\n");
	}
	free(meta);
	return 0;
}

int copyfromhdd(char *readfile, char *output)
{
	printf("copying from hdd..\n");
	struct metadata *meta=readmetadata();
	FILE *outptr = fopen(output, "wb");
	if (outptr == NULL)
	{
		printf("cannot open file");
		return -1;
	}
	int i = 0,flag=0;
	for (i = 0; i < meta->numberoffiles; i++)
	{
		if (str_equal1(readfile, meta->records[i].filename) == 1)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		printf("\nno file found %s\n", readfile);
		return -1;
	}
	else
	{
		int j=0, start = meta->records[i].start, no_of_blocks = meta->records[i].blocks;
		int length = meta->records[i].length;
		int last_block = start + no_of_blocks;
		void *str;
		for (j = start; j < last_block-1; j++)
		{
			str=read_block(j);
			fwrite(str, BLOCK_SIZE, 1, outptr);
			free(str);
			str = NULL;
		}
		int size = length%BLOCK_SIZE;
		if (size == 0)
		{
			size = BLOCK_SIZE;
		}
		str = read_block(j);
		fwrite(str, size, 1, outptr);

		
		fclose(outptr);
		free(str);
	}
	printf("\ncopied from hdd\n");
	return 0;

}


int debug()
{

	struct metadata * meta = readmetadata();
	printf("magic number\t no.of.files\n");
	printf("%u\t", meta->magicnumber);
	printf("%d\n", meta->numberoffiles);
	int i = 0;
	printf("printing files...\n");
	for (; i < meta->numberoffiles; i++)
	{
		printf("%s\t %d \t%d\t %d\n", meta->records[i].filename, meta->records[i].start,meta->records[i].blocks, meta->records[i].length);
	}
	printf("files printed...\n");
	return 0;
}




int find_free(struct metadata *meta,int num)
{
	int i, j = 0,k;
	for (i = 1; i + num < FILE_BLOCKS_END; i=j+1)
	{
		for (j = i; j <i+ num; j++)
		{
			k = meta->bitvector[j];
			if ( k== 1)
				break;
		}
		if (j == i+num)
			return i;
	}
	return -1;
}

int copytohdd(char *readfile, char *writefile)
{
	//reading metadata
	struct metadata *meta = readmetadata();
	

	//ends of file  ; get size function write it
	FILE *readptr = fopen(readfile, "rb+");
	if (readptr == NULL)
		return -1;
	unsigned int sizeoffile = size_of_file(readptr);
	
	
	//seeing if it fits
	int number_of_blocks= (sizeoffile/BLOCK_SIZE)+(!!(sizeoffile%BLOCK_SIZE));
	int start = find_free(meta, number_of_blocks);
	if (start == -1)
	{
		printf("no free space found");
		return -1;
	}
	
	
	//writting  to metadata
	int lastrecord = meta->numberoffiles;
	strcpy(meta->records[lastrecord].filename, writefile);
	meta->records[lastrecord].start = start;
	meta->records[lastrecord].blocks = number_of_blocks;
	meta->records[lastrecord].length = sizeoffile;
	meta->numberoffiles += 1;

	int i;
	void *buffer = malloc(BLOCK_SIZE);
	
	
	//writting contents to file
	for (i = start; i-start <number_of_blocks; i++)
	{
		fread(buffer, BLOCK_SIZE, 1, readptr);
		write_block(i,buffer);
		meta->bitvector[i] = 1;
	}
	
	//writting metadata to file
	setmetadata(meta);
	
	
	//closing files and buffers
	fclose(readptr);
	free(meta);
	printf("inserted into hdd\n");
	return 0;
}