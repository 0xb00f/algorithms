#include <stdio.h>

#define MAXSOLDIERS 100000+5

int left[MAXSOLDIERS];
int right[MAXSOLDIERS];

int main(void)
{
	int n_soldiers, n_reports;
	scanf("%d %d",&n_soldiers,&n_reports);
	while(n_soldiers && n_reports)
	{	
		int i;
		/* initialise arrays of everyone's left & right buddies */
		for(i=1; i <= n_soldiers+5; i++)
		{	
			left[i] = i-1;
			right[i] = i+1;
		}
		for(i=0; i < n_reports; i++)
		{
			int l, r;
			scanf("%d %d",&l,&r);
			/* kill soldiers */
			right[ left[l] ] = right[r];
			left[ right[r] ] = left[l];
			/* print buddies */
			if(left[l] > 0)
			{
				printf("%d ",left[l]);
			}
			else
			{
				printf("* ");
			}
			if(right[r] <= n_soldiers)
			{
				printf("%d\n",right[r]);
			}
			else
			{
				printf("*\n");
			}
		}
		printf("-\n");
		scanf("%d %d",&n_soldiers,&n_reports);
	}
	return 0;
}
