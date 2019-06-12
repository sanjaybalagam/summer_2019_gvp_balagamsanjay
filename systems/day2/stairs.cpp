#include<stdio.h>
#include<stdlib.h>

long int stairs(int steps, int size)
{
	if (steps < 0)
	{
		return 0;
	}
	if (steps == 0)
	{
		return 1;
	}
	else
	{
		int iter = 0, val = 0;
		for (iter = 1; iter <= size; iter++)
		{
			val += stairs(steps - iter, size);
		}
		return val;
	}
}



int main()
{
	printf("enter stairs count and size");
	int height, size;
	scanf_s("%d%d", &height, &size);
	printf("%ld", stairs(height, size));
	return 0;
}