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
#include <limits>
#include <map>
#include <queue>
#include <string>
#include <unordered_map>
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
  constexpr const size_t buffer_size{256U};
  constexpr const int int_max{numeric_limits<int>::max()};

  int char_index[buffer_size];
  fill(char_index, char_index + buffer_size, int_max);
  map<size_t, char> first_char_index;

  for (size_t i{}; i < str.length(); ++i) {
    if (' ' != str[i]) {
      if (int_max == char_index[static_cast<ptrdiff_t>(str[i])]) {
        first_char_index[i] = str[i];
        char_index[static_cast<ptrdiff_t>(str[i])] = i;
      } else if (-1 != char_index[static_cast<ptrdiff_t>(str[i])]) {
        first_char_index.erase(char_index[static_cast<ptrdiff_t>(str[i])]);
        char_index[static_cast<ptrdiff_t>(str[i])] = -1;
      }
    }
  }

  return !first_char_index.empty() ? cbegin(first_char_index)->second : 0;
}

char find_first_non_repeating_character_v3(string str) {
  if (str.empty())
    return 0;
  unordered_set<char> visited_chars{' '};

  for (size_t i{}; i < str.length() - 1; ++i) {
    if (0U == visited_chars.count(str[i])) {
      if (string::npos == str.find(str[i], i + 1))
        return str[i];
      visited_chars.emplace(str[i]);
    }
  }

  return str.back();
}

int main() {
  // cout << find_first_non_repeating_character_v3(gets(stdin));
  cout << find_first_non_repeating_character_v2("agettkgaeee")
       << '\n';  // expected output: 'k'
  cout << find_first_non_repeating_character_v2("abcdef")
       << '\n';  // expected output: 'a'
  cout << find_first_non_repeating_character_v2("hello world hi hey")
       << '\n';  // expected output: 'w'

  return 0;
}
