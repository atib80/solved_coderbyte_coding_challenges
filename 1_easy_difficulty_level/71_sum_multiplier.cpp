/*
Coderbyte coding challenge: Sum Multiplier

Using the C++ language, have the function SumMultiplier(arr) take the array of
numbers stored in arr and return the string true if any two numbers can be
multiplied so that the answer is greater than double the sum of all the elements
in the array. If not, return the string false. For example: if arr is [2, 5, 6,
-6, 16, 2, 3, 6, 5, 3] then the sum of all these elements is 42 and doubling it
is 84. There are two elements in the array, 16 * 6 = 96 and 96 is greater than
84, so your program should return the string true.

Sample test cases:

Input:  2, 2, 2, 2, 4, 1
Output: "false"

Input:  1, 1, 2, 10, 3, 1, 12
Output: "true"
*/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>

using namespace std;

string SumMultiplier(int* arr, const size_t arr_size) {
  if (arr_size < 2)
    return "false";

  sort(arr, arr + arr_size,
       [](const int ln, const int rn) { return (ln > rn); });

  const int double_sum{2 * accumulate(arr, arr + arr_size, 0)};

  if (arr[0] * arr[1] > double_sum)
    return "true";

  return "false";
}

int main() {
  // int A[] = gets(stdin);
  // cout << SumMultiplier(A, sizeof(A)/sizeof(*A));
  int B[] = {2, 5, 6, -6, 16, 2, 3, 6, 5, 3};
  cout << SumMultiplier(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "true"
  int C[] = {2, 2, 2, 2, 4, 1};
  cout << SumMultiplier(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "false"
  int D[] = {1, 1, 2, 10, 3, 1, 12};
  cout << SumMultiplier(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "true"

  return 0;
}
