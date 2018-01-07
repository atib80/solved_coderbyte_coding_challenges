/*
Coderbyte coding challenge: Missing Digit

Using the C++ language, have the function MissingDigit(str) take the str parameter, which will be a simple mathematical formula with three numbers, 
a single operator (+, -, *, or /) and an equal sign (=) and return the digit that completes the equation. 
In one of the numbers in the equation, there will be an x character, and your program should determine what digit is missing. 
For example, if str is "3x + 12 = 46" then your program should output 4. 
The x character can appear in any of the three numbers and all three numbers will be greater than or equal to 0 and less than or equal to 1000000.

Sample test cases:

Input:  "4 - 2 = x"
Output: 2

Input:  "1x0 * 12 = 1200"
Output: 0
*/

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string trim(const string& str)
{
	size_t begin_str{};
	size_t end_str{str.size() - 1};

	if (0u == str.length()) return string{};

	for (; begin_str <= end_str; ++begin_str)
	{
		if (!isspace(str[begin_str])) break;
	}

	if (begin_str > end_str) return string{};

	for (; end_str > begin_str; --end_str)
	{
		if (!isspace(str[end_str])) break;
	}

	return str.substr(begin_str, end_str - begin_str + 1);
}

int calculate_unknown_number_value(const char op, const int first_number = -1, const int second_number = -1, const int result = -1) {

	if (((-1 == first_number) && (-1 == second_number)) || ((-1 == first_number) && (-1 == result)) || ((-1 == second_number) && (-1 == result))) return 0;
	
	switch (op) {

    	case '+':
			if (-1 == first_number)
				return (result - second_number);
			else if (-1 == second_number)
				return (result - first_number);
			else
				return (first_number + second_number);		

		case '-':
			if (-1 == first_number)
				return (result + second_number);
			else if (-1 == second_number)
				return (first_number - result);
			else
				return (first_number - second_number);

		case '*':
			if (-1 == first_number)
				return (result / second_number);
			else if (-1 == second_number)
				return (result /  first_number);
			else
				return (first_number * second_number);

		case '/':
			if (-1 == first_number)
				return (result * second_number);
			else if (-1 == second_number)
				return (first_number / result);
			else
				return (first_number / second_number);

		default:
			return 0;

	}
}

string MissingDigit(string str) {

  str = trim(str);

  size_t start{str.find_first_of("xXyY1234567890")};

  if (string::npos == start) return string{"Not possible!"};

  size_t last{str.find_first_not_of("xXyY1234567890")};

  if (string::npos == last) return string{"Not possible!"};

  string first_num_str {str.substr(start, last - start)};

  start = str.find_first_of("+-*/", last);

  if (string::npos == start) return string{"Not possible!"};

  const char operation_sign { str[start] };

  start = str.find_first_of("xXyY1234567890", start + 1);

  if (string::npos == start) return string{"Not possible!"};

  size_t second_number_end_pos { str.find(' ', start + 1 ) };

  string second_num_str { str.substr(start, second_number_end_pos - start) };

  start = str.find_first_of("xXyY1234567890", second_number_end_pos + 1);

  string result_num_str { str.substr(start) };

  size_t var_x_index{string::npos};
  size_t var_x_pos{string::npos};

  if (string::npos != first_num_str.find_first_of("xyXY")) {

  	var_x_index = 0u;
  	var_x_pos = first_num_str.find_first_of("xyXY");
  
  } else if (string::npos != second_num_str.find_first_of("xyXY")) {

  	var_x_index = 1u;
  	var_x_pos = second_num_str.find_first_of("xyXY");

  } else if (string::npos != result_num_str.find_first_of("xyXY")) {

  	var_x_index = 2u;
  	var_x_pos = result_num_str.find_first_of("xyXY");

  }

  if (string::npos == var_x_index || string::npos == var_x_pos) return string{"Not possible!"};

  int first_number{-1}, second_number{-1}, result{-1};

  string whole_number{}, str_diff{};

  switch (var_x_index) {

  	case 0:
  		second_number = stoi(second_num_str);
  		result = stoi(result_num_str);
  		first_number = calculate_unknown_number_value(operation_sign, first_number, second_number, result);

  		if (!var_x_pos && (1u == first_num_str.length())) return to_string(first_number);

  		whole_number = to_string(first_number);

  		for (size_t i{var_x_pos}; i != whole_number.length(); i++) {

  			if (i >= first_num_str.length()) {
  				str_diff += whole_number.substr(i);
  				return str_diff;
  			}

  			if (whole_number[i] != first_num_str[i]) str_diff.push_back(whole_number[i]);
  		}

  		return str_diff;

  		break;

  	case 1:
  		first_number = stoi(first_num_str);
  		result = stoi(result_num_str);
  		second_number = calculate_unknown_number_value(operation_sign, first_number, second_number, result);

  		if (!var_x_pos && (1u == second_num_str.length())) return to_string(second_number);

  		whole_number = to_string(second_number);

  		for (size_t i{var_x_pos}; i != whole_number.length(); i++) {

  			if (i >= second_num_str.length()) {
  				str_diff += whole_number.substr(i);
  				return str_diff;
  			}

  			if (whole_number[i] != second_num_str[i]) str_diff.push_back(whole_number[i]);
  		}

  		return str_diff;

  		break;

  	case 2:
  		first_number = stoi(first_num_str);
  		second_number = stoi(second_num_str);
  		result = calculate_unknown_number_value(operation_sign, first_number, second_number, result);

  		if (!var_x_pos && (1u == result_num_str.length())) return to_string(result);

  		whole_number = to_string(result);

  		for (size_t i{var_x_pos}; i != whole_number.length(); i++) {

  			if (i >= result_num_str.length()) {
  				str_diff += whole_number.substr(i);
  				return str_diff;
  			}

  			if (whole_number[i] != result_num_str[i]) str_diff.push_back(whole_number[i]);
  		}

  		return str_diff;

  		break;

  	default:
  		return string{"Not possible!"};

  }

}

int main() { 
  
  // cout << MissingDigit(move(string{gets(stdin)}));
  cout << MissingDigit(move(string{"3x + 12 = 46"})) << '\n';    // expected output: 4
  cout << MissingDigit(move(string{"4 - 2 = x"})) << '\n';       // expected output: 2
  cout << MissingDigit(move(string{"1x0 * 12 = 1200"})) << '\n'; // expected output: 0
  
  return 0;    
}
