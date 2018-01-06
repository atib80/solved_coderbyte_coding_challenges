/*
Coderbyte coding challenge: Simple Evens

Using the C++ language, have the function SimpleEvens(num) check whether every single number in the passed in parameter is even. 
If so, return the string true, otherwise return the string false. 
For example: if num is 4602225 your program should return the string false because 5 is not an even number.

Sample test cases:

Input:  2222220222
Output: "true"

Input:  20864646452
Output: "false"
*/

#include <iostream>
#include <cstdint>
#include <string>
#include <algorithm>

using namespace std;

string SimpleEvens(const int64_t num) {

	const string num_str{to_string(num)};

	return ( all_of(begin(num_str), end(num_str), [](const char ch){
		return ('0' == ch || '2' == ch || '4' == ch || '6' == ch || '8' == ch);
	}) ? "true" : "false" );
           
}

int main() { 

  // cout << SimpleEvens(gets(stdin));
  cout << SimpleEvens(4602225LL) << '\n';     // expected output: "false"
  cout << SimpleEvens(2222220222LL) << '\n';  // expected output: "true"
  cout << SimpleEvens(20864646452LL) << '\n'; // expected output: "false"
  
  return 0;
    
} 
