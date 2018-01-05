/*
Coderbyte coding challenge: Nonrepeating Character

Using the C++ language, have the function NonrepeatingCharacter(str) take the str parameter being passed, which will contain only alphabetic characters and spaces, 
and return the first non-repeating character. For example: if str is "agettkgaeee" then your program should return k. 
The string will always contain at least one character and there will always be at least one non-repeating character.

Sample test cases:

Input:  "abcdef"
Output: "a"

Input:  "hello world hi hey"
Output: "w"
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

char find_first_non_repeating_character(string str) {

  str = trim(str); 
  
  for (const char ch : str) {
  
      if (!isspace(ch) && (1 == count(begin(str), end(str), ch))) return ch;      
  }

  return 0;

}

int main() { 
  
  // cout << find_first_non_repeating_character(move(string{gets(stdin)}));
  cout << find_first_non_repeating_character(move(string{"agettkgaeee"})) << '\n';        // expected output: 'k'
  cout << find_first_non_repeating_character(move(string{"abcdef"})) << '\n';             // expected output: 'a'
  cout << find_first_non_repeating_character(move(string{"hello world hi hey"})) << '\n'; // expected output: 'w'

  return 0;

}
