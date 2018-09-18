/*
84. Coderbyte coding challenge: String changes (difficulty level: easy)

Using the C++ language, have the function StringChanges(str) take the str
parameter being passed, which will be a string containing letters from the
alphabet, and return a new string based on the following rules. Whenever a
capital M is encountered, duplicate the previous character (then remove the M),
and whenever a capital N is encountered remove the next character from the
string (then remove the N). All other characters in the string will be lowercase
letters. For example: "abcNdgM" should return "abcgg". The final string will
never be empty. Sample Test Cases

Input:  "MrtyNNgMM"
Output: "rtyggg"

Input:  "oMoMkkNrrN"
Output: "ooookkr"
*/

#include <iostream>
#include <string>

using namespace std;

string StringChanges(const string& str) {
  const size_t str_len{str.length()};
  string output{};
  output.reserve(str_len);

  size_t i{};

  char prev_char{};

  while (i < str_len) {
    if ('M' == str[i]) {
      if (prev_char)
        output.push_back(prev_char);
    } else if ('N' == str[i])
      i++;
    else {
      prev_char = str[i];
      output.push_back(str[i]);
    }
    i++;
  }

  return output;
}

int main() {
  // cout << StringChanges(gets(stdin));
  cout << StringChanges("abcNdgM") << '\n';     // expected output: "abcgg"
  cout << StringChanges("MrtyNNgMM") << '\n';   // expected output: "rtyggg"
  cout << StringChanges("oMoMkkNrrN") << '\n';  // expected output: "ooookkr"
  return 0;
}
