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
#include <vector>

using namespace std;

string TwoSum_v1(const int* arr, const size_t arr_size) {
  if (arr_size < 3)
    return "-1";

  ostringstream oss{};

  for (size_t i{1}; i < arr_size - 1; i++) {
    for (size_t j{i + 1}; j < arr_size; j++) {
      if (arr[i] + arr[j] == arr[0]) {
        oss << arr[i] << ',' << arr[j] << ' ';
      }
    }
  }

  string result{oss.str()};

  if (result.empty())
    return "-1";

  result.erase(--(end(result)));

  return result;
}

template <class ForwardIt, class T>
size_t bsearch(ForwardIt first, ForwardIt last, const T& value) {
  using difference_type =
      typename std::iterator_traits<ForwardIt>::difference_type;
  const ForwardIt start{first};
  first = lower_bound(first, last, value);
  return (!(first == last) && !(value < *first))
             ? static_cast<difference_type>(first - start)
             : string::npos;
}

string TwoSum_v2(const int* arr, const size_t arr_size) {
  if (arr_size < 3)
    return "-1";

  const int target_num{arr[0]};

  vector<int> sorted_numbers(arr + 1, arr + arr_size);

  sort(begin(sorted_numbers), end(sorted_numbers));

  ostringstream oss{};

  for (size_t i{1}; i < arr_size; i++) {
    if (sorted_numbers.empty())
      break;

    const size_t left_number_index{
        bsearch(begin(sorted_numbers), end(sorted_numbers), arr[i])};

    if (string::npos == left_number_index)
      continue;

    sorted_numbers.erase(begin(sorted_numbers) + left_number_index);

    if (sorted_numbers.empty())
      break;

    const int search_value{target_num - arr[i]};

    const size_t right_number_index{
        bsearch(begin(sorted_numbers), end(sorted_numbers), search_value)};

    if (string::npos == right_number_index)
      continue;

    sorted_numbers.erase(begin(sorted_numbers) + right_number_index);

    oss << arr[i] << ',' << search_value << ' ';
  }

  string result{oss.str()};

  if (result.empty())
    return "-1";

  result.erase(result.length() - 1, 1);

  return result;
}

string TwoSum_v3(const int* arr, const size_t arr_size) {
  if (arr_size < 3)
    return "-1";

  const int target_num{arr[0]};

  unordered_map<int, size_t> numbers_freq{};

  for (size_t i{1}; i < arr_size; i++)
    numbers_freq[arr[i]]++;

  ostringstream oss{};

  for (size_t i{1}; i < arr_size; i++) {
    if (!numbers_freq.find(arr[i])->second)
      continue;

    numbers_freq[arr[i]]--;

    const int search_value{target_num - arr[i]};

    if (numbers_freq.find(search_value) == end(numbers_freq) ||
        !numbers_freq.find(search_value)->second)
      continue;

    numbers_freq[search_value]--;

    oss << arr[i] << ',' << search_value << ' ';
  }

  string result{oss.str()};

  if (result.empty())
    return "-1";

  result.erase(--(end(result)));

  return result;
}

int main() {
  // const int A[] = gets(stdin);
  // cout << TwoSum_v2(A, sizeof(A)/sizeof(*A));
  const int b[] = {7, 3, 5, 2, -4, 8, 11};
  cout << TwoSum_v2(b, sizeof(b) / sizeof(*b))
       << '\n';  // expected output: "5,2 -4,11"
  const int c[] = {17, 4, 5, 6, 10, 11, 4, -3, -5, 3, 15, 2, 7};
  cout << TwoSum_v2(c, sizeof(c) / sizeof(*c))
       << '\n';  // expected output: "6,11 10,7 15,2"
  const int d[] = {7, 6, 4, 1, 7, -2, 3, 12};
  cout << TwoSum_v2(d, sizeof(d) / sizeof(*d))
       << '\n';  // expected output: "6,1 4,3"
  const int e[] = {6, 2};
  cout << TwoSum_v2(e, sizeof(e) / sizeof(*e))
       << '\n';  // expected output: "-1"
  const int f[] = {100, 90, 90, 90, 90, 11};
  cout << TwoSum_v2(f, sizeof(f) / sizeof(*f))
       << '\n';  // expected output: "-1"
  const int g[] = {4, 5, 2, 1};
  cout << TwoSum_v2(g, sizeof(g) / sizeof(*g))
       << '\n';  // expected output: "-1"

  return 0;
}
