#include <stdio.h>

#define CARMAX 1000+5
#define CARNUMMAX 10000+5

int main(void)
{
	int n;
	while(scanf("%d",&n) == 1 && n > 0)
	{	
		int error = 0,rank;
		int grid[CARMAX] = {0};
		for(rank=0; rank < n; rank++)
		{
			int car, pos;
			scanf("%d %d",&car,&pos);
			int og_pos = pos + rank;
			if(og_pos < 0 || og_pos >= n) error = 1;
			if(grid[og_pos] > 0) error = 1;
			if(!error)
			{
				grid[og_pos] = car;
			}
			else
			{
				continue;
			}
		}
		if(!error)
		{
			for(rank=0; rank < n; rank++)
			{
				printf("%d",grid[rank]);
				if(rank < n-1) printf(" ");
			}
			printf("\n");
		}
		else
		{
			printf("-1\n");
		}
	}
	return 0;
}
