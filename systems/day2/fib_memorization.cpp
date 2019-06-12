#include<stdio.h>
#include<stdlib.h>

long long int fibonacci(int k, int *array)
{

	if (k <= 0)
		return 0;
	else if(k == 1)
	{
		return 1;
	}
	else
	{
		if (array[k] != 0)
			return array[k];
		else
		{
			array[k] = fibonacci(k - 1, array) + fibonacci(k - 2, array);
			return array[k];
		}
	}
}

int main()
{
	int len;
	scanf_s("%d", &len);
	int *array = (int*)calloc(len+1,sizeof(int));
	array[0] = 0;
	array[1] = 1;
	printf("%d", fibonacci(len-1, array));
	return 0;
}