/*
Coderbyte coding challenge: Camel Case

Using the C++ language, have the function CamelCase(str) take the str parameter
being passed and return it in proper camel case format where the first letter of
each word is capitalized (excluding the first letter). The string will only
contain letters and some combination of delimiter punctuation characters
separating each word.

For example: if str is "BOB loves-coding" then your program should return the
string bobLovesCoding.

Sample test cases:

Input:  "cats AND*Dogs-are Awesome"
Output: "catsAndDogsAreAwesome"

Input:  "a b c d-e-f%g"
Output: "aBCDEFG"
*/

#include <cctype>
#include <iostream>
#include <locale>
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

string convert_to_camel_case(string str, const locale& loc = locale{}) {
  str = trim(str);
  string final_str{};
  final_str.reserve(str.length());

  size_t si{};

  while (!isalpha(str[si]))
    si++;

  final_str.push_back(static_cast<char>(tolower(str[si], loc)));

  bool is_new_word{};

  for (size_t i{si + 1}; i < str.length(); i++) {
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

string CamelCase(string str) {
  return convert_to_camel_case(move(str));
}

int main() {
  // cout << CamelCase(move(string{gets(stdin)}));
  cout << CamelCase(move(string{"BOB loves-coding"}))
       << '\n';  // "bobLovesCoding"
  cout << CamelCase(move(string{"cats AND*Dogs-are Awesome"}))
       << '\n';  // "catsAndDogsAreAwesome"
  cout << CamelCase(move(string{"a b c d-e-f%g"})) << '\n';  // "aBCDEFG"

  return 0;
}
