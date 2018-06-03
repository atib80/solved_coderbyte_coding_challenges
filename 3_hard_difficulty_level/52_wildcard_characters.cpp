/*
Coderbyte coding challenge: Wildcard Characters

Using the C++ language, have the function WildcardCharacters(str) read str which
will contain two strings separated by a space. The first string will consist of
the following sets of characters: +, *, and {N} which is optional. The plus (+)
character represents a single alphabetic character, the asterisk (*) represents
a sequence of the same character of length 3 unless it is followed by {N} which
represents how many characters should appear in the sequence where N will be at
least 1. Your goal is to determine if the second string exactly matches the
pattern of the first string in the input.

For example: if str is "++*{5} gheeeee" then the second string in this case does
match the pattern, so your program should return the string true. If the second
string does not match the pattern your program should return the string false.

Sample Test Cases

Input:  "+++++* abcdemmmmmm"
Output: "false"

Input:  "**+*{2} mmmrrrkbb"
Output: "true"
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

string WildcardCharacters(string str) {
  str = trim(str);
  const size_t sep_char_pos{str.find(' ')};
  const string pattern{str.substr(0, sep_char_pos)};
  const size_t pattern_len{pattern.length()};
  const string text{str.substr(sep_char_pos + 1)};
  const size_t text_len{text.length()};

  size_t pi{}, ti{};

  while (pi < pattern_len) {
    if ('+' == pattern[pi]) {
      if (ti >= text_len)
        return "false";
      ti++;
      pi++;
    } else if ('*' == pattern[pi]) {
      size_t count{3u};

      if (pi + 1 == pattern.find("{", pi + 1)) {
        const size_t ei{pattern.find("}", pi + 2)};

        if (string::npos != ei && ei > pi + 2) {
          count = stoul(pattern.substr(pi + 2, ei - (pi + 2)));
          pi = ei + 1;
        }
      } else {
        pi++;
      }

      if (ti > text_len - count)
        return "false";

      const auto first_char = text[ti];

      for (size_t i{ti + 1}; i < ti + count; i++) {
        if (first_char != text[i])
          return "false";
      }

      ti += count;
    }
  }

  if (ti < text_len)
    return "false";

  return "true";
}

int main() {
  // cout << WildcardCharacters(string{gets(stdin)});
  cout << WildcardCharacters(string{"++*{5} gheeeee"})
       << '\n';  // expected output: "true"
  cout << WildcardCharacters(string{"+++++* abcdemmmmmm"})
       << '\n';  // expected output: "false"
  cout << WildcardCharacters(string{"**+*{2} mmmrrrkbb"})
       << '\n';  // expected output: "true"

  return 0;
}
