/*
Coderbyte coding challenge: Snake Case

Using the C++ language, have the function SnakeCase(str) take the str parameter
being passed and return it in proper snake case format where each word is
lowercased and separated from adjacent words via an underscore. The string will
only contain letters and some combination of delimiter punctuation characters
separating each word. For example: if str is "BOB loves-coding" then your
program should return the string bob_loves_coding.

Sample test cases:

Input:  "cats AND*Dogs-are Awesome"
Output: "cats_and_dogs_are_awesome"

Input:  "a b c d-e-f%g"
Output: "a_b_c_d_e_f_g"
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

string convert_to_snake_case_v1(string str, const locale& loc = locale{}) {
  str = trim(str);
  string final_str{};
  final_str.reserve(str.length());

  size_t si{};
  while (!isalnum(str[si]))
    si++;

  final_str.push_back(static_cast<char>(tolower(str[si], loc)));
  si++;

  bool is_new_word{};

  for (size_t i{si}; i < str.length(); i++) {
    if (!isalnum(str[i])) {
      is_new_word = true;
      continue;
    }

    if (is_new_word) {
      final_str.push_back('_');
      is_new_word = false;
    }

    final_str.push_back(static_cast<char>(tolower(str[i], loc)));
  }

  final_str.shrink_to_fit();
  return final_str;
}

string convert_to_snake_case_v2(string str, const locale& loc = locale{}) {
  str = trim(str);

  ostringstream oss{};

  size_t si{};
  while (!isalnum(str[si]))
    si++;
  oss << static_cast<char>(tolower(str[si], loc));
  si++;

  bool is_new_word{};

  for (size_t i{si}; i < str.length(); i++) {
    if (!isalnum(str[i])) {
      is_new_word = true;
      continue;
    }

    if (is_new_word) {
      oss << '_';
      is_new_word = false;
    }

    oss << static_cast<char>(tolower(str[i], loc));
  }

  return oss.str();
}

string SnakeCase(string str) {
  return convert_to_snake_case_v2(move(str));
}

int main() {
  // cout << SnakeCase(move(string{gets(stdin)}));
  cout << SnakeCase(move(string{"BOB loves-coding"}))
       << '\n';  // expected output: bob_loves_coding
  cout << SnakeCase(move(string{"cats AND*Dogs-are Awesome"}))
       << '\n';  // expected output: cats_and_dogs_are_awesome
  cout << SnakeCase(move(string{"a b c d-e-f%g"}))
       << '\n';  // expected output: a_b_c_d_e_f_g

  return 0;
}
