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

using std::array;
using std::begin;
using std::binary_search;
using std::cbegin;
using std::cend;
using std::cout;
using std::declval;
using std::distance;
using std::end;
using std::false_type;
using std::find;
using std::find_if;
using std::forward;
using std::iterator_traits;
using std::list;
using std::make_pair;
using std::move;
using std::mt19937;
using std::pair;
using std::random_device;
using std::shuffle;
using std::sort;
using std::string;
using std::true_type;
using std::unordered_set;
using std::vector;
using std::void_t;

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

template <typename T>
using has_sort_member_function_t = decltype(declval<T&>().sort());

template <typename T, typename = void>
struct has_sort_member_function : false_type {};

template <typename T>
struct has_sort_member_function<T, void_t<has_sort_member_function_t<T>>>
    : true_type {};

template <typename T>
constexpr const bool has_sort_member_function_v =
    has_sort_member_function<T>::value;

template <typename ForwardIterType, typename ContainerType>
pair<ForwardIterType, ForwardIterType> find_first_sequence_of_allowed_elements(
    ForwardIterType start,
    ForwardIterType last,
    const ContainerType& haystack,
    const bool is_haystack_sorted = false) {
  using T = typename iterator_traits<ForwardIterType>::value_type;

  if (start == last)
    return {last, last};

  if constexpr (has_find_member_function_v<ContainerType, T>) {
    const auto first{
        find_if(start, last, [&haystack](const auto& current_element) {
          return cend(haystack) != haystack.find(current_element);
        })};
    if (first == last)
      return {last, last};
    auto second{first};
    ++second;
    second = find_if(second, last, [&haystack](const auto& current_element) {
      return cend(haystack) == haystack.find(current_element);
    });
    return {first, second};

  } else {
    if (is_haystack_sorted) {
      const auto first{
          find_if(start, last, [&haystack](const auto& current_element) {
            return binary_search(cbegin(haystack), cend(haystack),
                                 current_element);
          })};
      if (last == first)
        return {last, last};
      auto second{first};
      ++second;
      second = find_if(second, last, [&haystack](const auto& current_element) {
        return !binary_search(cbegin(haystack), cend(haystack),
                              current_element);
      });

      return {first, second};
    } else {
      const auto first{
          find_if(start, last, [&haystack](const auto& current_element) {
            return cend(haystack) !=
                   find(cbegin(haystack), cend(haystack), current_element);
          })};
      if (last == first)
        return {last, last};
      auto second{first};
      ++second;
      second = find_if(second, last, [&haystack](const auto& current_element) {
        return cend(haystack) ==
               find(cbegin(haystack), cend(haystack), current_element);
      });

      return {first, second};
    }
  }
}

template <typename StringType, typename ContainerType>
StringType find_longest_word(const StringType& src, ContainerType& haystack) {
  using T = typename StringType::value_type;
  using U = typename ContainerType::value_type;

  bool is_haystack_sorted{has_find_member_function_v<ContainerType, T>};

  if constexpr (!has_find_member_function_v<ContainerType, T> &&
                ((has_sort_member_function_v<ContainerType> &&
                  is_operator_less_than_defined_v<U>) ||
                 is_operator_less_than_defined_v<U>)) {
    if constexpr (has_sort_member_function_v<ContainerType>)
      haystack.sort();
    else
      sort(begin(haystack), end(haystack));
    is_haystack_sorted = true;
  }

  auto next_iter = cbegin(src);
  const auto last_iter = cend(src);

  decltype(distance(next_iter, last_iter)) longest_first_word_length{};
  auto longest_first_word_start_iter = next_iter;
  auto longest_first_word_last_iter = next_iter;

  while (next_iter != last_iter) {
    const auto [first, last] = find_first_sequence_of_allowed_elements(
        next_iter, last_iter, haystack, is_haystack_sorted);

    if (first == last)
      break;

    const auto current_distance{distance(first, last)};

    if (current_distance > longest_first_word_length) {
      longest_first_word_length = current_distance;
      longest_first_word_start_iter = first;
      longest_first_word_last_iter = last;
    }

    next_iter = last;
  }

  return StringType(longest_first_word_start_iter,
                    longest_first_word_last_iter);
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
