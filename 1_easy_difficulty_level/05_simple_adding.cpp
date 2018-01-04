/*
Coderbyte coding challenge: Simple Adding

Using the C++ language, have the function SimpleAdding(num) add up all the numbers from 1 to num. 
For example: if the input is 4 then your program should return 10 because 1 + 2 + 3 + 4 = 10. For the test cases, 
the parameter num will be any number from 1 to 1000.

Sample test cases:

Input:  12
Output: 78

Input:  140
Output: 9870
*/

#include <iostream>
#include <cstdint>

using namespace std;

int64_t SimpleAdding(const int64_t num) { 
    
  int64_t result{1LL};
    
  for (int64_t i{2LL}; i <= num; i++) result += i;
  
  return result; 
            
}

int main() { 
  
  // cout << SimpleAdding(gets(stdin));
  cout << SimpleAdding(4) << '\n';   // expected output: 10
  cout << SimpleAdding(12) << '\n';  // expected output: 78
  cout << SimpleAdding(140) << '\n'; // expected output: 9870
  return 0;    
}
