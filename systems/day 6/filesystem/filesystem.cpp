#define _CRT_SECURE_NO_WARNINGS
#include"filesystem.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MB 1024*1024
#define SIZE MB * 100

unsigned int size_of_file(FILE *fptr)
{
	if (fptr == NULL)
		return -1;
	fseek(fptr, 0, SEEK_END);
	unsigned int k=ftell(fptr);
	fseek(fptr, 0, SEEK_SET);
	return k;
}

int readmetadata(FILE *ptrhdd, unsigned int *numberofrecords, unsigned int *available)
{
	fread(numberofrecords, 4, 1, ptrhdd);
	fread(available, 4, 1, ptrhdd);
	return 0;
}

int writedata(FILE *readptr, FILE *writeptr, int offset, int sizeoffile)
{
	char *data = (char *)malloc(sizeoffile);
	fread(data, 1, sizeoffile, readptr);
	fwrite(data, 1, sizeoffile, writeptr);
	free(data);
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



void print_files(char *diskfile)
{
	printf("printing files..\n");
	FILE *hdd = fopen(diskfile, "rb");
	if (hdd == NULL)
		return;
	unsigned int number_of_records, available, record;
	fread(&number_of_records, 4, 1, hdd);
	fread(&available, 4, 1, hdd);

	struct filerecord *precord = (struct filerecord*)malloc(sizeof(struct filerecord) * 1);
	printf("filenames\t size in bytes\n");
	for (record = 0; record < number_of_records; record++)
	{
		fread(precord, sizeof(struct filerecord), 1, hdd);
		printf("%s\t\t\t %u\n", precord->filename, precord->length);
	}
	printf("\nfininshed displaying..\n");
	fclose(hdd);
}


int copyfromhdd(char *diskfile,char *readfile, char *output)
{
	printf("copying from hdd..\n");
	FILE *hdd = fopen(diskfile, "rb");
	if (hdd == NULL)
		return -1;
	unsigned int number_of_records, available,record;
	fread(&number_of_records, 4, 1, hdd);
	fread(&available, 4, 1, hdd);
	
	struct filerecord *precord = (struct filerecord*)malloc(sizeof(struct filerecord));
	char flag = 0;
	for (record = 0; record < number_of_records; record++)
	{
		fread(precord, sizeof(struct filerecord), 1, hdd);
		if (str_equal1(precord->filename, readfile))
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		printf("no file found");
		return -1;
	}
	FILE *write = fopen(output, "wb");
	if (write == NULL)
	{
		return -1;
	}
	fseek(hdd, precord->offset, SEEK_SET);
	char *a = (char *)malloc((precord->length)*sizeof(char));
	fread(a, 1, precord->length,hdd);
	fwrite(a, 1, precord->length, write);
	
	fclose(hdd);
	fclose(write);
	printf("\ncopied from hdd\n");
	return 0;

}

void format(char *diskfile)
{
	printf("formatting hdd..");
	FILE *hdd = fopen(diskfile, "rb+");
	if (hdd == NULL)
	{
		printf("\nno harddisk");
		return;
	}
	int num = 0;
	fseek(hdd, 0, SEEK_END);
	int k = ftell(hdd);
	fseek(hdd, 0, SEEK_SET);
	while (k>0)
	{
		fwrite(&num, sizeof(int), 1, hdd);
		k -= 4;
	}
	fclose(hdd);
	printf("\nhdd formatted\n");
}


int insertintohdd(char *diskfile,char *readfile, char *writefile)
{
	//reading metadata
	unsigned int number_of_records, available;
	FILE *hdd=fopen(diskfile, "rb+");
	if (hdd == NULL)
		return -1;
	readmetadata(hdd,&number_of_records, &available);
	if (number_of_records == 0)
	{
		available = SIZE;
	}
	else
	{
		fread(&available, 4, 1, hdd);
	}

	//ends of file  ; get size function write it
	FILE *readptr = fopen(readfile, "rb+");
	if (readptr == NULL)
		return -1;
	unsigned int sizeoffile = size_of_file(readptr);
	
	//reading all records
	struct filerecord *precord = (struct filerecord*)malloc(sizeof(struct filerecord));
	unsigned int reco_i;
	int used = 0;
	fseek(hdd, 7, SEEK_SET);
	for (reco_i = 0; reco_i < number_of_records; reco_i++)
	{
		fread(precord, sizeof(struct filerecord), 1, hdd);
		used+= precord->length ;
	}
	unsigned int meta_end_pos = ftell(hdd);

	//seeing if it fits
	available -= used;
	available -= (number_of_records*sizeof(struct filerecord));
	if (available < sizeoffile)
	{
		printf("cannot fit file into hdd");
		return -1;
	}


	// writting to metadata
	strcpy(precord->filename, readfile);
	precord->length = sizeoffile;
	fseek(hdd, -(int)(used+sizeoffile), SEEK_END);
	precord->offset=ftell(hdd);
	
	writedata(readptr, hdd, precord->offset, sizeoffile);
	
	fseek(hdd, meta_end_pos, SEEK_SET);
	fwrite(precord, sizeof(struct filerecord), 1, hdd);
	
	//updating numeber of records and avaiable
	fseek(hdd, 0, SEEK_SET);
	number_of_records += 1;
	fwrite(&number_of_records, 4, 1, hdd);
	available -= (sizeoffile + sizeof(struct filerecord));
	fwrite(&available, 4, 1, hdd);

	fclose(hdd);
	fclose(readptr);

	free(precord);
	printf("inserted into hdd\n");
	return 0;
}