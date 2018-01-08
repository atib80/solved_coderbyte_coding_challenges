/*
Coderbyte coding challenge: Ternary Converter

Using the C++ language, have the function TernaryConverter(num) take the num parameter being passed, which will always be a positive integer, 
and convert it into a ternary representation. For example: if num is 12 then your program should return 110.

Sample test cases:

Input:  21
Output: 210

Input:  67
Output: 2111
*/

#include <iostream>
#include <string>

using namespace std;

string TernaryConverter(int num) { 

  string result{};

  result.reserve(16); 

  while (num) {

  	const int factor { num % 3};

  	result.insert(0, 1, static_cast<char>('0' + factor));

  	num /= 3;  	

  }

  result.shrink_to_fit();

  return result;
  
}

int main() { 
  
  // cout << TernaryConverter(gets(stdin));
  cout << TernaryConverter(12) << '\n'; // expected output: 110
  cout << TernaryConverter(21) << '\n'; // expected output: 210
  cout << TernaryConverter(67) << '\n'; // expected output: 2111

  return 0;    
}
