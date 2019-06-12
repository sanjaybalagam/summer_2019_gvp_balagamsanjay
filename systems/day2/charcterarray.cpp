#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>


int match(char map[4][5], char *string, int rows, int cols, int row, int col,int len)
{
	int row1, col1,index,flag=0,count=0;
	//right
	if (col + len < cols)
	{

		for (row1 = row,col1=col,flag=1, index = 0; index < len ; col1++)
		{
			if (string[index++] != map[row1][col1])
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			count++;
			printf("%d %d %d %d", row, col, row1, col1);
		}

	}
	//down
	if (row + len < rows)
	{
		for (row1 = row,col1=col,flag=1, index = 0; index < len ; row1++)
		{
			if (string[index++] != map[row1][col1])
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			count++;
			printf("%d %d %d %d", row, col, row1, col1);
		}
	}
	//up
	if (row-len+1 >=0)
	{
		for (row1 = row, col1 = col, flag = 1, index = 0; index < len; row1--)
		{
			if (string[index++] != map[row1][col1])
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			count++;
			printf("%d %d %d %d", row, col, row1, col1);
		}
	}
	//left
	if (col - len + 1 >= 0)
	{
		for (row1 = row, col1 = col, flag = 1, index = 0; index < len; col1--)
		{
			if (string[index++] != map[row1][col1])
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			count++;
			printf("%d %d %d %d", row, col, row1, col1);
		}
	}
	//rigthdowns
	if (row + len < rows && col + len < cols)
	{
		for (row1 = row, col1 = col, flag = 1, index = 0; index < len; row1++,col1++)
		{
			if (string[index++] != map[row1][col1])
			{	
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			count++;
			printf("%d %d %d %d", row, col, row1, col1);
		}
	}

	//rightup
	if (col + len < cols && row - len + 1 >= 0)
	{
		for (row1 = row, col1 = col, flag = 1, index = 0; index < len; row1--, col1++)
		{
			if (string[index++] != map[row1][col1])
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			count++;
			printf("%d %d %d %d", row, col, row1, col1);
		}
	}
	//leftup
	if (col - len + 1 >= 0 && row - len + 1 >= 0)
	{

		for (row1 = row, col1 = col, flag = 1, index = 0; index < len; row1--,col1--)
		{
			if (string[index++] != map[row1][col1])
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			count++;
			printf("%d %d %d %d", row, col, row1, col1);
		}
	}
	//leftdown
	if (col - len + 1 >= 0 && rows + len < rows)
	{
		for (row1 = row, col1 = col, flag = 1, index = 0; index < len; row1++, col1--)
		{
			if (string[index] != map[row1][col1])
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
		{
			count++;
			printf("%d %d\n %d %d\n", row, col, row1, col1);
		}
	}


	return count;
}



void stringsearch(char map[4][5], char *string,int rows,int cols)
{
	int len = 0, count = 0;;
	while (string[len] != '\0')
		len++;
	int row= 0, col = 0;
	for (row = 0; row < rows; row++)
	{
		for (col = 0; col < cols; col++)
			if(map[row][col]==string[0])
				count+=	match(map, string, rows, cols,row,col,len);
	}

}


int main()
{
	char map[4][5] = { "eeee", "eeee","eeee","eeee" };
	char string[] = "ee";
	stringsearch(map, string, 2, 5);
	return 0;
}

