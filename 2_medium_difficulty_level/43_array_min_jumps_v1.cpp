/*
Coderbyte coding challenge: Array Min Jumps

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

#include <iostream>
#include <vector>

using namespace std;

int ArrayMinJumps(const int* arr, const size_t arr_size) {
  if (arr_size < 2)
    return 0;

  vector<int> result(arr_size);

  for (size_t i{}; i < result.size() - 1; i++) {
    const int steps_to_make{arr[i]};

    if (!steps_to_make && arr_size - 2 == i)
      return -1;

    const int current_steps_count{result[i] + 1};

    for (size_t j{i + 1}; j < result.size() && j < i + 1 + steps_to_make; j++) {
      if (!result[j])
        result[j] = current_steps_count;
    }
  }

  return result[arr_size - 1];
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
