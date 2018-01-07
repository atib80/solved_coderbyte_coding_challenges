/*
Coderbyte coding challenge: Max Subarray

Using the C++ language, have the function MaxSubarray(arr) take the array of numbers stored in arr and determine the largest sum 
that can be formed by any contiguous subarray in the array. For example, if arr is [-2, 5, -1, 7, -3] then your program should return 11 
because the sum is formed by the subarray [5, -1, 7]. 
Adding any element before or after this subarray would make the sum smaller.

Sample test cases:

Input:  1, -2, 0, 3
Output: 3

Input:  3, -1, -1, 4, 3, -1
Output: 8
*/

#include <iostream>
#include <algorithm>

using namespace std;

int MaxSubarray(const int* arr, const size_t arr_size) {

	int current_largest_sum { *min_element(arr, arr + arr_size) };

	size_t current_sub_array_size{arr_size};

	while (current_sub_array_size != 0) {

		for (size_t i{}; (i + current_sub_array_size) <= arr_size; i++) {
			int current_sum{};
			for (size_t j{i}; j != (i + current_sub_array_size); j++) {
				current_sum += arr[j];
			}

			if (current_sum > current_largest_sum) current_largest_sum = current_sum;
		}

		current_sub_array_size--;

	}


  return current_largest_sum;            
}

int main() {   
    
  // const int A[] = gets(stdin);
  // cout << MaxSubarray(A, sizeof(A)/sizeof(*A));
  const int B[] = {-2, 5, -1, 7, -3};
  cout << MaxSubarray(B, sizeof(B)/sizeof(*B)) << '\n'; // 11
  const int C[] = {1, -2, 0, 3};
  cout << MaxSubarray(C, sizeof(C)/sizeof(*C)) << '\n'; // 3
  const int D[] = {3, -1, -1, 4, 3, -1};
  cout << MaxSubarray(D, sizeof(D)/sizeof(*D)) << '\n'; // 8

  return 0;    
}
