/*
Coderbyte coding challenge: Swap Case

Using the C++ language, have the function SwapCase(str) take the str parameter
and swap the case of each character. For example: if str is "Hello World" the
output should be hELLO wORLD. Let numbers and symbols stay the way they are.

Sample test cases:

Input:  "Hello-LOL"
Output: "hELLO-lol"

Input:  "Sup DUDE!!?"
Output: "sUP dude!!?"
*/

#include <algorithm>
#include <array>
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

std::string trim(const std::string& src,
                 const char* chars_to_trim = " \t\n\f\v\r") {
  if (0U == src.length())
    return {};

  const std::unordered_set<char> trimmed_chars(
      chars_to_trim, chars_to_trim + strlen(chars_to_trim));

  const auto first{std::find_if(
      std::cbegin(src), std::cend(src), [&trimmed_chars](const char ch) {
        return trimmed_chars.find(ch) == std::cend(trimmed_chars);
      })};

  if (first == std::cend(src))
    return {};

  const auto last{std::find_if(std::crbegin(src), std::crend(src),
                               [&trimmed_chars](const char ch) {
                                 return trimmed_chars.find(ch) ==
                                        std::cend(trimmed_chars);
                               })
                      .base()};

  return {first, last};
}

string swap_case_v1(string str) {
  str = trim(str);

  const int offset{'a' - 'A'};

  transform(cbegin(str), cend(str), begin(str), [&offset](const char ch) {
    if (ch >= 'a' && ch <= 'z')
      return static_cast<char>(ch - offset);
    else if (ch >= 'A' && ch <= 'Z')
      return static_cast<char>(ch + offset);
    return ch;
  });

  return str;
}

template <int offset1, int offset2>
struct character_offsets {
  int offsets[256U];

  constexpr character_offsets() : offsets{} {
    for (char i{'A'}, j{'a'}; i <= 'Z'; ++i, ++j) {
      offsets[i] = offset1;
      offsets[j] = offset2;
    }
  }
};

template <int char_offset1, int char_offset2>
using co = character_offsets<char_offset1, char_offset2>;

string swap_case_v2(string str) {
  constexpr co<'a' - 'A', 'A' - 'a'> char_offsets{};

  str = trim(str);

  transform(cbegin(str), cend(str), begin(str), [&char_offsets](const char ch) {
    return static_cast<char>(ch + char_offsets.offsets[ch]);
  });

  return str;
}

int main() {
  // cout << swap_case_v2(gets(stdin));
  cout << swap_case_v2("Hello World")
       << '\n';                               // expected output: "hELLO wORLD"
  cout << swap_case_v2("Hello-LOL") << '\n';  // expected output: "hELLO-lol"
  cout << swap_case_v2("Sup DUDE!!?")
       << '\n';  // expected output: "sUP dude!!?"

  return 0;
}
