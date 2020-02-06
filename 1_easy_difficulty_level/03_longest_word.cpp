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

#include <algorithm>
#include <cassert>
#include <cctype>
#include <iostream>
#include <iterator>
#include <list>
#include <random>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <vector>

#include "../include/stl_helper_functions.hpp"

using namespace std;
using namespace stl::helper;

string LongestWord_v1(string sen) {
  size_t longest_first_word_length{}, longest_first_word_start_index{};
  size_t word_len{}, start_index{string::npos};

  for (size_t i{}; i < sen.length(); i++) {
    if (isalnum(sen[i])) {
      if (string::npos == start_index)
        start_index = i;
      word_len++;
    } else {
      if (word_len > longest_first_word_length) {
        longest_first_word_start_index = start_index;
        longest_first_word_length = word_len;
      }

      start_index = string::npos;
      word_len = 0;
    }
  }

  if (word_len > longest_first_word_length)
    return sen.substr(start_index, word_len);

  return sen.substr(longest_first_word_start_index, longest_first_word_length);
}

string LongestWord_v2(string sen) {
  const size_t sen_len{sen.length()};
  size_t start{};
  size_t longest_first_word_length{}, longest_first_word_start_index{};

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

    if (last - start > longest_first_word_length) {
      longest_first_word_start_index = start;
      longest_first_word_length = last - start;
    }

    start = last + 1;
  }

  return sen.substr(longest_first_word_start_index, longest_first_word_length);
}

string LongestWord_v3(string sen) {
  static std::random_device rd{};
  static constexpr const array<char, 63> allowed_chars{
      {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"}};

  vector<char> vector_of_allowed_chars_unsorted{cbegin(allowed_chars),
                                                cend(allowed_chars)};

  shuffle(begin(vector_of_allowed_chars_unsorted),
          end(vector_of_allowed_chars_unsorted), std::mt19937{rd()});

  list<char> list_of_allowed_chars_unsorted{
      cbegin(vector_of_allowed_chars_unsorted),
      cend(vector_of_allowed_chars_unsorted)};

  unordered_set<char> allowed_chars_hash_set{cbegin(allowed_chars),
                                             cend(allowed_chars)};

  vector<string> results(3);
  results[0] = find_longest_word(sen, allowed_chars_hash_set);
  results[1] = find_longest_word(sen, vector_of_allowed_chars_unsorted);
  results[2] = find_longest_word(sen, list_of_allowed_chars_unsorted);

  // sort(begin(results), end(results), [](const string& lhs, const string& rhs)
  // {
  //   return lhs.length() >= rhs.length();
  // });

  assert(results[0].length() == results[1].length() &&
         results[0].length() == results[2].length() &&
         results[1].length() == results[2].length());

  return move(results[0]);
}

int main() {
  // cout << LongestWord_v1(gets(stdin));
  cout << LongestWord_v3("fun&!! time") << '\n';  // expected output: "time"
  cout << LongestWord_v3("I love dogs") << '\n';  // expected output: "love"
  cout << LongestWord_v3("I love both cats and dogs as well!")
       << '\n';  // expected output: "love"

  return 0;
}
