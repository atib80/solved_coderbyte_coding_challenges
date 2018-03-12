/*
Coderbyte coding challenge: Caesar Cipher

Using the C++ language, have the function CaesarCipher(str,num) take the str
parameter and perform a Caesar Cipher shift on it using the num parameter as the
shifting number. A Caesar Cipher works by shifting each letter in the string N
places down in the alphabet (in this case N will be num). Punctuation, spaces,
and capitalization should remain intact. For example if the string is "Caesar
Cipher" and num is 2 the output should be "Ecguct Ekrjgt".

Sample test cases:

Input:  "Hello" & num = 4
Output: "Lipps"

Input:  "abc" & num = 0
Output: "abc"
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

string CaesarCipher(string str, size_t num) {
  str = trim(str);

  if (str.empty())
    return str;

  num %= 26;

  for (auto& ch : str) {
    if (isalpha(ch)) {
      if (islower(ch)) {
        if (ch + num > 122) {
          const size_t diff = ch + num - 123;
          ch = static_cast<char>(97 + diff);
        } else {
          ch = static_cast<char>(ch + num);
        }

      } else {
        if (ch + num > 90) {
          const size_t diff = ch + num - 91;
          ch = static_cast<char>(65 + diff);
        } else {
          ch = static_cast<char>(ch + num);
        }
      }
    }
  }

  return str;
}

int main() {
  // cout << CaesarCipher(gets(stdin));
  cout << CaesarCipher("Caesar Cipher", 2)
       << '\n';                                  // expected output: "Ecguct Ekrjgt"
  cout << CaesarCipher("Hello", 4) << '\n';      // expected output: "Lipps"
  cout << CaesarCipher("abc", 0) << '\n';        // expected output: "abc"
  cout << CaesarCipher("coderBYTE", 2) << '\n';  // expected output: "eqfgtDAVG"
  cout << CaesarCipher("dogs", 8) << '\n';       // expected output: "lwoa"
  cout << CaesarCipher("byte", 13) << '\n';      // expected output: "olgr"
  return 0;
}
