/*
Coderbyte coding challenge: Parallel Sums v2

(solution implemented by using recursion)

Using the C++ language, have the function ParallelSums(arr) take the array of
integers stored in arr which will always contain an even amount of integers, and
determine how they can be split into two even sets of integers each so that both
sets add up to the same number. If this is impossible return -1. If it's
possible to split the array into two sets, then return a string representation
of the first set followed by the second set with each integer separated by a
comma and both sets sorted in ascending order. The set that goes first is the
set with the smallest first integer.

For example: if arr is [16, 22, 35, 8, 20, 1, 21, 11], then your program should
output 1,11,20,35,8,16,21,22

Sample test cases:

Input:  1,2,3,4
Output: "1,4,2,3"

Input:  1,2,1,5
Output: "-1"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool find_array_indices_for_half_sum(const size_t start_index,
                                     const vector<int>& vec,
                                     const int half_sum,
                                     const size_t iter_count,
                                     set<size_t>& found_indices,
                                     const int current_sum = 0) {
  for (size_t i{start_index}; i < vec.size(); i++) {
    if (current_sum + vec[i] > half_sum)
      return false;

    if (current_sum + vec[i] == half_sum) {
      if (iter_count > vec.size() / 2 - 1)
        return false;
      found_indices.insert(i);
      return true;
    }

    if (find_array_indices_for_half_sum(i + 1, vec, half_sum, iter_count + 1,
                                        found_indices, current_sum + vec[i])) {
      found_indices.insert(i);
      return true;
    }
  }

  return false;
}

string ParallelSums2(const int* arr, const size_t arr_size) {
  vector<int> numbers(arr, arr + arr_size);
  if (arr_size % 2 == 1)
    return "-1";
  sort(begin(numbers), end(numbers));
  int sum{accumulate(begin(numbers), end(numbers), 0)};
  if (sum % 2 == 1)
    return "-1";

  vector<int> left_numbers{};
  vector<int> right_numbers{};
  const int half_sum{sum / 2};

  set<size_t> found_indices{};

  find_array_indices_for_half_sum(0, numbers, half_sum, 0, found_indices, 0);

  if (found_indices.size() != arr_size / 2)
    return "-1";

  for (const size_t i : found_indices)
    left_numbers.emplace_back(numbers[i]);

  for (size_t i{}; i < numbers.size(); i++) {
    if (found_indices.find(i) == end(found_indices))
      right_numbers.emplace_back(numbers[i]);
  }

  ostringstream oss{};

  if (left_numbers[0] < right_numbers[0]) {
    for (const int n : left_numbers)
      oss << n << ',';
    for (size_t i{}; i < right_numbers.size() - 1; i++)
      oss << right_numbers[i] << ',';
    oss << right_numbers.back();
  } else {
    for (const int n : right_numbers)
      oss << n << ',';
    for (size_t i{}; i < left_numbers.size() - 1; i++)
      oss << left_numbers[i] << ',';
    oss << left_numbers.back();
  }

  return oss.str();
}

int main() {
  // const int A[] = gets(stdin);
  // cout << ParallelSums2(A, sizeof(A)/sizeof(*A));
  const int B[] = {16, 22, 35, 8, 20, 1, 21, 11};
  cout << ParallelSums2(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "1,11,20,35,8,16,21,22"
  const int C[] = {1, 2, 3, 4};
  cout << ParallelSums2(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "1,4,2,3"
  const int D[] = {1, 2, 1, 5};
  cout << ParallelSums2(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "-1"
  const int E[] = {9, 1, 0, 5, 3, 2};
  cout << ParallelSums2(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: "0,1,9,2,3,5"
  const int F[] = {6, 2, 4, 1, 10, 25, 5, 3, 40, 4};
  cout << ParallelSums2(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: "1,2,3,4,40,4,5,6,10,25"
  const int G[] = {100, 101, 1, 0};
  cout << ParallelSums2(G, sizeof(G) / sizeof(*G))
       << '\n';  // expected output: "0,101,1,100"

  return 0;
}
