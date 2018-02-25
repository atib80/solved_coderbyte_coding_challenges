/*
Coderbyte coding challenge: Element Merger

Using the C++ language, have the function ElementMerger(arr) take the array of
positive integers stored in arr and perform the following algorithm:
continuously get the difference of adjacent integers to create a new array of
integers, then do the same for the new array until a single number is left and
return that number. For example: if arr is [4, 5, 1, 2, 7] then taking the
difference of each pair of elements produces the following new array: [1, 4, 1,
5]. Then do the same for this new array to produce [3, 3, 4] -> [0, 1] -> 1. So
for this example your program should return the number 1 because that is what's
left at the end.

Sample test cases:

Input:  5, 7, 16, 1, 2
Output: 7

Input:  1, 1, 1, 2
Output: 1
*/

#include <cmath>
#include <iostream>

using namespace std;

int ElementMerger(int* arr, size_t arr_size) {

  while (arr_size > 1) {
    for (size_t i{}; i < arr_size - 1; i++)
      arr[i] = abs(arr[i + 1] - arr[i]);

    arr_size--;
  }

  return arr[0];
}

int main() {

  // int A[] = gets(stdin);
  // cout << ElementMerger(A, sizeof(A)/sizeof(*A));
  int A1[] = {4, 5, 1, 2, 7};
  cout << ElementMerger(A1, sizeof(A1) / sizeof(*A1))
       << '\n';  // expected output: 1
  int A2[] = {5, 7, 16, 1, 2};
  cout << ElementMerger(A2, sizeof(A2) / sizeof(*A2))
       << '\n';  // expected output: 7
  int A3[] = {1, 1, 1, 2};
  cout << ElementMerger(A3, sizeof(A3) / sizeof(*A3))
       << '\n';  // expected output: 1

  return 0;
}
