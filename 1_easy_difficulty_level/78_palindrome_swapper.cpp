/*
Coderbyte coding challenge: Palindrome Swapper

Using the C++ language, have the function PalindromeSwapper(str) take the str parameter being passed and determine if a palindrome can be created 
by swapping two adjacent characters in the string. If it is possible to create a palindrome, then your program should return the palindrome, 
if not then return the string -1. The input string will only contain alphabetic characters.

For example: if str is "rcaecar" then you can create a palindrome by swapping the second and third characters, 
so your program should return the string racecar which is the final palindromic string.

Sample test cases:

Input:  "anna"
Output: "anna"

Input:  "kyaak"
Output: "kayak"
*/

#include <iostream>
#include <cctype>
#include <string>
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

bool is_string_palindrome(const string& str) {

  string reversed_str{str};
  
  reverse(begin(reversed_str), end(reversed_str));
  
  if (str == reversed_str) return true;
     
  return false;

}

string palindrome_swapper(string str) {

  str = trim(str);

  if (str.length() < 2u) return "-1";

  if ((2u == str.length()) && (str[0] == str[1])) return str;

  if (is_string_palindrome(str)) return str;

  for (size_t i{}; i != ( str.length() - 1 ); i++) {

  	swap(str[i], str[i + 1]);

  	if (is_string_palindrome(str)) return str;
  	
  	swap(str[i], str[i + 1]);

  }

  return "-1";
  
}

int main() { 
  
  // cout << palindrome_swapper ( move ( string { gets(stdin) } ) );
  cout << palindrome_swapper ( move ( string { "madam" } ) ) << '\n';   // expected output: "madam"
  cout << palindrome_swapper ( move ( string { "rcaecar" } ) ) << '\n'; // expected output: "racecar"
  cout << palindrome_swapper ( move ( string { "anna" } ) ) << '\n';    // expected output: "anna"
  cout << palindrome_swapper ( move ( string { "kyaak" } ) ) << '\n';   // expected output: "kayak"
  return 0;    
}
