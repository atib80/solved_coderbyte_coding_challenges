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

#include <iostream>
#include <string>

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

using namespace std;

size_t LongestIncreasingSequence_v1(const int* arr, const size_t arr_size) {
  size_t max_list_length{1};

  find_longest_increasing_sequence_length(arr, arr_size, 0, max_list_length);

  return max_list_length;
}

int main() {
  // const int A[] = gets(stdin);
  // cout << LongestIncreasingSequence(A, sizeof(A)/sizeof(*A));
  const int B[] = {4, 3, 5, 1, 6};
  cout << LongestIncreasingSequence_v1(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 3
  const int C[] = {9, 9, 4, 2};
  cout << LongestIncreasingSequence_v1(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 1
  const int D[] = {10, 22, 9, 33, 21, 50, 41, 60, 22, 68, 90};
  cout << LongestIncreasingSequence_v1(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 7
  const int E[] = {2, 4, 3, 5, 1, 7, 6, 9, 8};
  cout << LongestIncreasingSequence_v1(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: 5
  const int F[] = {10, 22, 9, 33, 21, 50, 41, 60};
  cout << LongestIncreasingSequence_v1(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: 5
  const int G[] = {10, 12, 4, 6, 100, 2, 56, 34, 79};
  cout << LongestIncreasingSequence_v1(G, sizeof(G) / sizeof(*G))
       << '\n';  // expected output: 4
  const int H[] = {10, 12, 4, 6, 100, 2, 56, 34, 79, 45, 33, 12, 45, 67, 89};
  cout << LongestIncreasingSequence_v1(H, sizeof(H) / sizeof(*H))
       << '\n';  // expected output: 6

  return 0;
}
