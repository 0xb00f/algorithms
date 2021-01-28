#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARDSIZE 102
#define MINE (-1)

/*globals*/
char input_board[BOARDSIZE][BOARDSIZE] = {{0},{0}};
int output_board[BOARDSIZE][BOARDSIZE] = {{0},{0}};

void read_board(int m, int n)
{
	int i;
	for(i=1; i <= m; i++)
	{
		char line[BOARDSIZE+1] = {0};
		fgets(line,BOARDSIZE,stdin); 
		strncpy(input_board[i]+1,line,n);
	}
}

void clear_boards(void)
{
	int i, j;
	for(i = 0; i < BOARDSIZE; i++)
	{
		for(j = 0; j < BOARDSIZE; j++)
		{
			input_board[i][j] = output_board[i][j] = 0;
		}
	}
}

void process_mine(int row, int col)
{
	int i, j;
	for(i = -1; i < 2; i++)
	{
		for(j = -1; j < 2; j++)
		{	
			if((!i && !j) || (input_board[row+i][col+j] == '*')) continue;
			output_board[row+i][col+j]++; 
		}	
	}
}

void process_board(int m, int n)
{
	int i, j;
	for(i = 1; i <= m; i++)
	{
		for(j = 1; j <= n; j++)
		{	
			if(input_board[i][j] == '*')
			{
				output_board[i][j] = MINE;
				process_mine(i,j);
			}
		}	
	}
}

void print_board(int round, int m, int n)
{
	printf("Field #%d:\n",round);
	int i, j;
	for(i = 1; i <= m; i++)
	{
		for(j=1; j <= n; j++)
		{
			if(output_board[i][j] == MINE)
			{
				putchar('*');
			}
			else
			{
				printf("%d",output_board[i][j]);
			}
		}
		putchar('\n');
	}
}

int main(void)
{
	int rows, cols, round = 1; 
	while(1)
	{
		scanf("%d %d",&rows,&cols);
		getchar(); /*consume trailing newline*/
		if(!rows && !cols)
		{
			break;
		}
		else if(round > 1)
		{
			putchar('\n');
		}
		read_board(rows,cols);
		process_board(rows,cols);
		print_board(round++,rows,cols);
		clear_boards();
	}
	return 0;
}
