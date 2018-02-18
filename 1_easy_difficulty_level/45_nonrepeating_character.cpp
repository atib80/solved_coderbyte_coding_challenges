/*
Coderbyte coding challenge: Nonrepeating Character

Using the C++ language, have the function NonrepeatingCharacter(str) take the
str parameter being passed, which will contain only alphabetic characters and
spaces, and return the first non-repeating character. For example: if str is
"agettkgaeee" then your program should return k. The string will always contain
at least one character and there will always be at least one non-repeating
character.

Sample test cases:

Input:  "abcdef"
Output: "a"

Input:  "hello world hi hey"
Output: "w"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_set>

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

char find_first_non_repeating_character_v1(string str) {
  str = trim(str);

  for (const char ch : str) {
    if (!isspace(ch) && (1 == count(begin(str), end(str), ch)))
      return ch;
  }

  return 0;
}

char find_first_non_repeating_character_v2(string str) {
  str = trim(str);

  unordered_multiset<char> char_count(begin(str), end(str));

  for (const char ch : str) {
    if (!isspace(ch) && (1 == char_count.count(ch)))
      return ch;
  }

  return 0;
}

char find_first_non_repeating_character_v3(string str) {
  str = trim(str);

  for (size_t i{}; i < str.length(); i++) {
    if (!isspace(str[i]) &&
        ((i == str.length() - 1 ||
          (i < str.length() - 1 && string::npos == str.find(str[i], i + 1))) &&
         (!i || (i > 0 && string::npos == str.rfind(str[i], i - 1))))) {
      return str[i];
    }
  }

  return 0;
}

int main() {
  // cout << find_first_non_repeating_character_v3(move(string{gets(stdin)}));
  cout << find_first_non_repeating_character_v3(move(string{"agettkgaeee"}))
       << '\n';  // expected output: 'k'
  cout << find_first_non_repeating_character_v3(move(string{"abcdef"}))
       << '\n';  // expected output: 'a'
  cout << find_first_non_repeating_character_v3(
              move(string{"hello world hi hey"}))
       << '\n';  // expected output: 'w'

  return 0;
}
