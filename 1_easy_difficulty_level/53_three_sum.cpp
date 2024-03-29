/*
Coderbyte coding challenge: Three Sum

Using the C++ language, have the function ThreeSum(arr) take the array of
integers stored in arr, and determine if any three distinct numbers (excluding
the first element) in the array can sum up to the first element in the array.
For example: if arr is [8, 2, 1, 4, 10, 5, -1, -1] then there are actually three
sets of triplets that sum to the number 8: [2, 1, 5], [4, 5, -1] and [10, -1,
-1]. Your program should return the string true if 3 distinct elements sum to
the first element, otherwise your program should return the string false. The
input array will always contain at least 4 elements.

Sample test cases:

Input:  10, 2, 3, 1, 5, 3, 1, 4, -4, -3, -2
Output: "true"

Input:  12, 3, 1, -5, -4, 7
Output: "false"
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

string ThreeSum_v1(int* arr, const size_t arr_size) {
  if (arr_size < 4U)
    return "false";

  const int sum{arr[0]};

  unordered_set<int> visited_two_sums{};

  for (size_t i{1}; i < arr_size - 2; ++i) {
    for (size_t j{i + 1}; j < arr_size - 1; ++j) {
      const int two_sum{arr[i] + arr[j]};

      if (1U == visited_two_sums.count(two_sum))
        continue;

      visited_two_sums.emplace(two_sum);

      for (size_t k{j + 1}; k < arr_size; ++k) {
        if (two_sum + arr[k] == sum ||
            1U == visited_two_sums.count(sum - arr[k]))
          return "true";
      }
    }
  }

  return "false";
}

string ThreeSum_v2(int* arr, const size_t arr_size) {
  if (arr_size < 4U)
    return "false";

  const int sum{arr[0]};

  sort(arr + 1, arr + arr_size);

  unordered_set<int> visited_two_sums{};

  for (size_t i{1}; i < arr_size - 2; ++i) {
    for (size_t j{i + 1}; j < arr_size - 1; ++j) {
      const int two_sum{arr[i] + arr[j]};
      if (two_sum > sum)
        break;

      if (1U == visited_two_sums.count(two_sum))
        continue;

      if (binary_search(arr + j + 1, arr + arr_size, sum - two_sum))
        return "true";

      visited_two_sums.emplace(two_sum);
    }
  }

  return "false";
}

bool check_if_three_numbers_exist(const int* arr,
                                  const size_t arr_size,
                                  const size_t pos,
                                  unordered_set<int>& visited_two_sums,
                                  const size_t iter_count = 1U,
                                  const int current_sum = 0) {
  if (3U == iter_count)
    return binary_search(arr + pos, arr + arr_size, arr[0] - current_sum);

  if (2U == iter_count && visited_two_sums.count(current_sum) == 1U)
    return false;

  visited_two_sums.emplace(current_sum);

  for (size_t i{pos}; i < arr_size; ++i) {
    if (current_sum + arr[i] <= arr[0] &&
        check_if_three_numbers_exist(arr, arr_size, i + 1, visited_two_sums,
                                     iter_count + 1, current_sum + arr[i]))
      return true;
  }

  return false;
}

string ThreeSum_v3(int* arr, const size_t arr_size) {
  if (arr_size < 4U)
    return "false";

  sort(arr + 1, arr + arr_size);
  unordered_set<int> visited_two_sums{};
  if (check_if_three_numbers_exist(arr, arr_size, 1U, visited_two_sums, 1U, 0))
    return "true";

  return "false";
}

int main() {
  // int A[] = gets(stdin);
  // cout << ThreeSum_v2(A, sizeof(A)/sizeof(*A));
  int B[]{8, 2, 1, 4, 10, 5, -1, -1};
  cout << ThreeSum_v2(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "true"
  int C[]{10, 2, 3, 1, 5, 3, 1, 4, -4, -3, -2};
  cout << ThreeSum_v2(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "true"
  int D[]{12, 3, 1, -5, -4, 7};
  cout << ThreeSum_v2(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "false"
  int E[]{10, 5, 5, 5, 5};
  cout << ThreeSum_v2(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: "false"
  int F[]{10, 2, 2, 2, 2, 2, 2,  2,  2,  2,  2,  5,
          5,  5, 5, 5, 5, 8, -2, -2, -2, -2, -1, 7};
  cout << ThreeSum_v2(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: "true"
  int G[]{5, -6, 4, -5, -3, -2, 7, 1, 2, 12, 8, 14};
  cout << ThreeSum_v2(G, sizeof(G) / sizeof(*G))
       << '\n';  // expected output: "true"

  return 0;
}
