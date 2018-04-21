/*
Coderbyte coding challenge: Parallel Sums v1

(solution implemented by using brute-force method)

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
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string ParallelSums(const int* arr, const size_t arr_size) {
  vector<int> numbers(arr, arr + arr_size);
  if (arr_size % 2 == 1)
    return "-1";
  sort(begin(numbers), end(numbers));
  const int sum{accumulate(begin(numbers), end(numbers), 0)};
  if (sum % 2 == 1)
    return "-1";

  const bool is_partial_numbers_size_odd{(arr_size >> 1) % 2 == 1};
  const int half_sum{sum / 2};

  vector<int> left_numbers{};
  vector<int> right_numbers{};

  do {
    int left_sum{}, right_sum{};
    left_numbers.clear();
    right_numbers.clear();

    bool is_left_turn{true};

    for (size_t i{}, j{arr_size - 1}; i < j; i++, j--) {
      if (is_left_turn) {
        if (is_partial_numbers_size_odd && j - i == 1) {
          left_sum += numbers[i];

          if (left_sum > half_sum) {
            left_sum = 0;
            break;
          }

          left_numbers.emplace_back(numbers[i]);

          right_sum += numbers[j];

          if (right_sum > half_sum) {
            left_sum = 0;
            break;
          }

          right_numbers.emplace_back(numbers[j]);
        } else {
          left_sum += numbers[i] + numbers[j];

          if (left_sum > half_sum) {
            left_sum = 0;
            break;
          }

          left_numbers.emplace_back(numbers[i]);
          left_numbers.emplace_back(numbers[j]);
        }
      } else {
        if (is_partial_numbers_size_odd && j - i == 1) {
          left_sum += numbers[i];

          if (left_sum > half_sum) {
            left_sum = 0;
            break;
          }

          left_numbers.emplace_back(numbers[i]);

          right_sum += numbers[j];

          if (right_sum > half_sum) {
            left_sum = 0;
            break;
          }

          right_numbers.emplace_back(numbers[j]);
        } else {
          right_sum += numbers[i] + numbers[j];

          if (right_sum > half_sum) {
            left_sum = 0;
            break;
          }

          right_numbers.emplace_back(numbers[i]);
          right_numbers.emplace_back(numbers[j]);
        }
      }

      is_left_turn = !is_left_turn;
    }

    if (left_sum && right_sum && left_sum == right_sum) {
      sort(begin(left_numbers), end(left_numbers));
      sort(begin(right_numbers), end(right_numbers));

      ostringstream oss{};

      if (left_numbers[0] < right_numbers[0]) {
        for (size_t i{}; i < left_numbers.size(); i++)
          oss << left_numbers[i] << ',';
        for (size_t i{}; i < right_numbers.size() - 1; i++)
          oss << right_numbers[i] << ',';
        oss << right_numbers.back();
      } else {
        for (size_t i{}; i < right_numbers.size(); i++)
          oss << right_numbers[i] << ',';
        for (size_t i{}; i < left_numbers.size() - 1; i++)
          oss << left_numbers[i] << ',';
        oss << left_numbers.back();
      }

      return oss.str();
    }
  } while (next_permutation(begin(numbers), end(numbers)));

  return "-1";
}

int main() {
  // const int A[] = gets(stdin);
  // cout << ParallelSums(A, sizeof(A)/sizeof(*A));
  const int B[] = {16, 22, 35, 8, 20, 1, 21, 11};
  cout << ParallelSums(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "1,11,20,35,8,16,21,22"
  const int C[] = {1, 2, 3, 4};
  cout << ParallelSums(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "1,4,2,3"
  const int D[] = {1, 2, 1, 5};
  cout << ParallelSums(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "-1"
  const int E[] = {9, 1, 0, 5, 3, 2};
  cout << ParallelSums(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: "0,1,9,2,3,5"
  const int F[] = {6, 2, 4, 1, 10, 25, 5, 3, 40, 4};
  cout << ParallelSums(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: "1,2,3,4,40,4,5,6,10,25"
  return 0;
}
