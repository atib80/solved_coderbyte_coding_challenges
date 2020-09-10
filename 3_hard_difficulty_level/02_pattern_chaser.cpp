/*
Coderbyte coding challenge: Pattern Chaser

Using the C++ language, have the function PatternChaser(str) take str which will
be a string and return the longest pattern within the string. A pattern for this
challenge will be defined as: if at least 2 or more adjacent characters within
the string repeat at least twice. So for example "aabecaa" contains the pattern
aa, on the other hand "abbbaac" doesn't contain any pattern. Your program should
return yes/no pattern/null. So if str were "aabejiabkfabed" the output should be
"yes abe". If str were "123224" the output should return "no null". The string
may either contain all characters (a through z only), integers, or both. But the
parameter will always be a string type. The maximum length for the string being
passed in will be 20 characters. If a string for example is "aa2bbbaacbbb" the
pattern is "bbb" and not "aa". You must always return the longest pattern
possible.

Sample test cases:

Input:  "da2kr32a2"
Output: "yes a2"

Input:  "sskfssbbb9bbb"
Output: "yes bbb"
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

bool check_current_string_pattern(const string& src_str,
                                  const size_t current_pattern_start_index,
                                  const size_t current_pattern_len) {
  for (size_t i{current_pattern_start_index + current_pattern_len};
       i < src_str.length(); i++) {
    if (src_str[i] == src_str[current_pattern_start_index] &&
        i + current_pattern_len <= src_str.length()) {
      bool found{true};
      for (size_t j{i + 1}, offset{1}; j < i + current_pattern_len;
           j++, offset++) {
        if (src_str[j] != src_str[current_pattern_start_index + offset]) {
          i = j - 1;
          found = false;
          break;
        }
      }

      if (found)
        return true;
    }
  }

  return false;
}

string pattern_chaser(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (str_len < 3)
    return "no null";

  size_t current_pattern_size{str_len / 2};

  size_t current_pattern_start_index{};

  while (current_pattern_size > 1) {
    if (current_pattern_start_index + 2 * current_pattern_size > str_len) {
      current_pattern_size--;

      if (current_pattern_size < 2)
        return "no null";

      current_pattern_start_index = 0;
    }

    if (check_current_string_pattern(str, current_pattern_start_index,
                                     current_pattern_size))
      return "yes " +
             str.substr(current_pattern_start_index, current_pattern_size);

    current_pattern_start_index++;
  }

  return "no null";
}

int main() {
  // cout << pattern_chaser(gets(stdin));
  cout << pattern_chaser("aabecaa") << '\n';  // expected output: "yes aa"
  cout << pattern_chaser("abbbaac") << '\n';  // expected output: "no null"
  cout << pattern_chaser("aabejiabkfabed") << '\n';  // expected output: "yes abe"
  cout << pattern_chaser("123224") << '\n';  // expected output: "no null"
  cout << pattern_chaser("aa2bbbaacbbb") << '\n';  // expected output: "yes bbb"
  cout << pattern_chaser("da2kr32a2") << '\n';  // expected output: "yes a2"
  cout << pattern_chaser("sskfssbbb9bbb") << '\n';  // expected output: "yes bbb"

  return 0;
}
