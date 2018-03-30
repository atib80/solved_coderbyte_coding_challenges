/*
Coderbyte coding challenge: Longest Consecutive

Using the C++ language, have the function LongestConsecutive(arr) take the array
of positive integers stored in arr and return the length of the longest
consecutive subsequence (LCS). An LCS is a subset of the original list where the
numbers are in sorted order, from lowest to highest, and are in a consecutive,
increasing order. The sequence does not need to be contiguous and there can be
several different subsequences. For example: if arr is [4, 3, 8, 1, 2, 6, 100,
9] then a few consecutive sequences are [1, 2, 3, 4], and [8, 9]. For this
input, your program should return 4 because that is the length of the longest
consecutive subsequence.

Sample test cases:

Input:  6, 7, 3, 1, 100, 102, 6, 12
Output: 2

Input:  5, 6, 1, 2, 8, 9, 7
Output: 5
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

size_t LongestConsecutive_v1(int* arr, const size_t arr_size) {
  if (arr_size < 2)
    return arr_size;

  size_t max_lcs_len{1}, current_lcs_len{1};

  sort(arr, arr + arr_size);

  for (size_t i{}; i < arr_size - 1; i++) {
    if (arr[i] == arr[i + 1])  // if 2 consecutive numbers are equal skip to
                               // next array element (do not increase current
                               // LCS's length)
      continue;

    if (arr[i] + 1 == arr[i + 1])
      current_lcs_len++;
    else if (current_lcs_len > max_lcs_len) {
      max_lcs_len = current_lcs_len;
      current_lcs_len = 1;
    } else {
      current_lcs_len = 1;
    }
  }

  if (current_lcs_len > max_lcs_len)
    max_lcs_len = current_lcs_len;

  return max_lcs_len;
}

size_t LongestConsecutive_v2(int* arr, int arr_size) {
  if (!arr || arr_size < 2)
    return arr_size;

  if (2 == arr_size && 1 == abs(arr[0] - arr[1]))
    return 2;

  sort(arr, arr + arr_size);
  const int* unique_arr_end{unique(arr, arr + arr_size)};
  arr_size = unique_arr_end - arr;
  int lcs_len{arr_size};

  while (lcs_len > 1) {
    for (int i{}; i + lcs_len <= arr_size; i++) {
      if (arr[i + lcs_len - 1] - arr[i] == lcs_len - 1)
        return lcs_len;
    }

    lcs_len--;
  }

  return 1;
}

int main() {
  // int A[] = gets(stdin);
  // cout << LongestConsecutive_v2(A, sizeof(A)/sizeof(*A));
  int B[] = {4, 3, 8, 1, 2, 6, 100, 9};
  cout << LongestConsecutive_v2(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 4
  int C[] = {6, 7, 3, 1, 100, 102, 6, 12};
  cout << LongestConsecutive_v2(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 2
  int D[] = {5, 6, 1, 2, 8, 9, 7};
  cout << LongestConsecutive_v2(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 5
  int E[] = {11, 6, 6, 5, 7, 10, 1, 2, 3, 12, 9, 8};
  cout << LongestConsecutive_v2(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: 8
  int F[] = {5, 15, 16, 21, 4, 5, 10, 9, 8, 22, 23, 7, 3, 2, 24, 1, 6};
  cout << LongestConsecutive_v2(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: 10
  int G[] = {8, 7};
  cout << LongestConsecutive_v2(G, sizeof(G) / sizeof(*G))
       << '\n';  // expected output: 2

  return 0;
}
