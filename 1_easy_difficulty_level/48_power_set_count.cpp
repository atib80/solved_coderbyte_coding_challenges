/*
Coderbyte coding challenge: Power Set Count

Using the C++ language, have the function PowerSetCount(arr) take the array of integers stored in arr, and return the length of the power set 
(the number of all possible sets) that can be generated. For example: if arr is [1, 2, 3], then the following sets form the power set:

[]
[1]
[2]
[3]
[1, 2]
[1, 3]
[2, 3]
[1, 2, 3]

You can see above all possible sets, along with the empty set, are generated. Therefore, for this input, your program should return 8.

Sample test cases:

Input:  1, 2, 3, 4
Output: 16

Input:  5, 6
Output: 4
*/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

template <typename ..._Args>
void unused(const _Args&...) { }

size_t PowerSetCount(const int* numbers, const size_t numbers_size) { 

  unused(numbers);  
  return static_cast<size_t>(pow(2u, numbers_size));            
}

int main() { 
   
  // const int A[] = gets(stdin);
  // cout << PowerSetCount(A, sizeof(A)/sizeof(*A));
  const int b[] = {1, 2, 3};
  cout << PowerSetCount(b, sizeof(b)/sizeof(*b)) << '\n'; // 8
  const int c[] = {1, 2, 3, 4};
  cout << PowerSetCount(c, sizeof(c)/sizeof(*c)) << '\n'; // 16
  const int d[] = {5, 6};
  cout << PowerSetCount(d, sizeof(d)/sizeof(*d)) << '\n'; // 2
  
  return 0;
}
