/*
Coderbyte coding challenge: String Scramble

Using the C++ language, have the function StringScramble(str1,str2) take both parameters being passed and return the string true if a portion of str1 characters 
can be rearranged to match str2, otherwise return the string false. For example: if str1 is "rkqodlw" and str2 is "world" the output should return true. 
Punctuation and symbols will not be entered with the parameters.

Sample test cases:

Input:  "cdore" & str2= "coder"
Output: "true"

Input:  "h3llko" & str2 = "hello"
Output: "false"
*/

#include <iostream>
#include <string>
#include <map>
#include <cctype>

using namespace std;

string trim(const string& str)
{
	size_t begin_str{};
	size_t end_str{str.size() - 1};

	if (0u == str.length()) return string{};

	for (; begin_str <= end_str; ++begin_str)
	{
		if (!isspace(str[begin_str])) break;
	}

	if (begin_str > end_str) return string{};

	for (; end_str > begin_str; --end_str)
	{
		if (!isspace(str[end_str])) break;
	}

	return str.substr(begin_str, end_str - begin_str + 1);
}

string StringScramble(string str1, string str2) {

  str1 = trim(str1);
  str2 = trim(str2);

  if (str1.length() < str2.length()) return "false";

  map<char, size_t> str1_char_count{};
  map<char, size_t> str2_char_count{};

  for (const char c : str1) {

  	if (str1_char_count.find(c) != end(str1_char_count)) str1_char_count[c]++;

  	else str1_char_count[c] = 1u;

  }

  for (const char c : str2) {

  	if (str2_char_count.find(c) != end(str2_char_count)) str2_char_count[c]++;

  	else str2_char_count[c] = 1u;
  	
  }

  for (const auto& ch_count : str2_char_count) {

  	if (str1_char_count.find(ch_count.first) == end(str1_char_count)) return "false";

  	if (str1_char_count[ch_count.first] < ch_count.second) return "false";

  }
  
  return "true";            
}

int main() { 

  // cout << StringScramble(gets(stdin));
  cout << StringScramble("rkqodlw", "world") << '\n';         // expected output: "true"
  cout << StringScramble("cdore", "coder") << '\n';           // expected output: "true"
  cout << StringScramble("h3llko", "hello") << '\n';          // expected output: "false"
  cout << StringScramble("abcgggdfe", "abcdef") << '\n';      // expected output: "true"
  cout << StringScramble("aqwe", "qa") << '\n';   		        // expected output: "true"
  cout << StringScramble("yelowrqwedlk", "yellowred") << '\n';// expected output: "true"

  return 0;    
}
