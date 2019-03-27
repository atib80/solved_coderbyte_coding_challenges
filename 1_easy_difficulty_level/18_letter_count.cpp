/*
Coderbyte coding challenge: Letter Count I

Using the C++ language, have the function LetterCountI(str) take the str
parameter being passed and return the first word with the greatest number of
repeated letters. For example: "Today, is the greatest day ever!" should return
greatest because it has 2 e's (and 2 t's) and it comes before ever which also
has 2 e's. If there are no words with repeating letters return -1. Words will be
separated by spaces.

Sample test cases:

Input:  "Hello apple pie"
Output: "Hello"

Input:  "No words"
Output: -1
*/

#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (!str_len)
    return {};

  size_t first{}, last{str_len - 1};

  for (; first <= last; ++first) {
    if (!isspace(str[first]))
      break;
  }

  if (first > last)
    return {};

  for (; last > first; --last) {
    if (!isspace(str[last]))
      break;
  }

  return str.substr(first, last - first + 1);
}

vector<string> split(const string& source,
                     const char* needle,
                     size_t const max_count = string::npos) {
  vector<string> parts{};
  const size_t source_len{source.length()};
  const size_t needle_len{strlen(needle)};

  if (!source_len)
    return parts;

  if (!needle_len) {
    const size_t upper_limit{max_count < source_len ? max_count : source_len};
    for (size_t i{}; i < upper_limit; i++)
      parts.emplace_back(1, source[i]);
    return parts;
  }

  size_t number_of_parts{}, prev{};

  while (true) {
    const size_t current{source.find(needle, prev)};

    if (string::npos == current)
      break;

    number_of_parts++;

    if (string::npos != max_count && parts.size() == max_count)
      break;

    if (current - prev > 0)
      parts.emplace_back(source.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (prev < source_len) {
    if (string::npos == max_count)
      parts.emplace_back(source.substr(prev));

    else if (parts.size() < max_count)
      parts.emplace_back(source.substr(prev));
  }

  return parts;
}

string LetterCountI_v1(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  size_t start{};
  size_t count_of_max_repeated_letters{1};
  string_view word{};

  while (start < str_len) {
    start = str.find_first_not_of(' ', start);

    if (string::npos == start)
      break;

    size_t last{str.find_first_of(' ', start + 1)};

    if (string::npos == last)
      last = str_len;

    unordered_map<char, size_t> char_count{};

    for (size_t i{start}; i < last; i++)
      char_count[str[i]]++;

    size_t rep_char_count{};

    for (const auto& p : char_count) {
      if (p.second > 1)
        rep_char_count += p.second;
    }

    if (rep_char_count > count_of_max_repeated_letters) {
      count_of_max_repeated_letters = rep_char_count;
      word = string_view{str.c_str() + start, last - start};
    }

    start = last + 1;
  }

  if (count_of_max_repeated_letters > 1)
    return string{word.data(), word.length()};

  return "-1";
}

string LetterCountI_v2(string str) {
  str = trim(str);

  const vector<string> words{split(str, " ")};

  size_t count_of_max_repeated_letters{1};
  size_t found_word_index{string::npos};

  for (size_t i{}; i < words.size(); i++) {
    unordered_map<char, size_t> char_count{};

    for (const char ch : words[i])
      char_count[ch]++;

    size_t rep_char_count{};

    for (const auto& p : char_count) {
      if (p.second > 1)
        rep_char_count += p.second;
    }

    if (rep_char_count > count_of_max_repeated_letters) {
      count_of_max_repeated_letters = rep_char_count;
      found_word_index = i;
    }
  }

  if (count_of_max_repeated_letters > 1 && string::npos != found_word_index)
    return words[found_word_index];

  return "-1";
}

int main() {
  // cout << LetterCountI_v2(gets(stdin));
  cout << LetterCountI_v2("Today, is the greatest day ever!")
       << '\n';  // expected output: "greatest"
  cout << LetterCountI_v2("Hello apple pie")
       << '\n';                                 // expected output: "Hello"
  cout << LetterCountI_v2("No words") << '\n';  // expected output: "-1"

  return 0;
}
