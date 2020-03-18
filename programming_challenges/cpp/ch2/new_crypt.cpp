#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <unordered_set>
#include <vector>

#define DEBUG 0

// TO DO: handle tricky cases where there's no easy cases, hence no candidates too

using namespace std;

typedef unordered_map<char,unordered_set<char>> CharMap;
typedef unordered_map<string,unordered_set<string>> WordMap;
typedef unordered_map<int,unordered_set<string>> Dictionary;

// data structures
CharMap char_map;
WordMap word_map;
Dictionary dict;
unordered_map<char,bool> is_mapped_to;
unordered_map<char,char> decrypt;

const char nomap = '\0';

// helper functions

void print_maps(void) {

  for(auto& entry: word_map) {

    cout << "mappings for  word " << entry.first << ": ";

    for(auto& word: entry.second) {

      cout << word << " ";

    }

    cout << "\n";

  }

  for(auto& entry: char_map) {

    cout << "mappings for letter " << entry.first << ": ";

    for(auto& word: entry.second) {

      cout << word << " ";

    }

    cout << "\n";

  }

}

void init_data(void) {

  for(char c = 'a'; c <= 'z'; c++) {

    is_mapped_to[c] = decrypt[c] = nomap;

  }

}

inline void clear_data(void) {

  char_map.clear();
  word_map.clear();
  is_mapped_to.clear();
  decrypt.clear();

}

void read_dict(void) {

  int lines = 0;

  cin >> lines;

  string word;

  while(lines > 0) {

    cin >> word;
    dict[word.length()].insert(word);
    lines--;
    
  }

}

string translate(string s) {

  unordered_map<char,char> mapping;
  char subs = 'a';

  for(auto& ch: s) {

    mapping[ch] = subs++;

  }

  string res = "";

  for(int i=0; i < s.length(); i++) {

    res += mapping[s[i]];

  }

  return res;

}

bool same_structure(string s1, string s2) {

  return translate(s1) == translate(s2);

}

bool build_word_map(string line) {

  string word;
  stringstream stream(line);

  while(stream >> word) {

    int success = 0;

    for(auto& cand : dict[word.length()]) {

      if(same_structure(word,cand)) {

	word_map[word].insert(cand);
	success++;

      }

    }

    if(success == 0) return false;

  }

  return true;

}

void build_char_map(void) {
  
  for(auto& crypt_word: word_map) {

    // iterate thorugh the word map and initialise encrypted letters

    for(auto& crypt_char: crypt_word.first) {

      decrypt[crypt_char] = is_mapped_to[crypt_char] = nomap;

    }

    // add possible letter translations

    for(auto& plain_word: crypt_word.second) {

      for(int i=0; i < crypt_word.first.length(); i++) {

	char_map[crypt_word.first[i]].insert(plain_word[i]);

      }

    }

  }
  
}

void cleanup_words(char k,char v) {

  vector<pair<string,string>> to_delete;

  // iterate through word map
  for(auto& word_entry: word_map) {

    // iterate through possible translations
    for(auto& plain_word: word_entry.second) {

      // if a word conflicts with mapping k to v, delete it
      for(int i = 0; i < plain_word.length(); i++) {

	if(word_entry.first[i] == k && plain_word[i] != v)
	  to_delete.push_back(make_pair(word_entry.first,plain_word));

      }				     
      
    }

  }

  // delete kill list
  for(auto& kill_word: to_delete) word_map[kill_word.first].erase(kill_word.second);

}

void cleanup_chars(char k, char v) {

  vector<pair<char,char>> to_delete;

  // iterate through char map
  for(auto& char_entry: char_map) {

    // iterate trhough possible translations
    for(auto& plain_char: char_entry.second) {

      // if char present, it's been mapped and can be removed
      if(plain_char == v)
	to_delete.push_back(make_pair(char_entry.first,plain_char));

    }

  }

  // delete kill list
  for(auto& kill: to_delete) char_map[kill.first].erase(kill.second);

  char_map.erase(k);

}
  

void cleanup_data(char k, char v) {

  cleanup_words(k,v);
  cleanup_chars(k,v);

}

void do_mapping(char k, char v) {

  // early exit if mapping already done or there is a conflict
  if(is_mapped_to[v]) {

    return;

  }
  // perform the mapping
  decrypt[k] = v;
  is_mapped_to[v] = true;

  // remove all conflicts from the data
  cleanup_data(k,v);

}


bool map_word(string crypt, string plain) {

  // check that mappings wont conflict with existing, exit failure if so
  for(int i =0; i < crypt.length(); i++) {
    
    if(is_mapped_to[plain[i]] && decrypt[crypt[i]] != plain[i]) {

      return false;

    }

  }

  // perform mapping
  for(int i =0; i < crypt.length(); i++) {

    do_mapping(crypt[i],plain[i]);

  }

  // remove word from word map
  word_map[crypt].erase(plain);

  return true;

}

bool easy_word_cases(void) {

  // iterate through word map
  for(auto& entry: word_map) {

    //early exit failure if entry has zero candidates
    if(entry.second.size() == 0) return false; // TO DO: exit failure(separate checking function?) !!!!!!!!!!
    
    // if word has only one candidate
    if(entry.second.size() == 1) {
      
      // map word, exiting with failure if conflict exists
      auto elem = entry.second.begin();

      map_word(entry.first,*elem);

      // clean up data
      word_map.erase(entry.first);

      // exit success - easy case resolved
      return true;

    }

  }

  // exit failure - no easy case found
  return false;

}

bool easy_letter_cases(void) {

  for(auto& entry: char_map) {

    // leave failure conditions to another checking function !!!!!!!!!!!

    // if letter has only one possibility
    if(entry.second.size() == 1) {

      auto elem = entry.second.begin();
      
      do_mapping(entry.first,*elem);

      // clean up data
      char_map.erase(entry.first);

      // exit success - easy case resolved
      return true;

    }

  }

  // exit failure - no easy cases found
  return false;

}

void reject_line(string line) {

  for(auto& ch: line) {

    if(ch == ' ') {

      cout << ' ';

    }else{

    cout << '*';

    }
    
  }

  cout << "\n";

}

void accept_line(string line) {

  for(auto& ch: line) cout << decrypt[ch];

  cout << "\n";

}

bool all_mapped(void) {

  for(auto& letter: decrypt) {

    if(decrypt[letter.first] == nomap) {

      return false;

    }

  }

  return true;

}

bool all_valid_words(string line) {

  string mapped = "";

  for(auto& ch: line) mapped += decrypt[ch];

  stringstream ss(mapped);
  string word;
  
  while(ss >> word) {

    if(dict[word.length()].count(word) == 0) return false;

  }

  return true;

}

int score_candidate(const string& plain,const string& cand) {

  int score = 0;

  for(int i=0; i < plain.length(); i++) {

    if(decrypt[plain[i]] == cand[i]) score++;

  }

  return score;

}

bool decrypt_best_candidate(void) {

  string best_cand, plain_word;
  int best_cand_score = 0;

  // for each encrypted word
  for(auto& word: word_map) {

    // search for a best candidate for decryption
    for(auto& cand: word.second) {

      int temp_score = score_candidate(word.first,cand);

      if(temp_score > best_cand_score) {

	plain_word = word.first;
	best_cand = cand;
	best_cand_score = temp_score;

      }
    
    }

  }

  // was a candidate found?
  if(best_cand_score > 0) {

    if(map_word(plain_word,best_cand)) {

	return true;

      }else{

	return false;

      }

  }else{

	return false;

  }

}

bool decrypt_line(string line) {

  // decrypt
  while(true) {
	
    // easy cases
    if(easy_word_cases()) continue;
    if(easy_letter_cases()) continue;
    
    // best candidates
    if(decrypt_best_candidate()) continue;

    // are we done?
    if(all_mapped() && all_valid_words(line)) break;

    // no further progress
    return false;

  }

  // line decrypted
  return true;

}

int main(void) {

  decrypt[' '] = ' ';

  read_dict();

  cin >> ws;
  
  string line;
  while(getline(cin,line)) {
    
    if(line == "")
      {

	cout << "\n";
	continue;

      }
    
    if(!build_word_map(line)) {
      
      reject_line(line);
      continue;
      
    }else{
      
      build_char_map();
      
    }

    if(decrypt_line(line)) {

      accept_line(line);

    }else{

      reject_line(line);

    }
    
    // clean up
    clear_data();
    decrypt[' '] = ' ';
    
  }
  
  return 0;
  
}
