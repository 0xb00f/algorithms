#include <iostream>
#include <stack>
#include <string>

/* uses the shunting-yard algorithm to convert infix to postfix*/

using namespace std;

string postfix;

inline int rank_operator(char op)
{	
	if(op == '+' || op == '-') return 1;
	if(op == '*' || op == '/') return 2;
	return 3; /*open bracket*/
}

inline void pop_until_lower_precedence(stack<char>& s, char op)
{
	/*pop operators while greater precedence, or until open paren*/
	int op_val = rank_operator(op);
	while(!s.empty() && rank_operator(s.top()) >= op_val)
	{
		if(s.top() == '(') break;
		postfix += s.top();
		s.pop();
	}
	s.push(op);
}

inline void dump_stack(stack<char>& s)
{
	while(!s.empty()) 
	{
		postfix += s.top();
		s.pop();
	}
}

inline void handle_close_paren(stack<char>& s)
{
	/*pop until open paren*/
	while(!s.empty()) 
	{
		char item = s.top();
		s.pop();
		if(item != '(')
		{
			postfix += item;
		}
		else
		{
			break;
		}
	}
}

void handle_operator(stack<char>& s, char op)
{
	if(op == ')') 
	{
		handle_close_paren(s);
	}
	else if(op == '(')
	{
		s.push(op);
	}
	else
	{
		pop_until_lower_precedence(s,op);
	}
}

int main(void)
{
	string line;
	int n_cases, i;
	stack<char> s;
	
	cin >> n_cases >> ws;
	
	for(i=0; i < n_cases; i++)
	{
		while(getline(cin,line))
		{
			/*end of an expression*/
			if(line == "")
			{
				break;
			}
			/*if we have a digit write immediately*/
			else if(isdigit(line[0]))
			{
				postfix += line[0];
				continue;
			}
			/*else we have an operator and we deal with the stack*/
			else
			{
				handle_operator(s,line[0]);
			}
		}
		dump_stack(s);
		cout << postfix << "\n";
		if(i < n_cases-1) cout << "\n";
		postfix = "";
	}
	return 0;
}
