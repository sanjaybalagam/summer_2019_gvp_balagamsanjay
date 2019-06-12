#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int numbergenerator(int reset)
{
	static int num = 0;
	if (reset == 1)
		num = 0;
	num += 1;
	return num;
}


void sort_file(FILE *ptr)
{
	
}

int partition(unsigned int *numbers, int start, int end)
{
	unsigned int temp;
	int offset = end;
	int small_ptr =start  , ptr = 0;
	for (ptr = start; ptr < end; ptr++)
	{
		if (numbers[ptr] < numbers[offset])
		{
			temp = numbers[small_ptr];
			numbers[small_ptr] = numbers[ptr];
			numbers[ptr] = temp;
			small_ptr++;
		}
	}	
	temp = numbers[small_ptr];
	numbers[small_ptr] = numbers[offset];
	numbers[offset] = temp;
	return small_ptr;
}

int qsort1(unsigned int *numbers, int start, int end)
{
	if (start < end)
	{
		int offset = partition(numbers, 0, end);
		qsort1(numbers, 0, offset - 1);
		qsort1(numbers, offset + 1, end);
	}
	return 0;
}

int write_to_file(unsigned int * number,char *files,int len)
{
	int iter;
	FILE *dest_fptr = fopen(files, "w");
	for (iter = 0; iter < len; iter++)
	{
		fprintf(dest_fptr, "%d\n", number[iter]);
	}
	fclose(dest_fptr);
	return 0;
}

int mergefile(FILE *fptr1,FILE *fptr2, FILE *fptr3)
{
	int input_1, input_2, is_input_read1,is_input_read2;
	is_input_read1 = fscanf(fptr1, "%u", &input_1);
	is_input_read2 = fscanf(fptr2, "%u", &input_2);

	while (is_input_read1 == 1 && is_input_read2 == 1)
	{
		if (input_1<input_2)
		{
			fprintf(fptr3, "%u\n", input_1);
			is_input_read1 = fscanf(fptr1, "%u", &input_1);
		}
		else
		{
			fprintf(fptr3, "%u\n", input_2);
			is_input_read2 = fscanf(fptr2, "%u", &input_2);
		}
	}
	while (is_input_read1 == 1)
	{
		fprintf(fptr3, "%u\n", input_1);
		is_input_read1 = fscanf(fptr1, "%u", &input_1);
		
	}
	while (is_input_read2 == 1)
	{
		fprintf(fptr3, "%u\n", input_2);
		is_input_read2 = fscanf(fptr2, "%u", &input_2);

	}
	fclose(fptr1);
	fclose(fptr2);
	fclose(fptr3);
	return 0;
}

int mergefiles(int num)
{
	int i = 1;
	char filename[] = "file";
	char file1[10],file2[10],file3[10];
	while (i != num)
	{
		sprintf(file1, "%s%d.txt", filename, i);
		sprintf(file2, "%s%d.txt", filename, i+1);
		
		num = numbergenerator(0);
		sprintf(file3, "%s%d.txt", filename, num);
		
		i += 2;
		FILE *fileptr1, *fileptr2, *fileptr3;
		fileptr1 = fopen(file1, "r");
		fileptr2 = fopen(file2, "r");
		fileptr3 = fopen(file3, "w");	
		mergefile(fileptr1, fileptr2, fileptr3);
	}
	return num;
}


int open_and_write_to_files(char *inputfile)
{
	unsigned int number[31000], input, is_input_read;
	int num, iter;
	FILE *fptr_in;


	fptr_in = fopen(inputfile, "r");
	if (fptr_in == NULL)
	{
		printf("NO input file");
		return 0;
	}


	char filename[] = "file";
	char files[10];

	is_input_read = fscanf(fptr_in, "%u", &input);
	while (is_input_read == 1)
	{
		for (iter = 0; iter != 31000 && is_input_read == 1; iter++)
		{
			number[iter] = input;
			is_input_read = fscanf(fptr_in, "%u", &input);

		}
		int len = iter;
		qsort1(number, 0, len - 1);
		num = numbergenerator(0);


		files[10] = sprintf(files, "%s%d.txt", filename, num);
		write_to_file(number, files, len);
	}
	return num;
}

int main()
{
	char inputfile[30];
	scanf("%s", inputfile);
	int lastfilenum=open_and_write_to_files(inputfile);
	lastfilenum=mergefiles(lastfilenum);
	printf("\nlast file is  file%d", lastfilenum);
	return 0;
}