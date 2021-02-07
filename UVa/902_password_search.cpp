#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main(void)
{
	string msg;
	int klen;
	unordered_map<string,int> hash;
	while(cin >> klen >> msg)
	{
		int i;
		for(i=0; i <= msg.length()-klen; i++)
		{
			hash[msg.substr(i,klen)]++;
		}
		string max_str = "";
		int max_val = 0;
		for(auto entry: hash)
		{	
			if(entry.second > max_val)
			{
				max_val = entry.second;
				max_str = entry.first;
			}
		}
		cout << max_str << "\n";
		hash.clear();
	}
	return 0;
}
