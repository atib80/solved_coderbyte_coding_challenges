/*
Coderbyte coding challenge: Two Sum

Using the C++ language, have the function TwoSum(arr) take the array of integers stored in arr, and determine if any two numbers 
(excluding the first element) in the array can sum up to the first element in the array. 
For example: if arr is [7, 3, 5, 2, -4, 8, 11], then there are actually two pairs that sum to the number 7: [5, 2] and [-4, 11]. 
Your program should return all pairs, with the numbers separated by a comma, in the order the first number appears in the array. 
Pairs should be separated by a space. So for the example above, your program would return: "5,2 -4,11"
If there are no two numbers that sum to the first element in the array, return -1

Sample test cases:

Input:  17, 4, 5, 6, 10, 11, 4, -3, -5, 3, 15, 2, 7
Output: "6,11 10,7 15,2"

Input:  7, 6, 4, 1, 7, -2, 3, 12
Output: "6,1 4,3"
*/

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string TwoSum(const int* numbers, const size_t numbers_size) { 

  if (numbers_size < 3u) return "-1";
	
  ostringstream oss{};

	for (size_t i{1u}; i < (numbers_size - 1); i++) {

		for (size_t j{i + 1}; j < numbers_size; j++) {

			if ((numbers[i] + numbers[j]) == numbers[0]) {
        oss << numbers[i] << ',' << numbers[j] << ' ';
			}
		} 
	}

  string result{oss.str()};

  if (result.empty()) return "-1";  

  result.erase(--(end(result)));

  return result;             
}

int main() { 
   
  // const int A[] = gets(stdin);
  // cout << TwoSum(A, sizeof(A)/sizeof(*A));
  const int b[] = {7, 3, 5, 2, -4, 8, 11};
  cout << TwoSum(b, sizeof(b)/sizeof(*b)) << '\n'; // expected output: "5,2 -4,11"
  const int c[] = {17, 4, 5, 6, 10, 11, 4, -3, -5, 3, 15, 2, 7};
  cout << TwoSum(c, sizeof(c)/sizeof(*c)) << '\n'; // expected output: "6,11 10,7 15,2"
  const int d[] = {7, 6, 4, 1, 7, -2, 3, 12};
  cout << TwoSum(d, sizeof(d)/sizeof(*d)) << '\n'; // expected output: "6,1 4,3"
  const int e[] = {6, 2};
  cout << TwoSum(e, sizeof(e)/sizeof(*e)) << '\n'; // expected output: "-1"
  const int f[] = {100, 90, 90, 90, 90, 11};
  cout << TwoSum(f, sizeof(f)/sizeof(*f)) << '\n'; // expected output: "-1"
  const int g[] = {4, 5, 2, 1};
  cout << TwoSum(g, sizeof(g)/sizeof(*g)) << '\n'; // expected output: "-1"
  return 0;    
}
