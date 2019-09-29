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
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

char find_first_non_repeating_character_v1(string str) {
  unordered_set<char> visited_chars{' '};

  for (const char ch : str) {
    if (0U == visited_chars.count(ch)) {
      if (1 == count(begin(str), end(str), ch))
        return ch;
      visited_chars.emplace(ch);
    }
  }

  return 0;
}

char find_first_non_repeating_character_v2(string str) {
  vector<int> char_count(128U, 0);
  vector<char> char_sequence{};
  char_sequence.reserve(str.length());

  for (const char ch : str) {
    if (' ' != ch) {
      if (0 == char_count[ch])
        char_sequence.emplace_back(ch);
      ++char_count[ch];
    }
  }

  for (const char ch : char_sequence) {
    if (1 == char_count[ch])
      return ch;
  }

  return 0;
}

char find_first_non_repeating_character_v3(string str) {
  unordered_set<char> visited_chars{' '};

  for (size_t i{}; i < str.length(); ++i) {
    if (0U == visited_chars.count(str[i])) {
      if ((i == str.length() - 1) ||
          (i < str.length() - 1 && string::npos == str.find(str[i], i + 1)))
        return str[i];
      visited_chars.emplace(str[i]);
    }
  }

  return 0;
}

int main() {
  // cout << find_first_non_repeating_character_v2(gets(stdin));
  cout << find_first_non_repeating_character_v2("agettkgaeee")
       << '\n';  // expected output: 'k'
  cout << find_first_non_repeating_character_v2("abcdef")
       << '\n';  // expected output: 'a'
  cout << find_first_non_repeating_character_v2("hello world hi hey")
       << '\n';  // expected output: 'w'

  return 0;
}
