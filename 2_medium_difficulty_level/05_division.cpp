/*
Coderbyte coding challenge: Division

Using the C++ language, have the function Division(num1,num2) take both parameters being passed and return the Greatest Common Factor. 
That is, return the greatest number that evenly goes into both numbers with no remainder. For example: 12 and 16 both are divisible by 1, 2, and 4 
so the output should be 4. The range for both parameters will be from 1 to 10^3.

Sample test cases:

Input:  7 & num2 = 3
Output: 1

Input:  36 & num2 = 54
Output: 18
*/

#include <iostream>
#include <algorithm>

using namespace std;

int Division(const int* arr, const size_t arr_size) {

	if (arr_size < 2u) return -1;

	const int min_number { min(arr[0], arr[1]) };

	for (int i { min_number }; i >= 1; i--) {

		if ((arr[0] % i == 0) && (arr[1] % i == 0)) return i;

	}

  return 1;              
}

int main() { 
   
  // const int A[] = { gets(stdin) };
  // cout << Division(A, sizeof(A)/sizeof(*A));
  const int B[] = {45, 12};
  cout << Division(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: 3
  const int C[] = {1, 6};
  cout << Division(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: 1
  const int D[] = {12, 28};
  cout << Division(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: 4

  return 0;    

}
