/*
Coderbyte coding challenge: Largest Four

Using the C++ language, have the function LargestFour(arr) take the array of
integers stored in arr, and find the four largest elements and return their sum.
For example: if arr is [4, 5, -2, 3, 1, 2, 6, 6] then the four largest elements
in this array are 6, 6, 4, and 5 and the total sum of these numbers is 21, so
your program should return 21. If there are less than four numbers in the array
your program should return the sum of all the numbers in the array.

Sample test cases:

Input:  1, 1, 1, -5
Output: -2

Input:  0, 0, 2, 3, 7, 1
Output: 13
*/

#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;

int LargestFour(int* arr, const size_t arr_size) {
  sort(arr, arr + arr_size, [](const int ln, const int rn) { return ln > rn; });

  const size_t last_index{arr_size >= 4 ? 4 : arr_size};

  return accumulate(arr, arr + last_index, 0);
}

int main() {
  // int A[] = gets(stdin);
  // cout << LargestFour(A, sizeof(A)/sizeof(*A));
  int B[] = {4, 5, -2, 3, 1, 2, 6, 6};
  cout << LargestFour(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 21
  int C[] = {1, 1, 1, -5};
  cout << LargestFour(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: -2
  int D[] = {0, 0, 2, 3, 7, 1};
  cout << LargestFour(D, sizeof(D) / sizeof(*D))
       << '\n';  //  expected output: 13

  return 0;
}
