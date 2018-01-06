/*
Coderbyte coding challenge: Consecutive

Using the C++ language, have the function Consecutive(arr) take the array of integers stored in arr and return the minimum number of integers needed 
to make the contents of arr consecutive from the lowest number to the highest number. For example: If arr contains [4, 8, 6] then the output should be 2 
because two numbers need to be added to the array (5 and 7) to make it a consecutive array of numbers from 4 to 8. 
Negative numbers may be entered as parameters and no array will have less than 2 elements.

Sample test cases:

Input:  5,10,15
Output: 8

Input:  -2,10,4
Output: 10
*/

#include <iostream>
#include <algorithm>

using namespace std;

int Consecutive(int* arr, const size_t arr_size) {	

  int number_of_missing_steps{};

  sort(arr, arr + arr_size);

  for (size_t i{}; i != arr_size - 1; i++) number_of_missing_steps += (arr[i+1] - arr[i] - 1);

  return number_of_missing_steps;
            
}

int main() { 
   
  // int A[] = gets(stdin);  
  // cout << Consecutive(A, sizeof(A)/sizeof(A[0]));
  int B[] = {4, 8, 6};  
  cout << Consecutive(B, sizeof(B)/sizeof(B[0])) << '\n'; // expected output: 2
  int C[] = {5,10,15};  
  cout << Consecutive(C, sizeof(C)/sizeof(C[0])) << '\n'; // expected output: 8
  int D[] = {-2,10,4};  
  cout << Consecutive(D, sizeof(D)/sizeof(D[0])) << '\n'; // expected output: 10
  
  return 0;    
}
