/*
Coderbyte coding challenge: Swap II

Using the C++ language, have the function SwapII(str) take the str parameter and
swap the case of each character. Then, if a letter is between two numbers
(without separation), switch the places of the two numbers. For example: if str
is "6Hello4 -8World, 7 yes3" the output should be 4hELLO6 -8wORLD, 7 YES3.

Sample test cases:

Input:  "Hello -5LOL6"
Output: "hELLO -6lol5"

Input:  "2S 6 du5d4e"
Output: "2s 6 DU4D5E"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <utility>

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

void flip_character_case(char& ch) {
  if (islower(ch))
    ch = static_cast<char>(toupper(ch));

  else
    ch = static_cast<char>(tolower(ch));
}

string SwapII(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  size_t prev_digit_pos{string::npos};

  for (size_t i{}; i < str_len; i++) {
    if (isalpha(str[i]))
      flip_character_case(str[i]);

    else if (isdigit(str[i])) {
      if ((string::npos != prev_digit_pos) && isalpha(str[i - 1])) {
        swap(str[prev_digit_pos], str[i]);
        prev_digit_pos = string::npos;
      } else
        prev_digit_pos = i;

    } else
      prev_digit_pos = string::npos;
  }

  return str;
}

int main() {
  // cout << SwapII(move(string{gets(stdin)}));
  cout << SwapII(move(string{"6Hello4 -8World, 7 yes3"}))
       << '\n';  // expected output: "4hELLO6 -8wORLD, 7 YES3"
  cout << SwapII(move(string{"Hello -5LOL6"}))
       << '\n';  // expected output: "hELLO -6lol5"
  cout << SwapII(move(string{"2S 6 du5d4e"}))
       << '\n';  // expected output: "2s 6 DU4D5E"
  cout << SwapII(move(string{"123gg))(("}))
       << '\n';  // expected output: "123GG))(("

  return 0;
}
