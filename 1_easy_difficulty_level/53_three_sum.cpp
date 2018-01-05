/*
Coderbyte coding challenge: Three Sum

Using the C++ language, have the function ThreeSum(arr) take the array of integers stored in arr, and determine if any three distinct numbers 
(excluding the first element) in the array can sum up to the first element in the array. For example: if arr is [8, 2, 1, 4, 10, 5, -1, -1] 
then there are actually three sets of triplets that sum to the number 8: [2, 1, 5], [4, 5, -1] and [10, -1, -1]. 
Your program should return the string true if 3 distinct elements sum to the first element, otherwise your program should return the string false. 
The input array will always contain at least 4 elements.

Sample test cases:

Input:  10, 2, 3, 1, 5, 3, 1, 4, -4, -3, -2
Output: "true"

Input:  12, 3, 1, -5, -4, 7
Output: "false"
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>

using namespace std;

string ThreeSum(const int* arr, const size_t arr_size) {

  if (arr_size < 4u) return "false";

  const int sum { arr[0] };

  set<int, greater<int>> sorted_sequence(arr + 1, arr + arr_size);

  vector<int> numbers(begin(sorted_sequence), end(sorted_sequence));
  sort(begin(numbers), end(numbers), [](const int l, const int r) {

  	return (l > r);

  });

  const size_t ns { numbers.size() };

  if (ns < 3u) return "false";

  for (size_t i{}; i < ns - 2; i++) {

  	for (size_t j{i + 1}; j < ns - 1; j++) {
  	
  		for (size_t k{j + 1}; k < ns; k++) {

  			if (sum == (numbers[i] + numbers[j] + numbers[k])) return "true";  	
  		
  		}  	
  	
  	}

  }
 
  return "false"; 
            
}

int main() {

  // const int A[] = gets(stdin);
  // cout << ThreeSum(A, sizeof(A)/sizeof(*A));   
  const int B[] = {8, 2, 1, 4, 10, 5, -1, -1};
  cout << ThreeSum(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: "true"
  const int C[] = {10, 2, 3, 1, 5, 3, 1, 4, -4, -3, -2};
  cout << ThreeSum(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: "true"
  const int D[] = {12, 3, 1, -5, -4, 7};
  cout << ThreeSum(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: "false"
  const int E[] = {10, 5, 5, 5, 5};
  cout << ThreeSum(E, sizeof(E)/sizeof(*E)) << '\n'; // expected output: "false"
  const int F[] = {10, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 5, 5, 5, 5, 5, 5, 8, -2, -2, -2, -2, -1, 7};
  cout << ThreeSum(F, sizeof(F)/sizeof(*F)) << '\n'; // expected output: "true"
  const int G[] = {5, -6, 4, -5, -3, -2, 7, 1, 2, 12, 8, 14};
  cout << ThreeSum(G, sizeof(G)/sizeof(*G)) << '\n'; // expected output: "true"
  
  return 0;

}
