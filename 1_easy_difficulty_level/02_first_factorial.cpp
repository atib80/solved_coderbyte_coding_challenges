/*
Coderbyte coding challenge: First Factorial

Using the C++ language, have the function FirstFactorial(num) take the num parameter being passed and return the factorial of it (e.g. if num = 4, return (4 * 3 * 2 * 1)).
For the test cases, the range will be between 1 and 18 and the input will always be an integer.

Sample test cases:

Input:  4
Output: 24

Input:  8
Output: 40320
*/

#include <iostream>
#include <cstdint>

using namespace std;

int64_t FirstFactorial(int64_t num) {

  if (!num) return 1LL;
   
  if (num < 3LL) return num;

  int64_t result{num};

  while (num > 2) result *= --num;

  return result;

}

int64_t FirstFactorial_v2(const int64_t num) {

  if (num < 2LL) return 1LL;
   
  return num * FirstFactorial(num - 1);

}

int main() { 

  // cout << FirstFactorial(gets(stdin));
  cout << FirstFactorial_v2(0) << '\n';
  cout << FirstFactorial_v2(1) << '\n';
  cout << FirstFactorial_v2(2) << '\n';
  cout << FirstFactorial_v2(3) << '\n';
  cout << FirstFactorial_v2(4) << '\n';
  cout << FirstFactorial_v2(5) << '\n';
  cout << FirstFactorial_v2(6) << '\n';
  cout << FirstFactorial_v2(7) << '\n';
  cout << FirstFactorial_v2(8) << '\n';
  
  return 0;    
}
