/*
54. Coderbyte coding challenge: Wildcards (difficulty level: hard)

Using the C++ language, have the function Wildcards(str) read str which will
contain two strings separated by a space. The first string will consist of the
following sets of characters: +, *, $, and {N} which is optional. The plus (+)
character represents a single alphabetic character, the ($) character represents
a number between 1-9, and the asterisk (*) represents a sequence of the same
character of length 3 unless it is followed by {N} which represents how many
characters should appear in the sequence where N will be at least 1. Your goal
is to determine if the second string exactly matches the pattern of the first
string in the input.

For example: if str is "++*{5} jtggggg" then the second string in this case does
match the pattern, so your program should return the string true. If the second
string does not match the pattern your program should return the string false.

Hard challenges are worth 15 points and you are not timed for them.

Sample test cases:

Input:  "+++++* abcdehhhhhh"
Output: "false"

Input:  "$**+*{2} 9mmmrrrkbb"
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

string Wildcards(string str) {
  str = trim(str);
  const size_t sep_char_pos{str.find(' ')};
  string pattern{str.substr(0, sep_char_pos)};

  // Uncommect the following code block if you intend to submit this code solution on coderbyte.
  /* 
  for (size_t i{}; i < pattern.length(); i++) {
    if ('$' == pattern[i]) {
      pattern.insert(i, 1, '$');
      i++;
    }
  }
  */

  const size_t pattern_len{pattern.length()};
  const string text{str.substr(sep_char_pos + 1)};
  const size_t text_len{text.length()};

  size_t pi{}, ti{};

  while (pi < pattern_len) {
    if ('$' == pattern[pi]) {
      if (ti >= text_len || text[ti] < '1' || text[ti] > '9')
        return "false";
      ti++;
      pi++;
    } else if ('+' == pattern[pi]) {
      if (ti >= text_len || !isalpha(text[ti]))
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
  // cout << Wildcards(string{gets(stdin)});
  cout << Wildcards(string{"++*{5} jtggggg"})
       << '\n';  // expected output: "true"
  cout << Wildcards(string{"+++++* abcdehhhhhh"})
       << '\n';  // expected output: "false"
  cout << Wildcards(string{"$**+*{2} 9mmmrrrkbb"})
       << '\n';  // expected output: "true"
  cout << Wildcards(string{"$$**+*{2} 77mmmrrrkbb"})
       << '\n';  // expected output: "true"
  cout << Wildcards(string{"$****{4}+++$ 8fffbbbeeerrrrmkou"})
       << '\n';  // expected output: "false"

  return 0;
}
