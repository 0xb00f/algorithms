#include <iostream>
#include <set>
#include <list>
#include <vector>

#define NOT_NEEDED (-1)

using namespace std;

int main(void)
{
	int max_size, num_items, num_access;
	while(cin >> max_size >> num_items >> num_access)
	{
		int i, item, counter = 0;
		vector<int> history(num_access);
		vector<list<int>> indices(num_items);
		for(i=0; i < num_access; i++)
		{
			cin >> item;
			history[i] = item;
			indices[item].push_back(i);
		}
		set<int> cache, access_times;
		int next_idx;
		for(i=0; i < num_access; i++)
		{
			// update items next access index
			if(!indices[history[i]].empty())
			{
				indices[history[i]].pop_front();
				next_idx = indices[history[i]].empty() ? NOT_NEEDED : indices[history[i]].front();
			}
			auto search = cache.find(history[i]);	
			// item in cache?
			if(search != cache.end())
			{
				
				// erase if not needed
				if(next_idx == NOT_NEEDED)
				{
					access_times.erase(i);
					cache.erase(search);
				}
				// else update next index
				else
				{
					access_times.erase(i);
					access_times.insert(next_idx);
				}
				continue;
			}
			// erase highest next index item if cache full
			if(cache.size() == max_size)
			{
				cache.erase(history[*access_times.rbegin()]);
				access_times.erase(*access_times.rbegin());
			}
			// don't bother adding to cache if item not needed again
			if(next_idx != NOT_NEEDED)
			{
				cache.insert(history[i]);
				access_times.insert(next_idx);
			}
			counter++;
		}
		cout << counter << "\n";
	}
	return 0;
}
