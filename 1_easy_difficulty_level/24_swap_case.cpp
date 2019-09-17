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

string swap_case(string str) {
  str = trim(str);

  for (auto& ch : str) {
    if (isalpha(ch)) {
      if (islower(ch))
        ch = static_cast<char>(toupper(ch));
      else
        ch = static_cast<char>(tolower(ch));
    }
  }

  return str;
}

int main() {
  // cout << swap_case(gets(stdin));
  cout << swap_case("Hello World") << '\n';  // expected output: "hELLO wORLD"
  cout << swap_case("Hello-LOL") << '\n';    // expected output: "hELLO-lol"
  cout << swap_case("Sup DUDE!!?") << '\n';  // expected output: "sUP dude!!?"

  return 0;
}
