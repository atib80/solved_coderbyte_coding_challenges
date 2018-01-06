/*
Coderbyte coding challenge: Prime Time

Using the C++ language, have the function PrimeTime(num) take the num parameter being passed and return the string true 
if the parameter is a prime number, otherwise return the string false. The range will be between 1 and 2^16.

Sample test cases:

Input:  19
Output: "true"

Input:  110
Output: "false"
*/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

string PrimeTime(const int num) {

  if (2 == num || 3 == num || 5 == num) return string{"true"};

  if (num % 2 == 0 || num % 5 == 0) return string{"false"};

  const int highest_factor {static_cast<int>(sqrt(num)) + 1};

  for (int i{3}; i < highest_factor; i += 2) {
    
    if (num % i == 0) return string{"false"};

  }

  return string{"true"};
            
}

int main() { 
  
  // cout << PrimeTime(gets(stdin));
  cout << PrimeTime(3)  << '\n';  // expected output: "true"
  cout << PrimeTime(4)  << '\n';  // expected output: "false"
  cout << PrimeTime(5)  << '\n';  // expected output: "true"
  cout << PrimeTime(7)  << '\n';  // expected output: "true"
  cout << PrimeTime(19)  << '\n'; // expected output: "true"
  cout << PrimeTime(110) << '\n'; // expected output: "false"

  return 0;
} 
