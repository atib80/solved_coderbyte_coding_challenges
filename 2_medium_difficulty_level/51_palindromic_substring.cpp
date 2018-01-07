/*
Coderbyte coding challenge: Palindromic Substring

Using the C++ language, have the function PalindromicSubstring(str) take the str parameter being passed and find the longest palindromic substring,
which means the longest substring which is read the same forwards as it is backwards. For example: if str is "abracecars"
then your program should return the string racecar because it is the longest palindrome within the input string.

The input will only contain lowercase alphabetic characters. The longest palindromic substring will always be unique, 
but if there is none that is longer than 2 characters, return the string none.

Sample test cases:

Input:  "hellosannasmith"
Output: "sannas"

Input:  "abcdefgg"
Output: "none"
*/

#include <iostream>
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

bool check_if_current_substring_is_palindromic(const string& current_substring) {

  const size_t len { current_substring.length() };

  for (size_t i{}, j{len - 1}; i < j; i++, j--) {
  	if (current_substring[i] != current_substring[j]) return false;
  }

  // string reversed_currentsubstring{current_substring};
  // reverse(begin(reversed_currentsubstring), end(reversed_currentsubstring));
  // return (current_substring == reversed_currentsubstring);

  return true;
   
}

 string PalindromicSubstring(string str) { 

 str = trim(str);

  const size_t str_len { str.length() };

  if (str_len < 3u) return string{"none"};

   size_t current_substring_size { str_len };

   size_t current_substring_start_index{};
   
   while (current_substring_size > 2u) {

	   	if ((current_substring_start_index + current_substring_size) > str_len) {   		

	   		current_substring_size--;

	   		if (current_substring_size < 3u) return string{"none"};

	   		current_substring_start_index = 0u;

	   	}

	   const string current_substring { str.substr(current_substring_start_index, current_substring_size) };

	   if (check_if_current_substring_is_palindromic(current_substring)) {

	   	   return current_substring;
	   
	   }
	   
	   current_substring_start_index++;

    }
  
  return string{"none"};
            
}

int main() {

  // cout << PalindromicSubstring(move(string{gets(stdin)}));
  cout << PalindromicSubstring(move(string{"abracecars"})) << '\n';      // expected output: "racecar"
  cout << PalindromicSubstring(move(string{"hellosannasmith"})) << '\n'; // expected output: "sannas"
  cout << PalindromicSubstring(move(string{"abcdefgg"})) << '\n';        // expected output: "none"
  return 0;    
}
