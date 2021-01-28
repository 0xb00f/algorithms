#include <stdio.h>
#include <stdbool.h> 

#define GRIDMAX 3+2

int grid[GRIDMAX][GRIDMAX] = {{0},{0}};
int scratch[GRIDMAX][GRIDMAX] = {{0},{0}};

void read_grid(void)
{
	int i, j;
	for(i=1; i <= 3; i++)
	{
		for(j=1; j <= 3; j++)
		{
			char c = getchar();
			grid[i][j] = c - '0';
		}
		getchar();
	}
}

void transform_grid(void)
{	
	int i, j;
	/* transform grid */
	for(i=1; i <= 3; i++)
	{
		for(j=1; j <= 3; j++)
		{
			scratch[i][j] = grid[i-1][j] ^ grid[i+1][j]
			^ grid[i][j-1] ^ grid[i][j+1];
		}
	}
	/* copy grid */
	for(i=1; i <= 3; i++)
	{
		for(j=1; j <= 3; j++)
		{
			grid[i][j] = scratch[i][j];
		}
	}
}

bool is_zero_grid(void)
{
	int i, j;
	for(i=1; i <= 3; i++)
	{
		for(j=1; j <= 3; j++)
		{
			if(grid[i][j] != 0) return false;
		}
	}
	return true;
}

int main(void)
{
	int i,n;
	/* num cases */
	scanf("%d\n",&n);
	for(i=0; i < n; i++)
	{
		read_grid();
		/* how many transformations until a zero grid? */
		int iters = -1;
		while(!is_zero_grid())
		{
			transform_grid();
			iters++;
		}
		/* print answer */
		printf("%d\n",iters);
		getchar();
	}
	return 0;
}
