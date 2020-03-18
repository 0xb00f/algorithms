#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

inline void flip(vector<int>& vec, int i)
{
  
  reverse(vec.begin(),vec.begin()+i+1);

}

int main(void)
{

  string line;
  vector<int> stack, sorted_stack, flips;

  while(getline(cin,line))
    {

      istringstream ss(line);
      int x;
      
      while(ss >> x)
	{

	  sorted_stack.push_back(x);
	  stack.push_back(x);

	}

      sort(sorted_stack.begin(),sorted_stack.end());

      int end_range = stack.size()-1;

      //point end_range to the highest index which is out of place
      while(stack[end_range] == sorted_stack[end_range]) end_range--;
 
      while(end_range > 0)
	{

	  //get the index of the highest out-of-order pancake
	  int index;
	  
	  for(index=0; index <= end_range; index++)
	    {

	      if(stack[index] == sorted_stack[end_range]) break;

	    }

	  //is it at the front already?
	  if(index == 0)
	    {

	      //flip and decrement at end_range
	      flip(stack,end_range);
	      flips.push_back(stack.size()-end_range);
	      while(stack[end_range] == sorted_stack[end_range]) end_range--;

	      continue;

	    }

	  //else, flip at this index, bring next highest to the front
	  flip(stack,index);
	  flips.push_back(stack.size()-index);

	  //then flip and decrement at end_range
	  flip(stack,end_range);
	  flips.push_back(stack.size()-end_range);
	  while(stack[end_range] == sorted_stack[end_range]) end_range--;

	}
      
      cout << line << "\n";

      flips.push_back(0);
      
      for(int i=0; i < flips.size(); i++)
	{

	  cout << flips[i];

	  if(i == flips.size()-1)
	    {

	      cout << "\n";

	    }
	  else
	    {

	      cout << " ";

	    }

	}

      // clean up
      flips.clear();
      stack.clear();
      sorted_stack.clear();

    }

  return 0;

}
