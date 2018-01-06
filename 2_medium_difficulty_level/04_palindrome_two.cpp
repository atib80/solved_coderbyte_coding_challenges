/*
Coderbyte coding challenge: Palindrome Two

Using the C++ language, have the function PalindromeTwo(str) take the str parameter being passed and return the string true if the parameter is a palindrome, 
(the string is the same forward as it is backward) otherwise return the string false. The parameter entered may have punctuation and symbols but they should 
not affect whether the string is in fact a palindrome. For example: "Anne, I vote more cars race Rome-to-Vienna" should return true.

Sample test cases:

Input:  "Noel - sees Leon"
Output: "true"

Input:  "A war at Tarawa!"
Output: "true"
*/

#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <algorithm>

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

string PalindromeTwo(string str) { 

  str = trim(str);

  const size_t str_len { str.length() };

  if (1u == str_len) return "false";

  if ((2u == str_len) && (str[0] == str[1])) return "true";

  ostringstream oss{};

  for (const char c : str) {

    if (isalnum(c)) oss << static_cast<char>(tolower(c));

  }

  const string str1 { oss.str() };

  string str2 { str1 };

  reverse(begin(str2), end(str2));

  if (str1 == str2) return "true";

  return "false";
            
}

int main() { 
  
  // cout << PalindromeTwo(move(string{gets(stdin)}));
  cout << PalindromeTwo(move(string{"Anne, I vote more cars race Rome-to-Vienna"})) << '\n'; // expected: "true"
  cout << PalindromeTwo(move(string{"Noel - sees Leon"})) << '\n'; 							             // expected: "true"
  cout << PalindromeTwo(move(string{"A war at Tarawa!"})) << '\n'; 							             // expected: "true"

  return 0;
    
}
