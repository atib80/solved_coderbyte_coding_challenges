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

  string result{oss.str()};

  if (result.empty())
    return "-1";

  result.erase(--cend(result));

  return result;
}

string TwoSum_v2(const int* arr, const size_t arr_size) {
  if (arr_size < 3U)
    return "-1";

  const int target_num{arr[0]};

  unordered_multiset<int> numbers{arr + 1, arr + arr_size};

  ostringstream oss{};

  for (size_t i{1}; i < arr_size; ++i) {
    const auto left_number_pos = numbers.find(arr[i]);

    if (end(numbers) == left_number_pos)
      continue;

    numbers.erase(left_number_pos);

    const int search_value{target_num - arr[i]};

    const auto right_number_pos = numbers.find(search_value);

    if (end(numbers) == right_number_pos)
      continue;

    numbers.erase(right_number_pos);

    oss << arr[i] << ',' << search_value << ' ';
  }

  string result{oss.str()};

  if (result.empty())
    return "-1";

  result.erase(--cend(result));

  return result;
}

string TwoSum_v3(const int* arr, const size_t arr_size) {
  if (arr_size < 3U)
    return "-1";

  const int target_num{arr[0]};

  unordered_map<int, size_t> numbers_freq{};

  for (size_t i{1}; i < arr_size; i++)
    numbers_freq[arr[i]]++;

  ostringstream oss{};

  for (size_t i{1}; i < arr_size; i++) {
    if (0U == numbers_freq.find(arr[i])->second)
      continue;

    numbers_freq[arr[i]]--;

    const int search_value{target_num - arr[i]};

    if (numbers_freq.find(search_value) == end(numbers_freq) ||
        0U == numbers_freq.find(search_value)->second)
      continue;

    numbers_freq[search_value]--;

    oss << arr[i] << ',' << search_value << ' ';
  }

  string result{oss.str()};

  if (result.empty())
    return "-1";

  result.erase(--cend(result));

  return result;
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

string TwoSum_v4(const int* arr, const size_t arr_size) {
  if (arr_size < 3U)
    return "-1";

  const auto target_num{arr[0]};
  const int skip_item_value{arr[1] - 1};
  vector<int> sorted_numbers(arr + 1, arr + arr_size);
  sort(begin(sorted_numbers), end(sorted_numbers));

  ostringstream oss{};

  for (size_t i{}; i < sorted_numbers.size(); ++i) {
    if (skip_item_value == sorted_numbers[i])
      continue;
    const auto second_number{target_num - sorted_numbers[i]};

    if (second_number < sorted_numbers[i]) {
      const auto iter = optimal_bsearch(
          begin(sorted_numbers), begin(sorted_numbers) + i, second_number);
      if (iter != begin(sorted_numbers) + i) {
        oss << second_number << ',' << sorted_numbers[i] << ' ';
        sorted_numbers[i] = *iter = skip_item_value;
      }
    } else {
      const auto iter = optimal_bsearch(begin(sorted_numbers) + i + 1,
                                        end(sorted_numbers), second_number);
      if (iter != end(sorted_numbers)) {
        oss << sorted_numbers[i] << ',' << second_number << ' ';
        sorted_numbers[i] = *iter = skip_item_value;
      }
    }
  }

  string result{oss.str()};

  if (result.empty())
    return "-1";

  result.erase(--cend(result));

  return result;
}

int main() {
  // const int A[] = gets(stdin);
  // cout << TwoSum_v4(A, sizeof(A)/sizeof(*A));
  const int b[]{7, 3, 5, 2, -4, 8, 11};
  cout << TwoSum_v4(b, sizeof(b) / sizeof(*b))
       << '\n';  // expected output: "5,2 -4,11"
  const int c[]{17, 4, 5, 6, 10, 11, 4, -3, -5, 3, 15, 2, 7};
  cout << TwoSum_v4(c, sizeof(c) / sizeof(*c))
       << '\n';  // expected output: "6,11 10,7 15,2"
  const int d[]{7, 6, 4, 1, 7, -2, 3, 12};
  cout << TwoSum_v4(d, sizeof(d) / sizeof(*d))
       << '\n';  // expected output: "6,1 4,3"
  const int e[]{6, 2};
  cout << TwoSum_v4(e, sizeof(e) / sizeof(*e))
       << '\n';  // expected output: "-1"
  const int f[]{100, 90, 90, 90, 90, 11};
  cout << TwoSum_v4(f, sizeof(f) / sizeof(*f))
       << '\n';  // expected output: "-1"
  const int g[]{4, 5, 2, 1};
  cout << TwoSum_v4(g, sizeof(g) / sizeof(*g))
       << '\n';  // expected output: "-1"

  return 0;
}
