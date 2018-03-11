/*
Coderbyte coding challenge: Simple Mode

Using the C++ language, have the function SimpleMode(arr) take the array of
numbers stored in arr and return the number that appears most frequently (the
mode). For example: if arr contains [10, 4, 5, 2, 4] the output should be 4. If
there is more than one mode return the one that appeared in the array first (ie.
[5, 10, 10, 6, 5] should return 5 because it appeared first). If there is no
mode return -1. The array will not be empty.

Sample test cases:

Input:  5,5,2,2,1
Output: 5

Input:  3,4,1,6,10
Output: -1
*/

#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int SimpleMode_v1(const int* arr, const size_t arr_size) {
  if (!arr || 1 == arr_size)
    return -1;

  int mode_number{};
  int mode_freq{1};
  unordered_set<int> visited_modes{};

  for (size_t i{}; i < arr_size; i++) {
    if (visited_modes.count(arr[i]))
      continue;

    visited_modes.insert(arr[i]);

    const int mode_count = count(arr, arr + arr_size, arr[i]);

    if (mode_count > mode_freq) {
      mode_freq = mode_count;
      mode_number = arr[i];
    }
  }

  if (mode_freq > 1)
    return mode_number;

  return -1;
}

int SimpleMode_v2(const int* arr, const size_t arr_size) {
  if (!arr || 1 == arr_size)
    return -1;

  vector<pair<int, int>> mode_freq{};

  unordered_set<int> visited_modes{};

  for (size_t i{}; i < arr_size; i++) {
    if (visited_modes.count(arr[i]))
      continue;

    visited_modes.insert(arr[i]);

    const int mode_count = count(arr, arr + arr_size, arr[i]);

    mode_freq.emplace_back(make_pair(arr[i], mode_count));
  }

  stable_sort(begin(mode_freq), end(mode_freq),
              [](const pair<int, int>& lhs, const pair<int, int>& rhs) {
                return (lhs.second > rhs.second);
              });

  if (mode_freq[0].second > 1)
    return mode_freq[0].first;

  return -1;
}

int SimpleMode_v3(int* arr, const size_t arr_size) {
  if (!arr || 1 == arr_size)
    return -1;

  int mode_number{-1};
  size_t mode_freq{1};

  multiset<int> number_freq(arr, arr + arr_size);

  int* const last{unique(arr, arr + arr_size)};

  for (int* start{arr}; start != last; ++start) {
    if (number_freq.count(*start) > mode_freq) {
      mode_freq = number_freq.count(*start);
      mode_number = *start;
    }
  }

  return mode_number;
}

int main() {
  // const int A[] = gets(stdin);
  // cout << SimpleMode_v3(A, sizeof(A)/sizeof(*A));
  int B[] = {10, 4, 5, 2, 4};
  cout << SimpleMode_v3(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 4
  int C[] = {5, 10, 10, 6, 5};
  cout << SimpleMode_v3(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 5
  int D[] = {5, 5, 2, 2, 1};
  cout << SimpleMode_v3(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 5
  int E[] = {3, 4, 1, 6, 10};
  cout << SimpleMode_v3(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: -1
  return 0;
}
