/*
Coderbyte coding challenge: Different cases

Using the C++ language, have the function DifferentCases(str) take the str
parameter being passed and return it in upper camel case format where the first
letter of each word is capitalized. The string will only contain letters and
some combination of delimiter punctuation characters separating each word.

For example: if str is "Daniel LikeS-coding" then your program should return the
string DanielLikesCoding.

Sample test cases:

Input:  "cats AND*Dogs-are Awesome"
Output: "CatsAndDogsAreAwesome"

Input:  "a b c d-e-f%g"
Output: "ABCDEFG"
*/

#include <cctype>
#include <iostream>
#include <locale>
#include <sstream>
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

string convert_to_camel_case_v1(string str, const locale& loc = locale{}) {
  str = trim(str);
  string final_str{};
  const size_t str_len{str.length()};
  final_str.reserve(str_len);

  size_t si{};

  while (!isalpha(str[si]))
    si++;

  final_str.push_back(static_cast<char>(toupper(str[si], loc)));

  bool is_new_word{};

  for (size_t i{si + 1}; i < str_len; i++) {
    if (!isalnum(str[i])) {
      is_new_word = true;
      continue;
    }

    if (is_new_word) {
      final_str.push_back(static_cast<char>(toupper(str[i], loc)));
      is_new_word = false;
      continue;
    }

    final_str.push_back(static_cast<char>(tolower(str[i], loc)));
  }

  final_str.shrink_to_fit();
  return final_str;
}

string convert_to_camel_case_v2(string str, const locale& loc = locale{}) {
  str = trim(str);

  ostringstream oss{};

  size_t si{};

  while (!isalpha(str[si]))
    si++;

  oss << static_cast<char>(toupper(str[si], loc));

  bool is_new_word{};

  for (size_t i{si + 1}; i < str.length(); i++) {
    if (!isalnum(str[i])) {
      is_new_word = true;
      continue;
    }

    if (is_new_word) {
      oss << static_cast<char>(toupper(str[i], loc));
      is_new_word = false;
      continue;
    }

    oss << static_cast<char>(tolower(str[i], loc));
  }

  return oss.str();
}

string DifferentCases(string str) {
  return convert_to_camel_case_v1(move(str));
}

int main() {
  // cout << CamelCase(move(string{gets(stdin)}));
  cout << DifferentCases(string{"Daniel LikeS-coding"})
       << '\n';  // "DanielLikesCoding"
  cout << DifferentCases(string{"cats AND*Dogs-are Awesome"})
       << '\n';  // "CatsAndDogsAreAwesome"
  cout << DifferentCases(string{"a b c d-e-f%g"}) << '\n';  // "ABCDEFG"

  return 0;
}
