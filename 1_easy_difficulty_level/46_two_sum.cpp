/*
Coderbyte coding challenge: Two Sum

Using the C++ language, have the function TwoSum(arr) take the array of integers
stored in arr, and determine if any two numbers (excluding the first element) in
the array can sum up to the first element in the array. For example: if arr is
[7, 3, 5, 2, -4, 8, 11], then there are actually two pairs that sum to the
number 7: [5, 2] and [-4, 11]. Your program should return all pairs, with the
numbers separated by a comma, in the order the first number appears in the
array. Pairs should be separated by a space. So for the example above, your
program would return: "5,2 -4,11" If there are no two numbers that sum to the
first element in the array, return -1

Sample test cases:

Input:  17, 4, 5, 6, 10, 11, 4, -3, -5, 3, 15, 2, 7
Output: "6,11 10,7 15,2"

Input:  7, 6, 4, 1, 7, -2, 3, 12
Output: "6,1 4,3"
*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

string TwoSum_v1(const int* arr, const size_t arr_size) {
  if (arr_size < 3U)
    return "-1";

  const int target_num{*arr};
  ostringstream oss{};

  for (size_t i{1}; i < arr_size - 1; ++i) {
    for (size_t j{i + 1}; j < arr_size; ++j) {
      if (arr[i] + arr[j] == target_num) {
        oss << arr[i] << ',' << arr[j] << ' ';
      }
    }
  }

  if (oss.tellp() != 0) {
    string result{oss.str()};
    result.pop_back();
    return result;
  }

  return "-1";
}

string TwoSum_v2(const int* arr, const size_t arr_size) {
  if (arr_size < 3U)
    return "-1";

  const int target_num{arr[0]};

  unordered_map<int, size_t> numbers_freq{};

  ostringstream oss{};

  for (size_t i{1}; i < arr_size; ++i) {
    const int search_value{target_num - arr[i]};
    const auto search_value_iter = numbers_freq.find(search_value);

    if (end(numbers_freq) == search_value_iter ||
        0U == numbers_freq.at(search_value)) {
      ++numbers_freq[arr[i]];
    } else {
      --numbers_freq[search_value];
      oss << arr[i] << ',' << search_value << ' ';
    }
  }

  if (oss.tellp() != 0) {
    string result{oss.str()};
    result.pop_back();
    return result;
  }

  return "-1";
}

template <typename ForwardIter, typename T>
ForwardIter optimal_bsearch(ForwardIter first,
                            ForwardIter last,
                            const T& value) {
  const ForwardIter orig_last{last};
  ForwardIter next{first};

  while (++next != last) {
    ForwardIter current{first};

    std::advance(current, std::distance(first, last) / 2);

    if (value < *current)
      last = current;
    else
      first = current;

    next = first;
  }

  return value == *first ? first : orig_last;
}

bool check_if_found_number_has_been_used(
    const size_t index,
    const vector<int>& sorted_numbers,
    unordered_set<size_t>& ignored_indices) {
  bool illegal_index = false;

  if (0U != ignored_indices.count(index)) {
    const int target_number{sorted_numbers.at(index)};
    illegal_index = true;

    for (size_t x{index}, y{index + 1}; x > 0U || y < sorted_numbers.size();) {
      if (target_number == sorted_numbers[x - 1] &&
          0U == ignored_indices.count(x - 1)) {
        ignored_indices.emplace(x - 1);
        illegal_index = false;
        break;
      } else if (target_number == sorted_numbers[y] &&
                 0U == ignored_indices.count(y)) {
        ignored_indices.emplace(y);
        illegal_index = false;
        break;
      } else if (target_number != sorted_numbers[x - 1] &&
                 target_number != sorted_numbers[y])
        break;

      if (x > 0U)
        --x;
    }
  } else {
    ignored_indices.emplace(index);
  }

  return illegal_index;
}

string TwoSum_v3(const int* arr, const size_t arr_size) {
  if (arr_size < 3U)
    return "-1";

  const auto target_num{arr[0]};
  vector<int> sorted_numbers(arr + 1, arr + arr_size);
  sort(begin(sorted_numbers), end(sorted_numbers));
  unordered_set<size_t> ignored_indices{};

  ostringstream oss{};

  for (size_t i{}; i < sorted_numbers.size(); ++i) {
    const auto second_number{target_num - sorted_numbers[i]};

    ignored_indices.emplace(i);

    if (second_number < sorted_numbers[i]) {
      const auto iter = optimal_bsearch(
          cbegin(sorted_numbers), cbegin(sorted_numbers) + i, second_number);
      if (iter != cbegin(sorted_numbers) + i &&
          !check_if_found_number_has_been_used(
              static_cast<size_t>(iter - cbegin(sorted_numbers)),
              sorted_numbers, ignored_indices)) {
        oss << second_number << ',' << sorted_numbers[i] << ' ';
      }
    } else {
      const auto iter = optimal_bsearch(cbegin(sorted_numbers) + i + 1,
                                        cend(sorted_numbers), second_number);
      if (iter != cend(sorted_numbers) &&
          !check_if_found_number_has_been_used(
              static_cast<size_t>(iter - cbegin(sorted_numbers)),
              sorted_numbers, ignored_indices)) {
        oss << sorted_numbers[i] << ',' << second_number << ' ';
      }
    }
  }

  if (oss.tellp() != 0) {
    string result{oss.str()};
    result.pop_back();
    return result;
  }

  return "-1";
}

int main() {
  // const int A[] = gets(stdin);
  // cout << TwoSum_v2(A, sizeof(A)/sizeof(*A));
  const int b[]{7, 3, 5, 2, -4, 8, 11};
  cout << TwoSum_v3(b, sizeof(b) / sizeof(*b))
       << '\n';  // expected output: "5,2 -4,11"
  const int c[]{17, 4, 5, 6, 10, 11, 4, -3, -5, 3, 15, 2, 7};
  cout << TwoSum_v3(c, sizeof(c) / sizeof(*c))
       << '\n';  // expected output: "6,11 10,7 15,2"
  const int d[]{7, 6, 4, 1, 7, -2, 3, 12};
  cout << TwoSum_v3(d, sizeof(d) / sizeof(*d))
       << '\n';  // expected output: "6,1 4,3"
  const int e[]{6, 2};
  cout << TwoSum_v3(e, sizeof(e) / sizeof(*e))
       << '\n';  // expected output: "-1"
  const int f[]{100, 90, 90, 90, 90, 11};
  cout << TwoSum_v3(f, sizeof(f) / sizeof(*f))
       << '\n';  // expected output: "-1"
  const int g[]{4, 5, 2, 1};
  cout << TwoSum_v3(g, sizeof(g) / sizeof(*g))
       << '\n';  // expected output: "-1"

  return 0;
}
