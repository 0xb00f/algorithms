#include <iostream>

/* correct but time limit exceeded! optimise */

using namespace std;

#define NMAX 9
#define KMAX 65

int num_solns = 0;

void construct_cands(int a[], int n, int k, int c[], int& ncands)
{

  int i, j;
  bool legal_move;
  // we only want solutions sorted in ascending order
  int lim = k == 1 ? k : a[k-1]+1;

  ncands = 0;

  for(int i=lim; i <= n*n; i++)
    {

      legal_move = true;

      for(int j=1; j < k; j++)
	{

	  int b_row = a[j] / n;
	  int b_col = (a[j] %n) + 1;
	  int c_row = i / n;
	  int c_col = (i % n) + 1;
	  
	  if(abs(b_row-c_row) == abs(b_col-c_col))
	    {

	      legal_move = false;
	      break;

	    }

	}

      if(legal_move == true)
	{

	  c[ncands] = i;
	  ncands++;

	}

    }

}

void backtrack(int a[], int n, int k, int num_bishops)
{

  //early exit
  if(n > 1 && k > 2*n-2) return;

  int c[KMAX];
  int ncands;
  int i;

  if(k == num_bishops)
    {

      num_solns++;
      
    }
  else
    {
      
      num_bishops++;
      construct_cands(a,n,num_bishops,c,ncands);
      
      for(i=0; i<ncands; i++)
	{

	  a[num_bishops] = c[i];
	  backtrack(a,n,k,num_bishops);

	}

    }
  
}

int main(void)
{

  int n, k;
  int a[KMAX] = {0};
  
  while(true)
    {

      cin >> n >> k;

      if(n==0 && k==0) break;

      backtrack(a,n,k,0);

      cout << num_solns << "\n";

      num_solns = 0;

    }

  return 0;

}
