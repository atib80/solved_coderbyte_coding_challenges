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
#include <iterator>
#include <list>
#include <random>
#include <string>
#include <unordered_set>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <stl_helper_functions.hpp>
#define CATCH_CONFIG_MAIN

using namespace std;

string LongestWord_v1(string sen) {
  size_t longest_first_word_length{}, longest_first_word_start_index{};
  size_t word_len{}, start_index{string::npos};

  for (size_t i{}; i < sen.length(); ++i) {
    if (isalnum(sen[i])) {
      if (string::npos == start_index) {
        start_index = i;
      }
      ++word_len;
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

/* find_first_sequence_of_allowed_elements function template is
 * a less generic version of the std::search algorithm function template,
 * which allows the user to find in the input source range a consequtive
 * sequence of elements which are all present in the provided @haystack
 * container.
 */
// [1, 3, 4, 7, 8, 10) -> [1,2,3,4,5,6,7,8)
template <typename ForwardIterType, typename ContainerType>
std::pair<ForwardIterType, ForwardIterType>
find_first_sequence_of_allowed_elements(ForwardIterType start,
                                        ForwardIterType last,
                                        const ContainerType& haystack,
                                        const bool is_haystack_sorted = false) {
  using T = typename std::iterator_traits<ForwardIterType>::value_type;

  if (start == last)
    return {last, last};

  if constexpr (stl::helper::has_find_member_function_v<ContainerType, T>) {
    const auto first{
        std::find_if(start, last, [&haystack](const auto& current_element) {
          return std::cend(haystack) != haystack.find(current_element);
        })};
    if (last == first)
      return {last, last};
    auto second{first};
    ++second;
    second =
        std::find_if(second, last, [&haystack](const auto& current_element) {
          return std::cend(haystack) == haystack.find(current_element);
        });
    return {first, second};

  } else {
    if (is_haystack_sorted) {
      const auto first{
          find_if(start, last, [&haystack](const auto& current_element) {
            return std::binary_search(std::cbegin(haystack),
                                      std::cend(haystack), current_element);
          })};
      if (last == first)
        return {last, last};
      auto second{first};
      ++second;
      second =
          std::find_if(second, last, [&haystack](const auto& current_element) {
            return !std::binary_search(std::cbegin(haystack),
                                       std::cend(haystack), current_element);
          });

      return {first, second};
    } else {
      const auto first{
          std::find_if(start, last, [&haystack](const auto& current_element) {
            return std::cend(haystack) != std::find(std::cbegin(haystack),
                                                    std::cend(haystack),
                                                    current_element);
          })};
      if (last == first)
        return {last, last};
      auto second{first};
      ++second;
      second =
          std::find_if(second, last, [&haystack](const auto& current_element) {
            return std::cend(haystack) == std::find(std::cbegin(haystack),
                                                    std::cend(haystack),
                                                    current_element);
          });

      return {first, second};
    }
  }
}

/* find_longest_word function template finds the longest word in the provided
 * [first, last) source range of characters. The longest word may be comprised
 * of elements that are contained in the provided @haystack container only.
 */
template <typename IterType, typename ContainerType>
std::pair<IterType, IterType> find_longest_word(IterType first,
                                                const IterType last,
                                                ContainerType& haystack) {
  using T = typename std::iterator_traits<IterType>::value_type;
  using U = typename ContainerType::value_type;

  bool is_haystack_sorted{
      stl::helper::has_find_member_function_v<ContainerType, T> ||
      std::is_sorted(std::cbegin(haystack), std::cend(haystack))};

  if (!is_haystack_sorted) {
    if constexpr (stl::helper::has_sort_member_function_v<ContainerType>)
      haystack.sort();
    else if constexpr (std::is_same_v<std::random_access_iterator_tag,
                                      typename std::iterator_traits<
                                          typename ContainerType::iterator>::
                                          iterator_category>)
      std::sort(std::begin(haystack), std::end(haystack));
    is_haystack_sorted = true;
  }

  decltype(std::distance(first, last)) longest_first_word_length{};
  auto longest_first_word_start_iter = first;
  auto longest_first_word_last_iter = first;

  while (first != last) {
    const auto [seq_first, seq_last] = find_first_sequence_of_allowed_elements(
        first, last, haystack, is_haystack_sorted);

    if (seq_first == seq_last)
      break;

    const auto current_distance{std::distance(seq_first, seq_last)};

    if (current_distance > longest_first_word_length) {
      longest_first_word_length = current_distance;
      longest_first_word_start_iter = seq_first;
      longest_first_word_last_iter = seq_last;
    }

    first = seq_last;
  }

  return {longest_first_word_start_iter, longest_first_word_last_iter};
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

  vector<string> results{};
  results.reserve(3U);
  auto first_last_iter =
      find_longest_word(cbegin(sen), cend(sen), allowed_chars_hash_set);
  results.emplace_back(first_last_iter.first, first_last_iter.second);
  first_last_iter = find_longest_word(cbegin(sen), cend(sen),
                                      vector_of_allowed_chars_unsorted);
  results.emplace_back(first_last_iter.first, first_last_iter.second);
  first_last_iter =
      find_longest_word(cbegin(sen), cend(sen), list_of_allowed_chars_unsorted);
  results.emplace_back(first_last_iter.first, first_last_iter.second);

  // sort(begin(results), end(results), [](const string& lhs, const string& rhs)
  // {
  //   return lhs.length() >= rhs.length();
  // });

  assert(results[0].length() == results[1].length() &&
         results[0].length() == results[2].length() &&
         results[1].length() == results[2].length());

  return move(results[0]);
}

TEST_CASE("Longest Word : LongestWord_v1") {
  REQUIRE(LongestWord_v1("fun&!! time") == "time");
  REQUIRE(LongestWord_v1("I love dogs") == "love");
  REQUIRE(LongestWord_v1("I love both cats and dogs as well!") == "love");
}

TEST_CASE("Longest Word : LongestWord_v2") {
  REQUIRE(LongestWord_v2("fun&!! time") == "time");
  REQUIRE(LongestWord_v2("I love dogs") == "love");
  REQUIRE(LongestWord_v2("I love both cats and dogs as well!") == "love");
}

TEST_CASE("Longest Word : LongestWord_v3") {
  REQUIRE(LongestWord_v3("fun&!! time") == "time");
  REQUIRE(LongestWord_v3("I love dogs") == "love");
  REQUIRE(LongestWord_v3("I love both cats and dogs as well!") == "love");
}

// int main() {
//   // cout << LongestWord_v1(gets(stdin));
//   cout << LongestWord_v3("fun&!! time") << '\n';  // expected output: "time"
//   cout << LongestWord_v3("I love dogs") << '\n';  // expected output: "love"
//   cout << LongestWord_v3("I love both cats and dogs as well!")
//        << '\n';  // expected output: "love"
//
//   return 0;
// }
