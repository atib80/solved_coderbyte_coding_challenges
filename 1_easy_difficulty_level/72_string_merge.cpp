/*
Coderbyte coding challenge: String Merge

Using the C++ language, have the function StringMerge(str) read the str parameter being passed which will contain a large string of alphanumeric characters 
with a single asterisk character splitting the string evenly into two separate strings. Your goal is to return a new string by pairing up the characters 
in the corresponding locations in both strings. For example: if str is "abc1*kyoo" then your program should return the string akbyco1o 
because a pairs with k, b pairs with y, etc. The string will always split evenly with the asterisk in the center.

Sample test cases:

Input:  "aaa*bbb"
Output: "ababab"

Input:  "123hg*aaabb"
Output: "1a2a3ahbgb"
*/

#include <iostream>
#include <string>
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

string StringMerge(string str) {

	str = trim(str);

	if (str.length() < 3u) return string{"Not possible!"};	

	const size_t delim_pos { str.find('*', 1u) };

	if (string::npos == delim_pos) return string{"Not possile!"};

	if (str.substr(0, delim_pos).length() != str.substr(delim_pos + 1u).length()) return string{"Not possile!"};

	const size_t str_half_len { str.substr(0, delim_pos).length() };

	string result{};
	result.resize(2 * str_half_len);

	for (size_t i{}, j{delim_pos + 1}; i != str_half_len; i++, j++) {
		result[2 * i] = str[i];
		result[2 * i + 1] = str[j];
	}
 
  	return result; 
            
}

int main() { 
  
  // cout << StringMerge(move(string{gets(stdin)}));
  cout << StringMerge(move(string{"abc1*kyoo"})) << '\n';   // expected output: "akbyco1o"
  cout << StringMerge(move(string{"aaa*bbb"})) << '\n';     // expected output: "ababab"
  cout << StringMerge(move(string{"123hg*aaabb"})) << '\n'; // expected output: "1a2a3ahbgb"
  return 0;
    
}
