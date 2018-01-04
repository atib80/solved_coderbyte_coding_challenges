/*
Coderbyte coding challenge: Second Greatlow

Using the C++ language, have the function SecondGreatLow(arr) take the array of numbers stored in arr and return the second lowest and second greatest numbers, 
respectively, separated by a space. For example: if arr contains [7, 7, 12, 98, 106] the output should be 12 98. The array will not be empty and will contain 
at least 2 numbers. It can get tricky if there's just two numbers!

Sample test cases:

Input:  1, 42, 42, 180
Output: "42 42"

Input:  4, 90
Output: "90 4"
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string second_great_low(int* arr, const size_t arr_size) { 
  
  if (0u == arr_size) return string{"Array argument is empty!"};

  if (1u == arr_size) return string{"Array argument has only 1 element!"};

  sort(arr, arr + arr_size);

  if (2u == arr_size) {

  	string result { to_string(arr[1]) };
  	result += ' ';
  	result += to_string(arr[0]);
  	return result;

  }

  int second_min_element{arr[0]};
  int second_max_element{arr[arr_size - 1]};

  for (size_t i{1u}; i != arr_size; i++) {
  	if (arr[i] > second_min_element) {
  		second_min_element = arr[i];
  		break;
  	}

  }

  for (size_t j{arr_size - 2}; j != 0u; j--) {

  	if (arr[j] < second_max_element) {
  		second_max_element = arr[j];
  		break;
  	}

  }

  string result { to_string(second_min_element) };
  result += ' ';
  result += to_string(second_max_element);  
  return result;           
}

int main() { 
   
  int A[] = gets(stdin);
  cout << second_great_low(A, sizeof(A)/sizeof(A[0]));
  // int a[] = {7, 7, 12, 98, 106};
  // cout << second_great_low(a, sizeof(a)/sizeof(*a)) << '\n';
  // int b[] = {1, 42, 42, 180};
  // cout << second_great_low(b, sizeof(b)/sizeof(*b)) << '\n';
  // int c[] = {4, 90};
  // cout << second_great_low(c, sizeof(c)/sizeof(*c)) << '\n';
  return 0;    
} 
