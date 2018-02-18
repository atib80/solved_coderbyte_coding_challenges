/*
Coderbyte coding challenge: Longest Increasing Sequence (LIS)

Using the C++ language, have the function LongestIncreasingSequence(arr) take
the array of positive integers stored in arr and return the length of the
longest increasing subsequence (LIS). A LIS is a subset of the original list
where the numbers are in sorted order, from lowest to highest, and are in
increasing order. The sequence does not need to be contiguous or unique, and
there can be several different subsequences. For example: if arr is [4, 3, 5, 1,
6] then a possible LIS is [3, 5, 6], and another is [1, 6]. For this input, your
program should return 3 because that is the length of the longest increasing
subsequence.

Sample test cases:

Input:  9, 9, 4, 2
Output: 1

Input:  10, 22, 9, 33, 21, 50, 41, 60, 22, 68, 90
Output: 7
*/

#include <algorithm>
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <unordered_set>
#include <utility>

using namespace std;

void find_longest_increasing_sequence_length(
    const int* arr,
    const size_t arr_size,
    const size_t pos,
    size_t& max_lis_length,
    const size_t current_lis_length = 1) {
  if (current_lis_length + arr_size - pos <= max_lis_length)
    return;

  for (size_t i{pos}; i < arr_size - 1; i++) {
    if (arr[i + 1] > arr[pos])
      find_longest_increasing_sequence_length(
          arr, arr_size, i + 1, max_lis_length, current_lis_length + 1);
  }

  if (current_lis_length > max_lis_length)
    max_lis_length = current_lis_length;
}

size_t LongestIncreasingSequence_v1(const int* arr, const size_t arr_size) {
  size_t max_lis_length{1};

  find_longest_increasing_sequence_length(arr, arr_size, 0, max_lis_length);

  return max_lis_length;
}

size_t LongestIncreasingSequence_v2(const int* arr, const size_t arr_size) {
  size_t max_lis_length{1};

  unordered_set<size_t> ignore_array_indices{};

  bool repeat_search;

  do {
    repeat_search = false;

    for (size_t i{}; i < arr_size - 1; i++) {
      if (ignore_array_indices.count(arr[i]))
        continue;

      int prev_number{arr[i]};
      size_t prev_number_index{i};
      size_t current_lis_length{1};

      stack<size_t> last_visited_indices{};

      for (size_t j{i + 1}; j < arr_size; j++) {
        if (!ignore_array_indices.count(j) && (arr[j] > prev_number)) {
          current_lis_length++;
          prev_number = arr[j];
          prev_number_index = j;
          if (prev_number_index < arr_size - 1) {
            last_visited_indices.emplace(prev_number_index);
          }
        }
      }

      if (1 == current_lis_length)
        return max_lis_length;

      if (current_lis_length > max_lis_length)
        max_lis_length = current_lis_length;

      if (prev_number_index < arr_size - 1) {
        ignore_array_indices.insert(prev_number_index);
        repeat_search = true;
        break;
      }

      unordered_set<size_t> visited_array_indices{};

      while (!last_visited_indices.empty()) {
        const size_t last_visited_index{last_visited_indices.top()};
        visited_array_indices.insert(last_visited_index);
        last_visited_indices.pop();

        prev_number = arr[i];
        current_lis_length = 1;

        for (size_t j{i + 1}; j < arr_size; j++) {
          if (!ignore_array_indices.count(j) &&
              !visited_array_indices.count(j) && (arr[j] > prev_number)) {
            current_lis_length++;
            prev_number = arr[j];
          }
        }

        if (current_lis_length > max_lis_length)
          max_lis_length = current_lis_length;
      }

      if ((arr_size - 1 - i) <= max_lis_length)
        break;
    }
  } while (repeat_search);

  return max_lis_length;
}

size_t LongestIncreasingSequence_v3(const int* arr, const size_t arr_size) {
  vector<pair<int, size_t>> numbers(arr_size);
  for (size_t i{}; i < arr_size; i++) {
    numbers[i].first = arr[i];
    numbers[i].second = i;
  }
  sort(begin(numbers), end(numbers),
       [](const pair<int, size_t>& ln, const pair<int, size_t>& rn) {
         return ln.first < rn.first;
       });

  size_t max_lis_length{1};

  set<size_t> overlooked_indices{};

  for (size_t i{}; i < arr_size - 1; i++) {
    int prev_number{numbers[i].first};
    size_t prev_number_index{numbers[i].second};
    size_t current_lis_length{1};

    for (size_t j{i + 1}; j < numbers.size(); j++) {
      if ((numbers[j].first > prev_number) &&
          (numbers[j].second > prev_number_index)) {
        prev_number = numbers[j].first;
        prev_number_index = numbers[j].second;
        current_lis_length++;
      } else if ((numbers[j].first > numbers[i].first) &&
                 (numbers[j].second > numbers[i].second)) {
        overlooked_indices.insert(numbers[j].second);
      }
    }

    if (1 == current_lis_length)
      return max_lis_length;

    if (current_lis_length > max_lis_length)
      max_lis_length = current_lis_length;

    while (!overlooked_indices.empty()) {
      const size_t si{*begin(overlooked_indices)};
      overlooked_indices.erase(begin(overlooked_indices));

      if ((arr_size - si + 1) <= max_lis_length) {
        overlooked_indices.clear();
        break;
      }

      prev_number = numbers[i].first;
      current_lis_length = 1;

      for (size_t j{si}; j < arr_size; j++) {
        if (arr[j] > prev_number) {
          prev_number = arr[j];
          current_lis_length++;
        }
      }

      if (1 == current_lis_length)
        return max_lis_length;

      if (current_lis_length > max_lis_length)
        max_lis_length = current_lis_length;
    }

    if ((arr_size - 1 - i) <= max_lis_length)
      break;
  }

  return max_lis_length;
}

int main() {
  // const int A[] = gets(stdin);
  // cout << LongestIncreasingSequence(A, sizeof(A)/sizeof(*A));

  const int B[] = {4, 3, 5, 1, 6};
  cout << LongestIncreasingSequence_v3(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 3
  const int C[] = {9, 9, 4, 2};
  cout << LongestIncreasingSequence_v3(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 1
  const int D[] = {10, 22, 9, 33, 21, 50, 41, 60, 22, 68, 90};
  cout << LongestIncreasingSequence_v3(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 7
  const int E[] = {2, 4, 3, 5, 1, 7, 6, 9, 8};
  cout << LongestIncreasingSequence_v3(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: 5
  const int F[] = {10, 22, 9, 33, 21, 50, 41, 60};
  cout << LongestIncreasingSequence_v3(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: 5
  const int G[] = {10, 12, 4, 6, 100, 2, 56, 34, 79};
  cout << LongestIncreasingSequence_v3(G, sizeof(G) / sizeof(*G))
       << '\n';  // expected output: 4
  const int H[] = {10, 12, 4, 6, 100, 2, 56, 34, 79, 45, 33, 12, 45, 67, 89};
  cout << LongestIncreasingSequence_v3(H, sizeof(H) / sizeof(*H))
       << '\n';  // expected output: 6

  return 0;
}
