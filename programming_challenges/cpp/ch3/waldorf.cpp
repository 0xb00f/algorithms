#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<char>> grid;
int n, m, found_row, found_col;

bool compute_direction(string target, int row, int col, int row_mod, int col_mod)
{

  for(int i=0; i < target.length(); i++)
    {

      // bounds checking
      if(row < 0 || row == m || col < 0 || col == n) return false;
      // a mismatch?
      if(grid[row][col] != target[i]) return false;

      // good so far, keep going
      row += row_mod;
      col += col_mod;

    }

  return true;

}

bool match_found(string target, int row, int col)
{

  return compute_direction(target,row,col,-1,0) || // upward vertical
         compute_direction(target,row,col,1,0) ||  // downward vertical
         compute_direction(target,row,col,0,-1) || // left horizontal
         compute_direction(target,row,col,0,1) || // right horizontal
         compute_direction(target,row,col,-1,-1) || // left upward diag
         compute_direction(target,row,col,1,-1) || // left downward diag
         compute_direction(target,row,col,1,1) || // right downward diag
         compute_direction(target,row,col,-1,1);  // right upward diag
    
}

void find_match(string target)
{

  for(int row=0; row < m; row++)
    {

      for( int col=0; col < n; col++)
	{

	  if(grid[row][col] == target[0])
	    {

	      if(match_found(target,row,col))
		{
		  
		  cout << row+1 << " " << col+1 << "\n";
		  return;
		      
		}
	      
	    }
	  
	}

    }

}

int main(void)
{

  int cases;

  cin >> cases >> ws;

  for(int case_n=0; case_n < cases; case_n++)
    {

      cin >> m >> n >> ws;
      
      grid = vector<vector<char>>(m);
      
      char ch;

      // construct grid
      
      for(int i=0; i < m; i++)
	{
	  
	  for(int j=0; j < n; j++)
	    {
	      
	      grid[i].push_back(tolower(getchar()));
	      
	    }
	  
	  getchar();
	  
	}

      // read and match words

      int num_words;
      string word;
      
      cin >> num_words;
      
      for(int i=0; i < num_words; i++)
	{
	  
	  cin >> word;
	  transform(word.begin(),word.end(),word.begin(),::tolower);
	  found_col = n;
	  found_row = m;
	  find_match(word);
	  
	}

      grid.clear();

      if(case_n < cases-1) cout << "\n";

    }
  
  return 0;

}
