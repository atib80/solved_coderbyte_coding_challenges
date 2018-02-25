/*
Coderbyte coding challenge: Palindrome Swapper

Using the C++ language, have the function PalindromeSwapper(str) take the str
parameter being passed and determine if a palindrome can be created by swapping
two adjacent characters in the string. If it is possible to create a palindrome,
then your program should return the palindrome, if not then return the string
-1. The input string will only contain alphabetic characters.

For example: if str is "rcaecar" then you can create a palindrome by swapping
the second and third characters, so your program should return the string
racecar which is the final palindromic string.

Sample test cases:

Input:  "anna"
Output: "anna"

Input:  "kyaak"
Output: "kayak"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (!str_len)
    return string{};

  size_t first{}, last{str_len - 1};

  for (; first <= last; ++first) {
    if (!isspace(str[first]))
      break;
  }

  if (first > last)
    return string{};

  for (; last > first; --last) {
    if (!isspace(str[last]))
      break;
  }

  return str.substr(first, last - first + 1);
}

bool is_string_palindrome(const string& str) {
  string reversed_str{str};

  reverse(begin(reversed_str), end(reversed_str));

  if (str == reversed_str)
    return true;

  return false;
}

string palindrome_swapper(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (str_len < 2)
    return "-1";

  if ((2 == str_len) && (str[0] == str[1]))
    return str;

  if (is_string_palindrome(str))
    return str;

  for (size_t i{}; i < str_len - 1; i++) {
    swap(str[i], str[i + 1]);

    if (is_string_palindrome(str))
      return str;

    swap(str[i], str[i + 1]);
  }

  return "-1";
}

int main() {
  // cout << palindrome_swapper ( move ( string { gets(stdin) } ) );
  cout << palindrome_swapper(move(string{"madam"}))
       << '\n';  // expected output: "madam"
  cout << palindrome_swapper(move(string{"rcaecar"}))
       << '\n';  // expected output: "racecar"
  cout << palindrome_swapper(move(string{"anna"}))
       << '\n';  // expected output: "anna"
  cout << palindrome_swapper(move(string{"kyaak"}))
       << '\n';  // expected output: "kayak"
  return 0;
}
