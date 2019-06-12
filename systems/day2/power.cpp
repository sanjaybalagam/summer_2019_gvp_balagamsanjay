#include<stdio.h>
#include<stdlib.h>

#define M 1000000000+7

int power(int a, int n)
{
	if(n < 0)
		return -1;
	if (n == 0)
		return 1;
	else if (n == 1)
		return a;
	else
	{
		int k = n / 2;
		k = power(a, k);
		return ((k%M)*(k%M)*(power(a, n & 1)%M))%M;
	}
}

int main()
{
	int num, pow;
	printf("enter number , power");
	scanf_s("%d%d", &num, &pow);
	printf("\n%d",power(num, pow));
	return 0;
}