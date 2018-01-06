/*
Coderbyte coding challenge: Permutation Step

Using the C++ language, have the function PermutationStep(num) take the num parameter being passed and return the next number greater than num using the same digits. 
For example: if num is 123 return 132, if it's 12453 return 12534. If a number has no greater permutations, return -1 (ie. 999).

Sample test Cases:

Input:  11121
Output: 11211

Input:  41352
Output: 41523
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int PermutationStep(const int num) { 

  string num_str { to_string(num) };
  
  const bool is_next_permutation_available { next_permutation(begin(num_str), end(num_str)) };

  if (!is_next_permutation_available) return -1;

  return stoi(num_str); 
            
}

int main() { 

  // cout << PermutationStep(gets(stdin));
  cout << PermutationStep(123) << '\n';   // expected output: 132
  cout << PermutationStep(12453) << '\n'; // expected output: 12534
  cout << PermutationStep(11121) << '\n'; // expected output: 11211
  cout << PermutationStep(41352) << '\n'; // expected output: 41523
  
  return 0;

}
