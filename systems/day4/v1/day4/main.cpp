
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

void move_pos(int *i,int *j,int dir)
{
	switch (dir)
	{
	case 0:{//right
		*j =*j+ 1;
		break;
	}
	case 1:{//down
		*i = *i + 1;
		break;
	}
	case 2:{//left
		*j = *j - 1;
		break;
	}
	case 3:{//up
		*i = *i - 1;
		break;
	}
	}
}

int maze_safe(char **maze,char **result,int start_i,int start_j,int rows,int cols)
{
	if (start_i >= rows || start_i < 0 || start_j>=cols || start_j < 0 || maze[start_i][start_j] == '0'||result[start_i][start_j]!='0')
	{
		return -1;
	}
	return 0;
}

int maze_solver(char **maze,int start_i,int start_j,int end_i,int end_j,char **result,int rows,int cols)
{
	if (maze_safe(maze,result,start_i,start_j,rows,cols)==-1)
	{
		return -1;
	}
	else if (start_i == end_i && start_j == end_j)
	{
		return 0;
	}
	else
	{
		result[start_i][start_j] = '1';
		int dir = 0,pos_i,pos_j;
		for (dir = 0; dir < 3; dir++)
		{
			pos_i = start_i;
			pos_j = start_j;
			move_pos(&pos_i, &pos_j, dir);
			if(maze_solver(maze, pos_i, pos_j, end_i, end_j, result, rows, cols)==0)
				return 0;
		}
		result[start_i][start_j] = '2';
	}
}

void solve_maze(char **maze, int start_i, int start_j, int end_i, int end_j, char **result, int rows, int cols)
{
	if (maze == NULL)
	{
		printf("no dimensions");
	}
	else
	{
		int k = maze_solver(maze, start_i, start_j, end_i, end_j, result, rows, cols);
		if (k == -1)
		{
			printf("no solution");
		}
		else
		{
			result[end_i][end_j] = 1;
			int i = 0,j=0;
			for (; i < rows; i++)
			{
				for (j = 0; j < cols + 1; j++)
				{
					if (result[i][j] == '2')
						printf("%s\n", result[i][j] - 2);
					else
						printf("%s\n", result[i][j]);
				}
			}
		}
	}
}
int main()
{
	int rows, cols, start_row, start_col, end_row, end_col;
	printf("enter rows  cols  startrow  startcol  destrow  destcol");
	scanf("%d%d%d%d%d%d", &rows, &cols, &start_row, &start_col, &end_row, &end_col);
	char **maze = (char**)malloc(sizeof(char*)*rows);
	char **result = (char**)malloc(sizeof(char*)*rows+1);
	int i, j;
	for (i = 0; i < rows; i++)
	{
		j = 0;
		maze[i] = (char*)malloc(sizeof(char)*cols+1);
		result[i] = (char*)malloc(cols*sizeof(char));
		scanf("%s", maze[i]);
		while (j < cols)
		{
			result[i][j] = '0';
			j++;
		}

		result[i][j] = '\0';
	}
	printf("\n\n");
	solve_maze(maze,start_row,start_col,end_row,end_col,result,rows,cols);
}