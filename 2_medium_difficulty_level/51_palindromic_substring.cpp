/*
Coderbyte coding challenge: Palindromic Substring

Using the C++ language, have the function PalindromicSubstring(str) take the str
parameter being passed and find the longest palindromic substring, which means
the longest substring which is read the same forwards as it is backwards. For
example: if str is "abracecars" then your program should return the string
racecar because it is the longest palindrome within the input string.

The input will only contain lowercase alphabetic characters. The longest
palindromic substring will always be unique, but if there is none that is longer
than 2 characters, return the string none.

Sample test cases:

Input:  "hellosannasmith"
Output: "sannas"

Input:  "abcdefgg"
Output: "none"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

string trim(const string& input) {
  string output{input};
  output.erase(begin(output),
               find_if(begin(output), end(output),
                       [](const char ch) { return !isspace(ch); }));

  output.erase(find_if(output.rbegin(), output.rend(),
                       [](const char ch) { return !isspace(ch); })
                   .base(),
               end(output));

  return output;
}

bool check_if_current_substring_is_palindromic(
    const string& str,
    const size_t start_index,
    const size_t current_substr_len) {
  for (size_t i{start_index}, j{start_index + current_substr_len - 1}; i < j;
       i++, j--) {
    if (str[i] != str[j])
      return false;
  }

  return true;
}

string PalindromicSubstring(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (str_len < 3)
    return "none";

  size_t current_substr_len{str_len};
  size_t current_substring_start_index{};

  while (current_substr_len > 2) {
    if (current_substring_start_index + current_substr_len > str_len) {
      current_substr_len--;

      if (current_substr_len < 3)
        return "none";

      current_substring_start_index = 0;
    }

    if (check_if_current_substring_is_palindromic(
            str, current_substring_start_index, current_substr_len)) {
      return str.substr(current_substring_start_index, current_substr_len);
    }

    current_substring_start_index++;
  }

  return "none";
}

int main() {
  // cout << PalindromicSubstring(move(string{gets(stdin)}));
  cout << PalindromicSubstring(move(string{"abracecars"}))
       << '\n';  // expected output: "racecar"
  cout << PalindromicSubstring(move(string{"hellosannasmith"}))
       << '\n';  // expected output: "sannas"
  cout << PalindromicSubstring(move(string{"abcdefgg"}))
       << '\n';  // expected output: "none"
  return 0;
}
