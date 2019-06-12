#include<stdio.h>
#include<stdlib.h>


void printperm(char *finalarray, char *inputarr, char *visited,int  len,int index,int len1)
{
	if (index == len)
	{ 
		finalarray[index] = '\0';
		printf("%s\n", finalarray);
	}
	else
	{
		int i = 0, used[10] = { 0 };
		for (i = 0; i < len1; i++)
		{
			if (visited[i] == 0)
			{
				if (used[inputarr[i] - '0'] == 0)
				{
					used[inputarr[i] - '0'] = 1;
					finalarray[index] = inputarr[i];
					visited[i] = 1;
					printperm(finalarray, inputarr, visited, len, index + 1, len1);
					visited[i] = 0;
				}
			}
		}
	}

}


int main()
{
	int len1 = 4, len2 = 4;
	char array1[5], *array="1135";
	char *visited = (char *)calloc(len2, sizeof(char));
	printperm(array1, array,visited, len1, 0,len2);
	return 0;
	
}


