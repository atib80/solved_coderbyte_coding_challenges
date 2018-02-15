/*
Dynamic programming related coding challenge:

Find the maximum number of subsets of numbers given in the input array of whole
numbers that add up to the given sum value specified as the first number in the
input array.

Sample test cases:

Input:  "16", "2", "4", "6", "10"
Output: 2

Input: "13", "1", "3", "2", "5", "6", "7", "8", "4"
Output: 6
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
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

size_t find_number_of_subsets(const char** str_arr, const size_t str_arr_size) {
  const int sum{stoi(trim(string{str_arr[0]}))};

  if (1 == str_arr_size || 0 == sum)
    return 1;

  if ((2 == str_arr_size) && (str_arr[0] == str_arr[1]))
    return 1;

  vector<int> numbers{};

  for (size_t i{1}; i < str_arr_size; i++) {
    numbers.emplace_back(stoi(trim(string{str_arr[i]})));
  }

  sort(begin(numbers), end(numbers),
       [](const int ln, const int rn) { return ln > rn; });

  size_t number_of_subsets{};

  for (size_t i{}; i < numbers.size() - 1; i++) {
    int current_sum{};
    bool is_continue_search{};

    for (size_t j{i}; j < numbers.size(); j++) {
      if (current_sum + numbers[j] == sum) {
        number_of_subsets++;
        is_continue_search = true;
        continue;
      }

      if (current_sum + numbers[j] > sum) {
        is_continue_search = true;
        continue;
      }

      current_sum += numbers[j];
    }

    if (!is_continue_search)
      break;
  }

  return number_of_subsets;
}

int main() {
  const char* arr1[] = {"16", "2", "4", "6", "10"};
  cout << find_number_of_subsets(arr1, sizeof(arr1) / sizeof(*arr1))
       << '\n';  // expected output: 2
  const char* arr2[] = {"13", "1", "3", "2", "5", "6", "7", "8", "4"};
  cout << find_number_of_subsets(arr2, sizeof(arr2) / sizeof(*arr2))
       << '\n';  // expected output: 6

  return 0;
}
