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

#include <cctype>
#include <iostream>
#include <string>

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

string swap_case(string str) {
  str = trim(str);

  for (auto& ch : str) {
    if ((ch >= 'A') && (ch <= 'Z'))
      ch += ('a' - 'A');
    else if ((ch >= 'a') && (ch <= 'z'))
      ch -= ('a' - 'A');
  }

  return str;
}

int main() {
  // cout << swap_case(move(string{ gets(stdin) }));
  cout << swap_case(move(string{"Hello World"}))
       << '\n';  // expected output: "hELLO wORLD"
  cout << swap_case(move(string{"Hello-LOL"}))
       << '\n';  // expected output: "hELLO-lol"
  cout << swap_case(move(string{"Sup DUDE!!?"}))
       << '\n';  // expected output: "sUP dude!!?"

  return 0;
}
