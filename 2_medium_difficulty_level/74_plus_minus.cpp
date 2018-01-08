/*
Coderbyte coding challenge: Plus Minus

Using the C++ language, have the function PlusMinus(num) read the num parameter being passed which will be a combination of 1 or more single digits, and determine 
if it's possible to separate the digits with either a plus or minus sign to get the final expression to equal zero. For example: if num is 35132 then it's possible 
to separate the digits the following way, 3 - 5 + 1 + 3 - 2, and this expression equals zero. Your program should return a string of the signs you used, 
so for this example your program should return -++-. If it's not possible to get the digit expression to equal zero, return the string not possible.

Sample test cases:

Input:  199
Output: "not possible"

Input:  26712
Output: "-+--"
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string PlusMinus(const int num) {

  const string num_str{to_string(num)};
  const size_t num_digits_size{num_str.length()};
  if (1u == num_digits_size) return "not possible";
  const size_t max_operations{num_digits_size - 1};

  string op_seq { string(max_operations, '-') + string(max_operations, '+') };

  sort(begin(op_seq), end(op_seq));

  vector<string> result_op_seq_strings{};

  do {

  	int result{static_cast<int>(num_str[0] - '0')};
  	string current_operations_seq{};
  	current_operations_seq.reserve(16);  	
  	bool is_result_zero{};

  	for (size_t i{}; (i < max_operations && !is_result_zero); i++) {

  		switch (op_seq[i]) {

  			case '-':
  				current_operations_seq.push_back('-');
  			    result -= static_cast<int>(num_str[i + 1] - '0');
  			    if (!result) {
  			    	is_result_zero = true;
  			    	if (current_operations_seq.length() == max_operations) result_op_seq_strings.emplace_back(current_operations_seq);  			        
  			    }
  				break;

  			case '+':
  				current_operations_seq.push_back('+');
  				result += static_cast<int>(num_str[i + 1] - '0');
  				if (!result) {
  			    	is_result_zero = true;
  			    	if (current_operations_seq.length() == max_operations) result_op_seq_strings.emplace_back(current_operations_seq);   			    	
  			    }
  				break;

  			default:
  				return "not possible";
  				break;
  		}

  	}



  } while (next_permutation(begin(op_seq), end(op_seq)));

  if (result_op_seq_strings.empty()) return "not possible";

  return result_op_seq_strings.back();

}

int main() {
  
  // cout << PlusMinus(gets(stdin));
  cout << PlusMinus(35132) << '\n'; // expected output: "-++-"
  cout << PlusMinus(199) << '\n';   // expected output: "not possible"
  cout << PlusMinus(26712) << '\n'; // expected output: "-+--"
  
  return 0;    
}
