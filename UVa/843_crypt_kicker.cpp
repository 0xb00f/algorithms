#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

inline bool same_structure(string x, string y)
{
	// can we map x to y?
	map<char,char> m, r;
	int i;
	for(i=0; i < x.length(); i++)
	{
		if(m[x[i]] && m[x[i]] != y[i]) return false;
		if(r[y[i]] && r[y[i]] != x[i]) return false;
		m[x[i]] = y[i];
		r[y[i]] = x[i];
	}
	return true;
}

void build_ctext_dict(multimap<int,string>& pmm, map<string,set<string>>& m, string line)
{
	istringstream ss(line);
	string cword;
	// go through each cryptword
	while(ss >> cword)
	{
		auto search = pmm.equal_range(cword.length());
		// find each plain word of same length
		for(auto itr = search.first; itr != search.second; itr++)
		{
			if(same_structure(cword,itr->second)) m[cword].insert(itr->second);
		}
	}	
}

bool invalid_mapping(vector<char>& record, vector<char>& rev_record, string crypt, string cand)
{
	bool err = false;
	int i;
	for(i=0; i < cand.length(); i++)
	{
		// not yet mapped
		if(record[crypt[i] - 'a'] == '*' && rev_record[cand[i] - 'a'] == '*') continue;
		// mapped to something else
		if(record[crypt[i] - 'a'] != cand[i]) {err = true; break;} 
		// already mapped into by something else
		if(rev_record[cand[i] - 'a'] != crypt[i]) {err = true; break;} 	
	}
	return err;
}

bool success = false;

void backtrack(multimap<int,string>& mm, string line, map<string,set<string>>::iterator itr, map<string,set<string>>::iterator itr_end, vector<char>& record, vector<char>& rev_record)
{
	if(itr == itr_end)
	{
		success = true;
		return;
	}
	
	string cword = itr->first;
	set<string> cands = itr->second;
	for(string s: cands)
	{
		if(invalid_mapping(record,rev_record,cword,s)) continue;
		int i;
		for(i=0; i < cword.length(); i++)
		{
			record[cword[i] - 'a'] = s[i];
			rev_record[s[i] - 'a'] = cword[i];
		}
		backtrack(mm,line,next(itr,1),itr_end,record,rev_record);	
		if(!success)
		{
			for(i=0; i < cword.length(); i++)
			{
				record[cword[i] - 'a'] = '*';
				rev_record[s[i] - 'a'] = '*';
			}
		}
		else // we're all done
		{
			return;
		}
	}
}

int main(void)
{
	int ptext_size;

	cin >> ptext_size >> ws;
	
	multimap<int,string> ptext;
	int i;
	string line;
	for(i=0; i < ptext_size; i++)
	{	
		getline(cin >> ws,line);
		ptext.insert(make_pair(line.length(),line));
	}
	while(getline(cin,line))
	{
		map<string,set<string>> ctext; 
		build_ctext_dict(ptext,ctext,line);
		vector<char> record(26,'*');
		vector<char> rev_record(26,'*');
		success = false;
		backtrack(ptext,line,ctext.begin(),ctext.end(),record,rev_record);
		for(i=0; i < line.length(); i++)
		{
			if(line[i] == ' ') {cout << line[i]; continue;}
			success ? cout << record[ line[i] - 'a' ] : cout << '*';
		}
		cout << "\n";
	}
	return 0;
}
