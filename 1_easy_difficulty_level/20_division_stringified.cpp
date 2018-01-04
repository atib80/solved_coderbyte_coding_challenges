/*
Coderbyte coding challenge: Division Stringified

Using the C++ language, have the function DivisionStringified(num1,num2) take both parameters being passed, divide num1 by num2, and return the result as a string 
with properly formatted commas. If an answer is only 3 digits long, return the number with no commas (ie. 2 / 3 should output "1"). For example: 
if num1 is 123456789 and num2 is 10000 the output should be "12,346".

Sample test cases:

Input:  5 & num2 = 2
Output: "3"

Input:  6874 & num2 = 67
Output: "103"
*/

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

string DivisionStringified(const vector<long>& numbers) { 
    
  const long num1 = numbers[0];
  const long num2 = numbers[1];
  if (0 == num2) return string{"Not possible!"};
  double result = static_cast<double>(num1) / static_cast<double>(num2);
  long whole_part = static_cast<long>(round(result));
  string whole_part_str{to_string(whole_part)};
  const size_t whole_part_str_len{whole_part_str.length()};
  if (whole_part_str_len <= 3) return whole_part_str;

  for (int i = static_cast<int>(whole_part_str_len - 3); i >= 0; i -= 3) {
  		whole_part_str.insert(i, 1, ',');
  }

  return whole_part_str;
}

int main() { 
  
  // const vector<long> numbers { gets(stdin) };
  // cout << DivisionStringified(numbers);
  cout << DivisionStringified({1, 10}) << '\n';            // expected output: "0"
  cout << DivisionStringified({5, 54}) << '\n';            // expected output: "0"
  cout << DivisionStringified({175, 24}) << '\n';          // expected output: "7"
  cout << DivisionStringified({101077282, 21123}) << '\n'; // expected output: "4,785"
  return 0;
}
