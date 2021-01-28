#include <stdio.h>
#include <stdbool.h>

#define GRIDMAX 10+2
#define RESULTMAX 9
#define DEBUG 0

char grid[GRIDMAX][GRIDMAX] = {{0},{0}};
char copy[GRIDMAX][GRIDMAX] = {{0},{0}};
char* output[RESULTMAX] = {"improperly transformed",
			"preserved",
			"rotated 90 degrees",
			"rotated 180 degrees",
			"rotated 270 degrees",
			"reflected vertically",
			"reflected vertically and rotated 90 degrees",
			"reflected vertically and rotated 180 degrees",
			"reflected vertically and rotated 270 degrees",
			};
enum Result 
{
	Improper,
	Preserved,
	Deg_90,
	Deg_180,
	Deg_270,
	Vert,
	Vert_Deg_90,
	Vert_Deg_180,
	Vert_Deg_270
};

bool identical_grids(int dim)
{
	int i, j;
	for(i=0; i < dim; i++)
	{
		for(j=0; j < dim; j++)
		{
			if(grid[i][j] != copy[i][j]) return false;
		}
	}
	return true;
}

void swap(char *x, char *y)
{
	char tmp = *x;
	*x = *y;
	*y = tmp;
}

void transpose(int dim)
{
	int i, j, new[GRIDMAX][GRIDMAX] = {{0},{0}};
	for(i=0; i < dim; i++)
	{
		for(j=0; j < dim; j++)
		{
			 new[i][j] = grid[j][i];
		}
	}
	for(i=0; i < dim; i++)
	{
	        for(j=0; j < dim; j++)
	        {
	          	grid[i][j] = new[i][j];
		}
	}
}

void vert_reflect(int dim)
{
	int i;
	for(i=0; i < dim; i++)
	{
		int lo = 0, hi = dim-1;
		while(lo < hi)
		{
			swap(&grid[lo++][i],&grid[hi--][i]);
		}
	}
}

void horz_reflect(int dim)
{
	int i;
	for(i=0; i < dim; i++)
	{
		int lo = 0, hi = dim-1;
		while(lo < hi)
		{
			swap(&grid[i][lo++],&grid[i][hi--]);
		}
	}
}

/* rotate to the right */
void rotate(int dim)
{
  transpose(dim);
  horz_reflect(dim);
}

enum Result valid_transform(int dim)
{
	/*
	transform grid until it becomes copy, or bust 
	*/
	
	/* 0 degree rotation */
	if(identical_grids(dim)) return Preserved;
	/* 90 degree rotation */
	rotate(dim);
	if(identical_grids(dim)) return Deg_90;
	/* 180 degree rotation */
	rotate(dim);
	if(identical_grids(dim)) return Deg_180;
	/* 270 degree rotation */
	rotate(dim);
	if(identical_grids(dim)) return Deg_270;
	/* rotate once more to return to original */
	rotate(dim);
	/* mirrored 0 degree rotation */
	vert_reflect(dim);
	if(identical_grids(dim)) return Vert;
	/* mirrored 90 degree rotation */
	rotate(dim);
	if(identical_grids(dim)) return Vert_Deg_90;
	/* mirrored 180 degree rotation */
	rotate(dim);
	if(identical_grids(dim)) return Vert_Deg_180;
	/* mirrored 270 degree rotation */
	rotate(dim);
	if(identical_grids(dim)) return Vert_Deg_270;
	
	return Improper;
}

/* read grid */
void read_grids(int dim)
{
	int i, j;
	for(i=0; i < dim; i++)
	{
		for(j=0; j < dim; j++)
		{
			grid[i][j] = getchar();
		}
		getchar();
		for(j=0; j < dim; j++)
		{
			copy[i][j] = getchar();
		}
		getchar();
	}
}

int main(void)
{
	int n, round = 1;
	while(scanf("%d",&n) == 1)
	{
		getchar();
		read_grids(n);
		enum Result res = valid_transform(n);
		printf("Pattern %d was %s.\n",round++,output[res]);
	}
	return 0;
}
