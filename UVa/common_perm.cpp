#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void find_common_perm(string s1, string s2)
{

  int s1_len = s1.length();
  int s2_len = s2.length();

  vector<vector<bool>> matrix(s1_len);

  // populate matrix
  for(int i=0; i < s1_len; i++)
    {

      matrix[i] = vector<bool>(s2_len,false);

      for(int j=0; j < s2_len; j++)
	{

	  if(s1[i] == s2[j])
	    {

	      matrix[i][j] = true;

	    }

	}

    }

  // discern lcs
  string lcs;
  vector<bool> rows(s1_len,false);
  vector<bool> cols(s2_len,false);

  for(int i=0; i < s1_len; i++)
    {
      
      for(int j=0; j < s2_len; j++)
	{

	  if(rows[i] || cols[j]) continue;
	  
	  if(matrix[i][j])
	    {

	      lcs += s1[i];
	      rows[i] = cols[j] = true;

	    }
	    
	}
      
    }

  sort(lcs.begin(),lcs.end());

  cout << lcs <<"\n";

}

int main(void)
{

  string s1, s2;

  while(getline(cin, s1) && getline(cin,s2))
    {

      find_common_perm(s1,s2);

    }
  
  return 0;

}
