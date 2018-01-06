/*
Coderbyte coding challenge: GCF

Using the C++ language, have the function GCF(arr) take the array of numbers stored in arr which will always contain only two positive integers, 
and return the greatest common factor of them. For example: if arr is [45, 12] then your program should return 3. 
There will always be two elements in the array and they will be positive integers.

Sample test cases:

Input:  1, 6
Output: 1

Input:  12, 28
Output: 4
*/

#include <iostream>
#include <algorithm>

using namespace std;

int GCF(const int* arr, const size_t arr_size) {

	if (arr_size < 2u) return -1;

	const int min_number { min(arr[0], arr[1]) };

	for (int i { min_number }; i >= 1; i--) {

		if ((arr[0] % i == 0) && (arr[1] % i == 0)) return i;

	}

  return 1; 
            
}

int main() { 
   
  // const int A[] = gets(stdin);
  // cout << GCF(A, sizeof(A)/sizeof(*A));
  const int B[] = {45, 12};
  cout << GCF(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: 3
  const int C[] = {1, 6};
  cout << GCF(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: 1
  const int D[] = {12, 28};
  cout << GCF(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: 4

  return 0;
    
}
