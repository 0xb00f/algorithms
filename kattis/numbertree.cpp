#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int num_nodes(int depth)
{	
	int i = depth+1, y=1;
	while(i-- > 0) y = 2*y;
	return y-1;
}

int compute_label(int depth, string path)
{
	int curr_node = num_nodes(depth);
	int level = 1, diff = 0;
	for(auto ch: path)
	{
		level <<= 1;
		// node even
		if(curr_node % 2 == 0)
		{
			//left turn
			if(ch == 'L')
			{
				diff = 2*diff;
			}
			//right turn
			else
			{
				diff = 2*diff+1;
			}
		}
		// node odd
		else
		{
			//right turn
			if(ch == 'R')
			{
				diff = 2*diff;
			}
			//right turn
			else
			{
				diff = 2*diff-1;
			}
		}
		curr_node -= level+diff;
	}
	return curr_node;
}

int main(void)
{
	int depth;
	string path, line;
	while(getline(cin,line))
	{
		stringstream iss(line);
		iss >> depth >> path; 
		if(iss.fail()) path = "";
		cout << compute_label(depth,path) << "\n";
	}
	return 0;
}
