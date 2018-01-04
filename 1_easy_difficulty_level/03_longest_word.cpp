/*
Coderbyte coding challenge: Longest Word

Using the C++ language, have the function LongestWord(sen) take the sen parameter being passed and return the largest word in the string. 
If there are two or more words that are the same length, return the first word from the string with that length. 
Ignore punctuation and assume sen will not be empty.

Sample test cases:

Input:  "fun&!! time"
Output: "time"

Input:  "I love dogs"
Output: "love"
*/

#include <iostream>
#include <string>
#include <cctype>
#include <map>

using namespace std;

string LongestWord(string sen) { 
    
    size_t current_max_len{}, si{string::npos};
   
    map<size_t, string> words{};

    for (size_t i{}; i < sen.length(); i++) {
       
        if (isalnum(sen[i])) {

        	if (string::npos == si) si = i;

            current_max_len++;
            continue;
        }

        if ((words.find(current_max_len) == end(words)) && (string::npos != si)) {

        	words[current_max_len] = sen.substr(si, current_max_len);
    	}

    	si = string::npos;
      current_max_len = 0u;

    }

    if (current_max_len && (string::npos != si)) {

    	if (words.find(current_max_len) == end(words)) {

        	words[current_max_len] = sen.substr(si, current_max_len);
    	}
    }
    

  if (!words.empty()) {
  	auto last_pair_pos = end(words);
  	--last_pair_pos;
  	return last_pair_pos->second;  
  }

  return string{}; 
            
}

int main() { 
  
  // cout << LongestWord(gets(stdin));
  cout << LongestWord(move(string{"fun&!! time"})) << '\n'; // expected output: "time"
  cout << LongestWord(move(string{"I love dogs"})) << '\n'; // expected output: "love"
  return 0;    
}
