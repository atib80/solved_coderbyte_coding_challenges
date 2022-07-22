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
// #include <cctype>
#include <cstring>
// #include <iostream>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
// #include <utility>
#include <stl_helper_functions.hpp>
#include <vector>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

using namespace std;

string LetterCountI_v1(string str) {
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

    if (last - start > count_of_max_repeated_letters) {
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
    }

    start = last + 1;
  }

  if (count_of_max_repeated_letters > 1)
    return string{word.data(), word.length()};

  return "-1";
}

string LetterCountI_v2(string str) {
  vector<string> words{stl::helper::str_split(str, " \t\f\v\n\r", "")};

  bool found_word_with_repeated_characters{};

  stable_sort(begin(words), end(words),
              [&found_word_with_repeated_characters](const string& lhs,
                                                     const string& rhs) {
                unordered_map<char, size_t> char_count_lhs{};
                unordered_map<char, size_t> char_count_rhs{};
                const size_t lhs_len{lhs.length()};
                const size_t rhs_len{rhs.length()};
                const size_t min_len{!(lhs_len > rhs_len) ? lhs_len : rhs_len};
                const size_t max_len{!(lhs_len < rhs_len) ? lhs_len : rhs_len};
                const string& max_word{!(lhs_len < rhs_len) ? lhs : rhs};
                unordered_map<char, size_t>& char_count_max{
                    !(lhs_len < rhs_len) ? char_count_lhs : char_count_rhs};

                unordered_set<char> characters{};

                for (size_t i{}; i < min_len; ++i) {
                  char_count_lhs[lhs[i]]++;
                  char_count_rhs[rhs[i]]++;
                  if (0U == characters.count(lhs[i]))
                    characters.insert(lhs[i]);
                  if (0U == characters.count(rhs[i]))
                    characters.insert(rhs[i]);
                }

                for (size_t i{min_len}; i < max_len; ++i) {
                  char_count_max[max_word[i]]++;
                  if (0U == characters.count(max_word[i]))
                    characters.insert(max_word[i]);
                }

                size_t rep_char_count_lhs{}, rep_char_count_rhs{};

                for (const char ch : characters) {
                  if (char_count_lhs[ch] > 1U) {
                    rep_char_count_lhs += char_count_lhs[ch];
                    found_word_with_repeated_characters = true;
                  }
                  if (char_count_rhs[ch] > 1U) {
                    rep_char_count_rhs += char_count_rhs[ch];
                    found_word_with_repeated_characters = true;
                  }
                }

                return rep_char_count_lhs > rep_char_count_rhs;
              });

  if (found_word_with_repeated_characters)
    return move(words[0]);

  return "-1";
}

string LetterCountI_v3(string str) {
  size_t max_number_of_repeated_letters{1U};
  size_t found_word_index{string::npos};

  vector<string> words{stl::helper::str_split(str, " \t\f\v\n\r", "")};

  for (size_t i{}; i < words.size(); ++i) {
    const string& w{words.at(i)};
    multiset<char> word_char_frequencies{cbegin(w), cend(w)};
    if (w.length() <= max_number_of_repeated_letters)
      continue;

    unordered_set<char> unique_chars{cbegin(w), cend(w)};
    if ((unique_chars.size() == w.length()) ||
        ((word_char_frequencies.size() - unique_chars.size()) * 2 <=
         max_number_of_repeated_letters))
      continue;

    size_t repeated_char_count{};
    for (const char ch : unique_chars) {
      if (word_char_frequencies.count(ch) > 1U)
        repeated_char_count += word_char_frequencies.count(ch);
    }

    if (repeated_char_count > max_number_of_repeated_letters) {
      max_number_of_repeated_letters = repeated_char_count;
      found_word_index = i;
    }
  }

  if (string::npos != found_word_index)
    return move(words[found_word_index]);

  return "-1";
}

TEST_CASE("Letter Count I : LetterCountI_v1") {
  CHECK(LetterCountI_v1("Today, is the greatest day ever!") == "greatest");
  CHECK(LetterCountI_v1("Hello apple pie") == "Hello");
  CHECK(LetterCountI_v1("No words") == "-1");
}

TEST_CASE("Letter Count I : LetterCountI_v2") {
  CHECK(LetterCountI_v2("Today, is the greatest day ever!") == "greatest");
  CHECK(LetterCountI_v2("Hello apple pie") == "Hello");
  CHECK(LetterCountI_v2("No words") == "-1");
}

TEST_CASE("Letter Count I : LetterCountI_v3") {
  CHECK(LetterCountI_v3("Today, is the greatest day ever!") == "greatest");
  CHECK(LetterCountI_v3("Hello apple pie") == "Hello");
  CHECK(LetterCountI_v3("No words") == "-1");
}

// int main() {
//   // cout << LetterCountI_v3(gets(stdin));
//   cout << LetterCountI_v3("Today, is the greatest day ever!")
//        << '\n';  // expected output: "greatest"
//   cout << LetterCountI_v3("Hello apple pie")
//        << '\n';                                 // expected output: "Hello"
//   cout << LetterCountI_v3("No words") << '\n';  // expected output: "-1"

//   return 0;
// }
