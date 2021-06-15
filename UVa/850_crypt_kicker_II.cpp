#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

bool known_plaintext(string line)
{
	string known = "the quick brown fox jumps over the lazy dog";
	if(line.length() != known.length()) return false; 
	vector<char> m(26,'*'), r(26,'*');
	int i;
	// can we map it to the known plaintext?
	for(i=0; i < known.length(); i++)
	{
		if(known[i] == ' ' && line[i] == ' ') continue;
		if(known[i] == ' ' && line[i] != ' ') return false;
		if((m[line[i] - 'a'] != '*') && (m[line[i] - 'a'] != known[i])) return false;
		if((r[known[i] - 'a'] != '*') && (r[known[i] - 'a'] != line[i])) return false;
		m[line[i] - 'a'] = known[i];
		r[known[i] - 'a'] = line[i];
	}
	return true;
}

vector<char> keygen(string line)
{
	vector<char> key(26,'*');
	string known = "the quick brown fox jumps over the lazy dog";
	int i;
	for(i=0; i < line.length(); i++)
	{
		if(line[i] == ' ') continue;
		key[line[i]-'a'] = known[i];
	}
	return key;
}

int main(void)
{
	int n_rounds;

	cin >> n_rounds >> ws;
	
	vector<string> lines;
	string line;
	int round;
	for(round = 0; round < n_rounds; round++)
	{
		while(getline(cin, line))
		{
			if(line == "") break; 
			lines.push_back(line);
		}
		string known = "";
		for(string s: lines)
		{
			if(known_plaintext(s))
			{
				known = s;
				break;
			}
		}
		if(known == "")
		{
			cout << "No solution.\n";
			if(round < n_rounds-1) cout << "\n";
			lines.clear();
			continue;
		}
		for(string cand: lines)
		{
			vector<char> key = keygen(known);
			int i;
			for(i=0; i < cand.length(); i++)
			{
				if(cand[i] == ' ') 
				{
					cout << cand[i];
					continue;
				}
				cout << key[ cand[i] - 'a' ];
			}
			cout << "\n";
		}
		if(round < n_rounds-1) cout << "\n";
		lines.clear();
	}
}
