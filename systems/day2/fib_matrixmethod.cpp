#include<stdio.h>
#include<stdlib.h>

void an(int array[2][2], int n)
{
	if (n == 1)
		return;
	else
	{
		an(array, n / 2);
		int val1 = (array[0][0] * array[0][0]) + (array[0][1] * array[1][0]);
		int val2 = (array[0][0] * array[0][1]) + (array[0][1] * array[1][1]);
		int val3 = (array[1][0] * array[0][0]) + (array[1][1] * array[1][0]);
		int val4 = (array[1][0] * array[0][1]) + (array[1][1] * array[1][1]);
		array[0][0] = val1;
		array[0][1] = val2;
		array[1][0] = val3;
		array[1][1] = val4;
		if (n & 1 == 1)
		{
			int val1 = (array[0][0] * 0) + (array[0][1] * 1);
			int val2 = (array[0][0] * 1) + (array[0][1] * 1);
			int val3 = (array[1][0] * 0) + (array[1][1] * 1);
			int val4 = (array[1][0] * 1) + (array[1][1] * 1);
			array[0][0] = val1;
			array[0][1] = val2;
			array[1][0] = val3;
			array[1][1] = val4;
		}
	}
}

int fib(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
	{

		int array[2][2] = { 0, 1, 1, 1 };
		an(array, n);
		int val = array[1][1];
		return val;
	}
}

int main()
{
	int input;
	scanf_s("%d", &input);
	printf("%d", fib(input-2));
	return 0;
}

