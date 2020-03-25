#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

inline int get_median(vector<int>& vec)
{

  bool even = vec.size() % 2 == 0 ? true : false;

  int mid = (vec.size() - 1) / 2;

  if(even)
    {

      return (vec[mid] + vec[mid+1]) / 2;

    }
  else
    {

      return vec[mid];

    }

}

int main(void)
{

  int cases;

  cin >> cases;

  for(int i=0; i < cases; i++)
    {

      int num_relos;
      cin >> num_relos;

      vector<int> house_nums;
      int n;
      
      for(int house=0; house < num_relos; house++)
	{

	  cin >> n;
	  house_nums.push_back(n);
	  
	}

      sort(house_nums.begin(),house_nums.end());


      int median = get_median(house_nums), result = 0;

      for(auto& x: house_nums) result += abs(median - x);

      cout << result << "\n";

    }
  
  return 0;

}
