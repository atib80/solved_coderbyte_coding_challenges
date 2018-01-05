/*
Coderbyte coding challenge: Largest Pair

Using the C++ language, have the function LargestPair(num) take the num parameter being passed and determine the largest double digit number within the whole number. 
For example: if num is 4759472 then your program should return 94 because that is the largest double digit number. 
The input will always contain at least two positive digits.

Sample test cases:

Input:  453857
Output: 85

Input:  363223311
Output: 63
*/

#include <iostream>
#include <string>
#include <set>

using namespace std;

int LargestPair(int num) { 

  string num_str { to_string(num) };

  set<int> two_digit_numbers{};

  for (size_t i{}; i < num_str.length() - 1; i++) {
  	two_digit_numbers.insert(stoi(num_str.substr(i, 2)));
  }

  return (*(--end(two_digit_numbers)));
           
}

int main() { 
  
  // cout << LargestPair(gets(stdin));
  cout << LargestPair(4759472) << '\n';   // expected output: 94
  cout << LargestPair(453857) << '\n';    // expected output: 85
  cout << LargestPair(363223311) << '\n'; // expected output: 63
  return 0;    
}
