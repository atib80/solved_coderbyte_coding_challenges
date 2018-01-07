/*
Coderbyte coding challenge: Triple Double

Using the C++ language, have the function TripleDouble(num1,num2) take both parameters being passed, and return 1 if there is a straight triple of a number at any place 
in num1 and also a straight double of the same number in num2. For example: if num1 equals 451999277 and num2 equals 41177722899, 
then return 1 because in the first parameter you have the straight triple 999 and you have a straight double, 99, of the same number in the second parameter. 
If this isn't the case, return 0.

Sample test cases:
Input:  465555 & num2 = 5579
Output: 1

Input:  67844 & num2 = 66237
Output: 0
*/

#include <iostream>
#include <string>
#include <cstdint>
#include <unordered_set>

using namespace std;

int TripleDouble(int64_t num1, int64_t num2) { 

	const string num1_str{to_string(num1)};
	const string num2_str{to_string(num2)};

	unordered_set<char> digits{};

	for (const char digit : num1_str) digits.insert(digit);

	for (const char digit : digits) {

		const string triple_num(3, digit);
		const string double_num(2, digit);

		if ((string::npos != num1_str.find(triple_num)) && (string::npos != num2_str.find(double_num))) return 1;

	}
 
	return 0; 
            
}

int main() { 

  // cout << TripleDouble(gets(stdin));
  cout << TripleDouble(451999277LL, 41177722899LL) << '\n';
  cout << TripleDouble(465555LL, 5579LL) << '\n';
  cout << TripleDouble(67844LL, 66237LL) << '\n';
  return 0;    
}
