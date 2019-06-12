#include<stdio.h>
#include<stdlib.h>


void printmirror(char *array, int len)
{
	static char array1[] = { '0', '1', '2', 'E', 'h', '5', '9', 'L', '8', '6' };
	char *array2 = (char *)malloc(sizeof(char)*len+1);
	int index;
	for (index = 0; index < len; index++)
		if (array[index] >= '0' && array[index] <= '9')
			array2[index] = array1[array[index]-'0'];
	array2[index] = '\0';
	printf("mirror: %s\n", array2);
}


void printn(int len, char *array, int index)
{
	if (index == len)
	{
		array[index] = '\0';
		int val;
		sscanf_s(array, "%d", &val);
		if (val != 0)
		{
			printf("val: %d  ", val);
			printmirror(array, len);
		}
	}
	else
	{
		int digit;
		for (digit = 0; digit <= 9; digit++)
		{
			array[index] = digit + '0';
			printn(len, array, index + 1);
		}
	}

}

int main()
{
	int len;
	scanf_s("%d", &len);
	char *array = (char *)malloc(sizeof(char)*len);
	printn(len-1, array, 0);
	return 0;
}
