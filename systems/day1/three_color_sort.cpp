#include<stdio.h>
#include<stdlib.h>

void three_color_sort(int *array, int size)
{
	int ptr0=0, ptr1=0, ptr2=size-1,swap;
	while (ptr1 <= ptr2)
	{
		if (array[ptr1] == 0)
		{
			array[ptr1++] = array[ptr0];
			array[ptr0++] = 0;
		}
		else if (array[ptr1] == 2)
		{
			array[ptr1] = array[ptr2];
			array[ptr2--] = 2;
		}
		else
			ptr1++;
	}
}

int main()
{
	int size, iter;
	printf("enter size of array");
	scanf_s("%d", &size);
	int *array = (int *)malloc(sizeof(int)*size);
	for (iter = 0; iter < size; iter++)
	{
		scanf_s("%d", &array[iter]);
	}
	three_color_sort(array, size);
	for (iter = 0; iter < size; iter++)
	{
		printf("%d ", array[iter]);
	}
	return 0;
}