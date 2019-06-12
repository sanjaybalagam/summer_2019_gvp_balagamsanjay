#include<stdio.h>
#include<stdlib.h>

long long int sum_array(int *array, int size)
{
	return --size >= 0 ? (array[size] + sum_array(array, size)) : 0;
}


int main()
{
	int len;
	scanf_s("%d", &len);
	int *array = (int*)malloc(sizeof(int)*len);
	int iter;
	for (iter = 0; iter < len; iter++)
		scanf_s("%d", &array[iter]);
	printf("%d", sum_array(array, len));
	return 0;
}