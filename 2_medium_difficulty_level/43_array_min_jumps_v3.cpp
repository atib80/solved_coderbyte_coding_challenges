/*
Coderbyte coding challenge: Array Min Jumps v3

(An alternative simple, easy to understand iterative solution implemented by
using queue<pair<int, int>> for tracking current array positions and their
respective number of steps)

Using the C++ language, have the function ArrayMinJumps(arr) take the array of
integers stored in arr, where each integer represents the maximum number of
steps that can be made from that position, and determine the least amount of
jumps that can be made to reach the end of the array. For example: if arr is [1,
5, 4, 6, 9, 3, 0, 0, 1, 3] then your program should output the number 3 because
you can reach the end of the array from the beginning via the following steps: 1
-> 5 -> 9 -> END or 1 -> 5 -> 6 -> END. Both of these combinations produce a
series of 3 steps. And as you can see, you don't always have to take the maximum
number of jumps at a specific position, you can take less jumps even though the
number is higher.

If it is not possible to reach the end of the array, return -1.

Sample test cases:

Input:  3, 4, 2, 1, 1, 100
Output: 2

Input:  1, 3, 6, 8, 2, 7, 1, 2, 1, 2, 6, 1, 2, 1, 2
Output: 4
*/

#include <climits>
#include <iostream>
#include <queue>
#include <utility>

using namespace std;

int find_min_number_of_steps_needed_from_current_position(const int* arr,
                                                          const int arr_size) {
  queue<pair<int, int>> q{{make_pair(0, 1)}};
  int min_steps_needed{INT_MAX};

  while (!q.empty()) {
    const int current_pos{q.front().first};
    const int current_steps_count{q.front().second};
    q.pop();

    if (current_pos + arr[current_pos] >= arr_size - 1 &&
        current_steps_count < min_steps_needed)
      min_steps_needed = current_steps_count;

    else {
      for (int start{current_pos + 1}; start <= current_pos + arr[current_pos];
           start++) {
        if (current_steps_count + 1 >= min_steps_needed)
          break;
        q.emplace(make_pair(start, current_steps_count + 1));
      }
    }
  }

  if (INT_MAX != min_steps_needed)
    return min_steps_needed;

  return -1;
}

int ArrayMinJumps(const int* arr, const int arr_size) {
  if (arr_size < 2)
    return 0;

  return find_min_number_of_steps_needed_from_current_position(arr, arr_size);
}

int main() {
  // const int A[] = gets(stdin);
  // cout << ArrayMinJumps(A, sizeof(A)/sizeof(*A));
  const int B[] = {1, 5, 4, 6, 9, 3, 0, 0, 1, 3};
  cout << ArrayMinJumps(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 3
  const int C[] = {3, 4, 2, 1, 1, 100};
  cout << ArrayMinJumps(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 2
  const int D[] = {1, 3, 6, 8, 2, 7, 1, 2, 1, 2, 6, 1, 2, 1, 2};
  cout << ArrayMinJumps(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 4
  const int E[] = {1, 0, 0, 2};
  cout << ArrayMinJumps(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: -1
  const int F[] = {4};
  cout << ArrayMinJumps(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: 0

  return 0;
}
