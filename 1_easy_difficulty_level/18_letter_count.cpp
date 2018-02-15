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
#include <iostream>
#include <string>
#include <utility>
#include <vector>

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

vector<string> split(const string& source,
                     const char* needle,
                     size_t const max_count = string::npos) {
  vector<string> parts{};

  string needle_st{needle};

  const size_t source_len{source.length()};

  const size_t needle_len{needle_st.size()};

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
    const size_t current{source.find(needle_st, prev)};

    if (string::npos == current)
      break;

    number_of_parts++;

    if ((string::npos != max_count) && (parts.size() == max_count))
      break;

    if ((current - prev) > 0)
      parts.emplace_back(source.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (prev < source_len) {
    if (string::npos == max_count)
      parts.emplace_back(source.substr(prev));

    else if ((string::npos != max_count) && (parts.size() < max_count))
      parts.emplace_back(source.substr(prev));
  }

  return parts;
}

string LetterCountI(string str) {
  str = trim(str);

  const vector<string> words{split(str, " ")};

  int max_rep_characters{1};
  string found_word{};

  for (const auto& word : words) {
    int rep_char_count{};

    for (const char ch : word) {
      const int ch_freq = count(begin(word), end(word), ch);

      if (ch_freq > 1)
        rep_char_count += ch_freq;
    }

    if (rep_char_count > max_rep_characters) {
      max_rep_characters = rep_char_count;
      found_word = word;
    }
  }

  if (max_rep_characters > 1)
    return found_word;

  return "-1";
}

int main() {
  // cout << LetterCountI(move(string{gets(stdin)}));
  cout << LetterCountI(move(string{"Today, is the greatest day ever!"}))
       << '\n';  // expected output: "greatest"
  cout << LetterCountI(move(string{"Hello apple pie"}))
       << '\n';  // expected output: "Hello"
  cout << LetterCountI(move(string{"No words"}))
       << '\n';  // expected output: "-1"

  return 0;
}
