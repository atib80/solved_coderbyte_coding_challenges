/*
Coderbyte coding challenge: Array Addition

Using the C++ language, have the function ArrayAddition(arr) take the array of numbers stored in arr and return the string true 
if any combination of numbers in the array can be added up to equal the largest number in the array, otherwise return the string false. 
For example: if arr contains [4, 6, 23, 10, 1, 3] the output should return true because 4 + 6 + 10 + 3 = 23. 
The array will not be empty, will not contain all the same elements, and may contain negative numbers.

Sample test cases:

Input:  5,7,16,1,2
Output: "false"

Input:  3,5,-1,8,12
Output: "true"
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string ArrayAddition(const int* arr, const size_t arr_size) { 

  if (arr_size < 2) return string{"false"};

  vector<int> numbers(arr, arr + arr_size);

  sort(begin(numbers), end(numbers), [](const int lhs, const int rhs) {
    return (lhs > rhs);
  });

  const int maximum { numbers[0] };

   auto negative_pos = find_if(begin(numbers), end(numbers), [](const int& n) { 
      return (n < 0);
   });
   
   const bool negative_numbers_present_in_array { negative_pos != end(numbers) ? true : false }; 

  for (size_t i{1u}; i != numbers.size(); i++) {
      
    int current_sum{};
    
    for (size_t j{i}; j != numbers.size(); j++) {

      current_sum += numbers[j];

      if (maximum == current_sum) return string{"true"};

      if (current_sum > maximum) {        

        if (negative_numbers_present_in_array) {

          int balanced_sum { current_sum };
        
          for (auto start = negative_pos; start != end(numbers); ++start) {

            balanced_sum += *start;

            if (maximum == balanced_sum) return string{"true"};

          }

          if (balanced_sum > maximum) current_sum -= numbers[j];
         
         } else {

            current_sum -= numbers[j];

         }

      }

    }
  
  }

  return string{"false"};
    
}

int main() { 
   
  int A[] = gets(stdin);
  cout << ArrayAddition(A, sizeof(A)/sizeof(A[0]));   
  // const int A[] = {4, 6, 23, 10, 1, 3};
  // cout << ArrayAddition(A, sizeof(A)/sizeof(A[0])) << '\n'; // expected: "true"
  // const int B[] = {5,7,16,1,2};
  // cout << ArrayAddition(B, sizeof(B)/sizeof(B[0])) << '\n'; // expected: "false"
  // const int C[] = {3,5,-1,8,12};
  // cout << ArrayAddition(C, sizeof(C)/sizeof(C[0])) << '\n'; // expected: "true"
  
  return 0;
}
