/*
Coderbyte coding challenge: Power Set Count

Using the C++ language, have the function PowerSetCount(arr) take the array of
integers stored in arr, and return the length of the power set (the number of
all possible sets) that can be generated. For example: if arr is [1, 2, 3], then
the following sets form the power set:

[]
[1]
[2]
[3]
[1, 2]
[1, 3]
[2, 3]
[1, 2, 3]

You can see above all possible sets, along with the empty set, are generated.
Therefore, for this input, your program should return 8.

Sample test cases:

Input:  1, 2, 3, 4
Output: 16

Input:  5, 6
Output: 4
*/

#include <cmath>
#include <iostream>

using namespace std;

template <typename... Args>
void unused(Args&&...) {}

size_t PowerSetCount_v1(const int* numbers, const size_t numbers_size) {
  unused(numbers);
  return pow(static_cast<size_t>(2U), numbers_size);
}

size_t PowerSetCount_v2(const int* numbers, const size_t numbers_size) {
  unused(numbers);
  return 1U << numbers_size;
}

int main() {
  // const int A[] = gets(stdin);
  // cout << PowerSetCount_v2(A, sizeof(A)/sizeof(*A));
  const int b[]{1, 2, 3};
  cout << PowerSetCount_v2(b, sizeof(b) / sizeof(*b))
       << '\n';  // expected output: 8
  const int c[]{1, 2, 3, 4};
  cout << PowerSetCount_v2(c, sizeof(c) / sizeof(*c))
       << '\n';  // expected output: 16
  const int d[]{5, 6};
  cout << PowerSetCount_v2(d, sizeof(d) / sizeof(*d))
       << '\n';  // expected output: 4

  return 0;
}
