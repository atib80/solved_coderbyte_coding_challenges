/*
Coderbyte coding challenge: Longest Word

Using the C++ language, have the function LongestWord(sen) take the sen
parameter being passed and return the largest word in the string. If there are
two or more words that are the same length, return the first word from the
string with that length. Ignore punctuation and assume sen will not be empty.

Sample test cases:

Input:  "fun&!! time"
Output: "time"

Input:  "I love dogs"
Output: "love"
*/

#include <cctype>
#include <iostream>
#include <string>

using namespace std;

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (!str_len)
    return string{};

  size_t begin_str{};
  size_t end_str{str_len - 1};

  for (; begin_str <= end_str; ++begin_str) {
    if (!isspace(str[begin_str]))
      break;
  }

  if (begin_str > end_str)
    return string{};

  for (; end_str > begin_str; --end_str) {
    if (!isspace(str[end_str]))
      break;
  }

  return str.substr(begin_str, end_str - begin_str + 1);
}

string LongestWord_v1(string sen) {
  sen = trim(sen);

  size_t word_len{}, start_index{string::npos};
  size_t max_word_len{};
  string longest_first_word{};

  for (size_t i{}; i < sen.length(); i++) {
    if (isalnum(sen[i])) {
      if (string::npos == start_index)
        start_index = i;
      word_len++;
      continue;
    }

    if ((word_len > max_word_len) && (string::npos != start_index)) {
      max_word_len = word_len;
      longest_first_word = sen.substr(start_index, word_len);
    } else if (!word_len)
      continue;

    start_index = string::npos;
    word_len = 0;
  }

  if ((word_len > max_word_len) && (string::npos != start_index)) {
    longest_first_word = sen.substr(start_index, word_len);
  }

  return longest_first_word;
}

string LongestWord_v2(string sen) {
  sen = trim(sen);

  const size_t sen_len{sen.length()};
  size_t start{}, max_word_len{};
  string longest_first_word{};

  while (start < sen_len) {
    start = sen.find_first_of(
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
        start);

    if (string::npos == start)
      break;

    size_t last{sen.find_first_not_of(
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
        start + 1)};

    if (string::npos == last)
      last = sen_len;

    if (last - start > max_word_len) {
      max_word_len = last - start;
      longest_first_word = sen.substr(start, last - start);
    }

    start = last + 1;
  }

  return longest_first_word;
}

int main() {
  // cout << LongestWord_v2(gets(stdin));
  cout << LongestWord_v2(move(string{"fun&!! time"}))
       << '\n';  // expected output: "time"
  cout << LongestWord_v2(move(string{"I love dogs"}))
       << '\n';  // expected output: "love"
  cout << LongestWord_v2(move(string{"I love both cats and dogs as well!"}))
       << '\n';  // expected output: "love"

  return 0;
}
