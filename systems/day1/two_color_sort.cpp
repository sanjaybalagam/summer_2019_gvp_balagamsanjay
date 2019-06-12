#include<stdio.h>
#include<stdlib.h>

void two_color_sort(int *array, int size)
{
	int iter0=0, iter1=size-1;
	while (iter0 < iter1)
	{
		if (array[iter0] == 0)
			iter0++;
		else if (array[iter1] == 1)
			iter1--;
		else if (array[iter0] == 1 && array[iter1] == 0)
		{
			array[iter0++] = 0;
			array[iter1--] = 1;
		}
	}
}

int main()
{
	int size,iter;
	printf("enter size of array");
	scanf_s("%d", &size);
	int *array=(int *)malloc(sizeof(int)*size);
	for (iter = 0; iter < size; iter++)
	{
		scanf_s("%d", &array[iter]);
	}
	two_color_sort(array, size);
	for (iter = 0; iter < size; iter++)
	{
		printf("%d ", array[iter]);
	}
	return 0;
}