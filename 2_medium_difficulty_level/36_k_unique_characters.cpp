/*
Coderbyte coding challenge: K Unique Characters

Using the C++ language, have the function KUniqueCharacters(str) take the str parameter being passed and find the longest substring 
that contains k unique characters, where k will be the first character from the string. 
The substring will start from the second position in the string because the first character will be the integer k. 
For example: if str is "2aabbacbaa" there are several substrings that all contain 2 unique characters, namely: ["aabba", "ac", "cb", "ba"], 
but your program should return "aabba" because it is the longest substring. If there are multiple longest substrings, 
then return the first substring encountered with the longest length. k will range from 1 to 6.

Sample test cases:

Input:  "3aabacbebebe"
Output: "cbebebe"

Input:  "2aabbcbbbadef"
Output: "bbcbbb"
*/

#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

string KUniqueCharacters(string str) {

  const size_t k{static_cast<size_t>(str[0] - '0')};

  str.erase(begin(str));

  const size_t str_len { str.length() };

  size_t current_substr_len { str_len };

  unordered_set<char> found_chars{};

  while (current_substr_len >= k) {

  for (size_t i{}; i + current_substr_len <= str_len; i++) {

  		const string sub_str{ str.substr(i, current_substr_len) };

  		found_chars.clear();  		

  		for (const char ch : sub_str) found_chars.insert(ch);

  		if (k == found_chars.size()) return sub_str;

  	}

  	current_substr_len--;

  }

  char buffer[128];
  sprintf(buffer, "Could not find any substring with %lu unique characters!", k);  
  return string{buffer}; 

  // string reply{"Could not find any substring with "};
  // reply += to_string(k);            
  // reply += " unique characters!";
  // return reply;
}

int main() { 
  
  // cout << KUniqueCharacters(move(string{gets(stdin)}));
  cout << KUniqueCharacters(move(string{"2aabbacbaa"})) << '\n';    // expected output: "aabba"
  cout << KUniqueCharacters(move(string{"3aabacbebebe"})) << '\n';  // expected output: "cbebebe"
  cout << KUniqueCharacters(move(string{"2aabbcbbbadef"})) << '\n'; // expected output: "bbcbbb"

  return 0;    
}
