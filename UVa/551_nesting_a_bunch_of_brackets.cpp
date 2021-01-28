#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

/* int tokens */
const int other = 0;
const int o_square = 1;
const int o_curly = 2;
const int o_paren = 3;
const int o_star = 4;
const int o_wedge = 5;
const int c_square = -1;
const int c_curly = -2;
const int c_paren = -3;
const int c_star = -4;
const int c_wedge = -5;

inline int token_value(string& s, int i)
{	
	switch(s[i])
	{
		case '(': 
			
			if(i < s.length() && s[i+1] == '*') return o_star;
			return o_paren;

		case ')': return c_paren;
		case '[': return o_square;
		case ']': return c_square;
		case '{': return o_curly;
		case '}': return c_curly;
		case '<': return o_wedge;
		case '>': return c_wedge;
		case '*': 
			
			if(i < s.length() && s[i+1] == ')') return c_star;
			
		default: return other;
	}
}

vector<int> tokenise_string(string& s)
{
	vector<int> ret;
	int i;
	for(i=0; i < s.length(); i++)
	{
		int token = token_value(s,i);
		ret.push_back(token); 
		if(token == o_star || token == c_star) i++;
	}

	return ret;
}

inline void clear_stack(stack<int>& s)
{
	while(!s.empty()) s.pop();
}

int main(void)
{
	string line;
	vector<int> token_line;
	stack<int> s;
	while(getline(cin,line))
	{
		token_line = tokenise_string(line);
		bool success = true;
		int i;
		for(i=0; i < token_line.size(); i++)
		{
			/*opening bracket*/
			if(token_line[i] >= o_square && token_line[i] <= o_wedge)
			{
				s.push(token_line[i]);
				continue;
			}
			/*closing bracket*/
			else if(token_line[i] >= c_wedge && token_line[i] <= c_square)
			{
				if(s.empty())
				{
					//cout << "NO " << i+1 << "\n";
					success = false;
					break;
				}
				int val = s.top();
				s.pop();
				if(val + token_line[i]) 
				{
					//cout << "NO " << i+1 << "\n";
					success = false;
					break;
				}
			}
		}
		if(success && s.empty())
		{
			cout << "YES\n";		
		}
		else
		{
			cout << "NO " << i+1 << "\n"; //yeah?
		}
		clear_stack(s);
	}

	return 0;
}
