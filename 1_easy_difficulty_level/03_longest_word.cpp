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
#include <cctype>
#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>
#include <unordered_set>

using namespace std;

string LongestWord_v1(string sen) {
  size_t word_len{};
  size_t start_index{string::npos};
  size_t max_word_len{};
  string longest_first_word{};

  for (size_t i{}; i < sen.length(); i++) {
    if (isalnum(sen[i])) {
      if (string::npos == start_index)
        start_index = i;
      word_len++;
      continue;
    }

    if (word_len > max_word_len && string::npos != start_index) {
      max_word_len = word_len;
      longest_first_word = sen.substr(start_index, word_len);
    } else if (!word_len)
      continue;

    start_index = string::npos;
    word_len = 0;
  }

  if (word_len > max_word_len && string::npos != start_index)
    longest_first_word = sen.substr(start_index, word_len);

  return longest_first_word;
}

string LongestWord_v2(string sen) {
  const size_t sen_len{sen.length()};
  size_t start{};
  size_t max_word_len{};
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

template <typename T, typename U = T>
using is_operator_less_than_defined_t =
    decltype(std::declval<T&>().operator<(std::declval<U>()));

template <typename T, typename U = T, typename = void>
struct is_operator_less_than_defined : std::false_type {};

template <typename T, typename U>
struct is_operator_less_than_defined<
    T,
    U,
    std::void_t<is_operator_less_than_defined_t<T, U>>> : std::true_type {};

template <typename T, typename U = T>
constexpr const bool is_operator_less_than_defined_v =
    is_operator_less_than_defined<T, U>::value;

template <typename T, typename U>
using has_find_member_function_t =
    decltype(std::declval<T&>().find(std::declval<U>()));

template <typename T, typename U, typename = void>
struct has_find_member_function : std::false_type {};

template <typename T, typename U>
struct has_find_member_function<T,
                                U,
                                std::void_t<has_find_member_function_t<T, U>>>
    : std::true_type {};

template <typename T, typename U>
constexpr const bool has_find_member_function_v =
    has_find_member_function<T, U>::value;

template <typename ForwardIterType, typename ContainerType>
std::pair<ForwardIterType, ForwardIterType> find_next_sequence(
    ForwardIterType start,
    ForwardIterType last,
    const ContainerType& haystack,
    const bool is_haystack_sorted = false) {
  using T = typename iterator_traits<ForwardIterType>::value_type;

  if (start == last)
    return make_pair(last, last);

  if constexpr (has_find_member_function_v<ContainerType, T>) {
    const auto first{
        std::find_if(start, last, [&haystack](const auto& current_element) {
          return std::cend(haystack) != haystack.find(current_element);
        })};
    if (first == last)
      return make_pair(last, last);
    auto second{first};
    ++second;
    second =
        std::find_if(second, last, [&haystack](const auto& current_element) {
          return std::cend(haystack) == haystack.find(current_element);
        });
    return make_pair(first, second);

  } else {
    if (is_haystack_sorted) {
      const auto first{
          std::find_if(start, last, [&haystack](const auto& current_element) {
            return std::binary_search(std::cbegin(haystack),
                                      std::cend(haystack), current_element);
          })};
      if (last == first)
        return make_pair(last, last);
      auto second{first};
      ++second;
      second =
          std::find_if(second, last, [&haystack](const auto& current_element) {
            return !std::binary_search(std::cbegin(haystack),
                                       std::cend(haystack), current_element);
          });

      return make_pair(first, second);
    } else {
      const auto first{
          std::find_if(start, last, [&haystack](const auto& current_element) {
            return std::cend(haystack) != std::find(std::cbegin(haystack),
                                                    std::cend(haystack),
                                                    current_element);
          })};
      if (last == first)
        return make_pair(last, last);
      auto second{first};
      ++second;
      second =
          std::find_if(second, last, [&haystack](const auto& current_element) {
            return std::cend(haystack) == std::find(std::cbegin(haystack),
                                                    std::cend(haystack),
                                                    current_element);
          });

      return make_pair(first, second);
    }
  }
}

template <typename StringType, typename ContainerType>
StringType find_longest_word(StringType&& src, ContainerType&& haystack) {
  using T = typename StringType::value_type;
  using U = typename ContainerType::value_type;

  bool is_haystack_sorted{has_find_member_function_v<ContainerType, T>};

  if constexpr (!has_find_member_function_v<ContainerType, T> &&
                is_operator_less_than_defined_v<U>) {
    sort(begin(haystack), end(haystack));
    is_haystack_sorted = true;
  }

  auto next_iter = cbegin(src);
  const auto last_iter = cend(src);
  decltype(distance(next_iter, last_iter)) max_word_len{};
  StringType longest_first_word{};

  while (next_iter != last_iter) {
    const auto [first, last] =
        find_next_sequence(next_iter, last_iter, haystack, is_haystack_sorted);

    if (first == last)
      break;

    const auto current_distance{std::distance(first, last)};

    if (current_distance > max_word_len) {
      max_word_len = current_distance;
      longest_first_word.assign(first, last);
    }

    next_iter = last;
  }

  return longest_first_word;
}

string LongestWord_v3(string sen) {
  static const char allowed_chars[]{
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"};
  auto haystack{
      unordered_set<char>{cbegin(allowed_chars), cend(allowed_chars)}};

  return find_longest_word(move(sen), move(haystack));
}

int main() {
  // cout << LongestWord_v2(gets(stdin));
  cout << LongestWord_v3("fun&!! time") << '\n';  // expected output: "time"
  cout << LongestWord_v3("I love dogs") << '\n';  // expected output: "love"
  cout << LongestWord_v3("I love both cats and dogs as well!")
       << '\n';  // expected output: "love"

  return 0;
}
