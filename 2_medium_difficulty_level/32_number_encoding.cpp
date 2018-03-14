/*
Coderbyte coding challenge: Number Encoding

Using the C++ language, have the function NumberEncoding(str) take the str
parameter and encode the message according to the following rule: encode every
letter into its corresponding numbered position in the alphabet. Symbols and
spaces will also be used in the input. For example: if str is "af5c a#!" then
your program should return 1653 1#!.

Sample test cases:

Input:  "hello 45"
Output: 85121215 45

Input:  "jaj-a"
Output: 10110-1
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
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

string NumberEncoding(string str) {
  static const string alphabet_str{"abcdefghijklmnopqrstuvwxyz"};

  str = trim(str);

  ostringstream oss{};

  for (size_t i{}; i < str.length(); i++) {
    str[i] = static_cast<char>(tolower(str[i]));
    const size_t index{alphabet_str.find(str[i])};

    if (string::npos == index) {
      oss << str[i];
      continue;
    }

    oss << index + 1;
  }

  return oss.str();
}

int main() {
  // cout << NumberEncoding(move(string{gets(stdin)}));
  cout << NumberEncoding(move(string{"af5c a#!"}))
       << '\n';  // expected output: 1653 1#!
  cout << NumberEncoding(move(string{"hello 45"}))
       << '\n';  // expected output: 85121215 45
  cout << NumberEncoding(move(string{"jaj-a"}))
       << '\n';  // expected output: 10110-1
  cout << NumberEncoding(move(string{"km#e"}))
       << '\n';  // expected output: 1113#5
  cout << NumberEncoding(move(string{"af5c a#!"}))
       << '\n';  // expected output: 1653 1#!
  cout << NumberEncoding(move(string{"---fc9#"}))
       << '\n';  // expected output: ---639#

  return 0;
}
