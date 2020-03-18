#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
#include <regex>
#include <vector>

using namespace std;

// structures
queue<string> targets;
unordered_map<string,int> erdos_numbers;
unordered_map<string,vector<string>> coauthors;
unordered_map<string,bool> scored;

int main(void)
{

  int cases, papers, num_targets;
  queue<string> q;

  cin >> cases;

  // for each case
  for(int case_num=1; case_num <= cases; case_num++)
    {

      cin >> papers >> num_targets >> ws;
      cout << "Scenario " << case_num << "\n";

      // read papers into vectors

      string line;
      smatch match;
      regex re {R"((\w+,\s[\w.]+),?)"};
      
      for(int paper_num=0; paper_num < papers; paper_num++)
	{

	  getline(cin >> ws,line);

	  sregex_iterator it(line.begin(),line.end(),re);
	  vector<string> paper_authors;

	  // get the authors of this paper
	  while(it != sregex_iterator{})
	    {
	      
	      erdos_numbers[(*it)[1]] = -1;
	      scored[(*it)[1]] = false;
	      paper_authors.push_back((*it)[1]);
	      
	      it++;
	      
	    }

	  // populate coauthors
	  for(auto& primary: paper_authors)
	    {

	      for(auto& secondary: paper_authors)
		{

		  if(primary == secondary) continue;

		  coauthors[primary].push_back(secondary);

		}

	    }

	}

      // read targets into queue

      string target_name;
      
      for(int target=0; target < num_targets; target++)
	{

	  getline(cin >> ws,target_name);
	  q.push(target_name);

	}

      // compute erdos numbers
      
      queue<string> score_q;
      score_q.push("Erdos, P.");
      erdos_numbers["Erdos, P."] = 0;
      string curr;

      while(!score_q.empty())
	{

	curr = score_q.front();
	score_q.pop();
	scored[curr] = true;

	for(auto& collab: coauthors[curr])
	  {

	    if(erdos_numbers[collab] >= 0) continue;

	    erdos_numbers[collab] = erdos_numbers[curr]+1;

	    if(scored[collab]) continue;

	    score_q.push(collab);

	  }


      }
      
    
      // read out erdos numbers of targets

      string target;
      
      while(!q.empty())
	{

	  target = q.front();
	  q.pop();

	  string res;

	  if(erdos_numbers.find(target) == erdos_numbers.end() ||
	     erdos_numbers[target] == -1)
	    {
	      
	      res = "infinity";

	    }
	  else
	    {

	      res = to_string(erdos_numbers[target]);
	    
	    }
	  
	  cout << target << " " << res << "\n";

	}
    

      // cleanup
      coauthors.clear();
      erdos_numbers.clear();

    }

  return 0;
  
}
