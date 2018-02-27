/*
Coderbyte coding challenge: Division

Using the C++ language, have the function Division(num1,num2) take both
parameters being passed and return the Greatest Common Factor. That is, return
the greatest number that evenly goes into both numbers with no remainder. For
example: 12 and 16 both are divisible by 1, 2, and 4 so the output should be 4.
The range for both parameters will be from 1 to 10^3.

Sample test cases:

Input:  7 & num2 = 3
Output: 1

Input:  36 & num2 = 54
Output: 18
*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int gcf(const int num1, const int num2) {
  const int min_number{min(num1, num2)};

  for (int gcf{min_number}; gcf > 1; gcf--) {
    if ((num1 % gcf == 0) && (num2 % gcf == 0))
      return gcf;
  }

  return 1;
}

int Division(const int* arr, const size_t arr_size) {
  if (arr_size < 2)
    return -1;

  return gcf(arr[0], arr[1]);
}

int main() {
  // const int A[] = { gets(stdin) };
  // cout << Division(A, sizeof(A)/sizeof(*A));
  const int B[] = {45, 12};
  cout << Division(B, sizeof(B) / sizeof(*B)) << '\n';  // expected output: 3
  const int C[] = {1, 6};
  cout << Division(C, sizeof(C) / sizeof(*C)) << '\n';  // expected output: 1
  const int D[] = {12, 28};
  cout << Division(D, sizeof(D) / sizeof(*D)) << '\n';  // expected output: 4
  const int E[] = {7, 3};
  cout << Division(E, sizeof(E) / sizeof(*E)) << '\n';  // expected output: 1
  const int F[] = {36, 54};
  cout << Division(F, sizeof(F) / sizeof(*F)) << '\n';  // expected output: 18

  return 0;
}
