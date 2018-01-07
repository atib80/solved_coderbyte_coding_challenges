/*
Coderbyte coding challenge: String Reduction

Using the C++ language, have the function StringReduction(str) take the str parameter being passed and return the smallest number 
you can get through the following reduction method. 
The method is: Only the letters a, b, and c will be given in str and you must take two different adjacent characters and replace it with the third. 
For example "ac" can be replaced with "b" but "aa" cannot be replaced with anything. 
This method is done repeatedly until the string cannot be further reduced, and the length of the resulting string is to be outputted. 
For example: if str is "cab", "ca" can be reduced to "b" and you get "bb" (you can also reduce it to "cc"). 
The reduction is done so the output should be 2. 
If str is "bcab", "bc" reduces to "a", so you have "aab", then "ab" reduces to "c", and the final string "ac" is reduced to "b" so the output should be 1.

Sample test cases:

Input:  "abcabc"
Output: 2

Input:  "cccc"
Output: 4
*/

#include <iostream>
#include <cctype>
#include <string>
#include <unordered_map>

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

string StringReduction(string str) { 

  str = trim(str);  

  const unordered_map<string, char> reduce_pairs{ {"ab", 'c'}, {"ba", 'c'}, {"ac", 'b'}, {"ca", 'b'}, {"bc", 'a'}, {"cb", 'a'} };  

  while (true) {  	

  	bool is_reduced{};

  	size_t i{};

  	for ( ; i < str.length() - 1; i++) {

  		const string key { str.substr(i, 2) };

  		if (reduce_pairs.find(key) != end(reduce_pairs)) { 

  			const char rc { reduce_pairs.find(key)->second };

  			str.replace(i, 2, 1, rc);

  			is_reduced = true;

  			continue;
  		}

  	}

  	if (!is_reduced) break;
  
  }

  return to_string(str.length());
            
}

int main() {

  // cout << StringReduction(move(string{gets(stdin)}));
  cout << StringReduction(move(string{"cab"})) << '\n';    // expected output: 2  
  cout << StringReduction(move(string{"bcab"})) << '\n';   // expected output: 1
  cout << StringReduction(move(string{"abcabc"})) << '\n'; // expected output: 2
  cout << StringReduction(move(string{"cccc"})) << '\n';   // expected output: 4
  cout << StringReduction(move(string{"aabc"})) << '\n';   // expected output: 1
  cout << StringReduction(move(string{"ccaa"})) << '\n';   // expected output: 2

  return 0;    
}
