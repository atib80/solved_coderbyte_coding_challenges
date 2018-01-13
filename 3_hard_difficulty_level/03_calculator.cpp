/*
Coderbyte coding challenge: Calculator

Using the C++ language, have the function Calculator(str) take the str parameter being passed and evaluate the mathematical expression within in.
For example, if str were "2+(3-1)*3" the output should be 8. Another example: if str were "(2-0)*(6/2)" the output should be 6.
There can be parenthesis within the string so you must evaluate it properly according to the rules of arithmetic.
The string will contain the operators: +, -, /, *, (, and ). If you have a string like this: #/#*# or #+#(#)/#, then evaluate from left to right.
So divide then multiply, and for the second one multiply, divide, then add.
The evaluations will be such that there will not be any decimal operations, so you do not need to account for rounding and whatnot.
Hard challenges are worth 15 points and you are not timed for them.

Sample test cases:

Input:  "6*(4/2)+3*1"
Output: "15"

Input:  "6/3-1"
Output: "1"
*/

#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string trim(const string& str)
{
	const size_t str_len{ str.length() };

	if (!str_len) return string{};

	size_t first{}, last{ str_len - 1 };

	for (; first <= last; ++first)
	{
		if (!isspace(str[first])) break;
	}

	if (first > last) return string{};

	for (; last > first; --last)
	{
		if (!isspace(str[last])) break;
	}

	return str.substr(first, last - first + 1);
}

void insert_missing_multiplication_symbols(string& str) {

	size_t current_pos{};

	while (true) {

		current_pos = str.find(")(", current_pos);

		if (string::npos == current_pos) break;

		str.insert(current_pos + 1, 1, '*');

		current_pos += 3;

	}

	current_pos = 0u;

	while (true) {

		current_pos = str.find(") (", current_pos);

		if (string::npos == current_pos) break;

		str[current_pos + 1] = '*';

		current_pos += 3;		
	}

	size_t number_end_pos{};

	while (true) {

		number_end_pos = str.find_first_of("0123456789", number_end_pos);

		if (string::npos == number_end_pos) break;

		number_end_pos = str.find_first_not_of("0123456789", number_end_pos);

		if (string::npos == number_end_pos) break;

		if ('(' == str[number_end_pos]) {

			str.insert(number_end_pos, 1, '*');

			number_end_pos += 2;
		
		} else if ( (number_end_pos < (str.length() - 1)) && (' ' == str[number_end_pos]) && ('(' == str[number_end_pos + 1]) ) {

			str[number_end_pos] = '*';

			number_end_pos += 2;
		}
	}

	size_t number_start_pos{}, prnths_end_pos{};

	while (true) {

		prnths_end_pos = str.find(')', prnths_end_pos);

		if (string::npos == prnths_end_pos) break;

		number_start_pos = str.find_first_of("0123456789", prnths_end_pos + 1);

		if (string::npos == number_start_pos) break;

		if (')' == str[number_start_pos - 1]) {

			str.insert(number_start_pos, 1, '*');

			number_end_pos += 2;
		
		} else if ((' ' == str[number_start_pos - 1]) && (')' == str[number_start_pos - 2]) ) {

			str[number_start_pos - 1] = '*';

			number_start_pos++;
		}

		prnths_end_pos += 2;
	}
}

enum class operation { plus, minus, multiplies, divides };

int evaluate_expression_in_parenthesis(string expression) {

	int multiply_divide_op_count{};
	int plus_minus_op_count{};

	vector<operation> operations{};
	vector<int> sub_expression_results{};

	while (true) {		

		size_t number_start_pos { expression.find_first_of("0123456789") };

		if (string::npos == number_start_pos) break;

		size_t begin_prnths_pos{ expression.find('(') };

		size_t end_prnths_pos{ string::npos };

		if (string::npos != begin_prnths_pos) end_prnths_pos = expression.find(')', begin_prnths_pos + 1);

		if ((string::npos != begin_prnths_pos) && (string::npos != end_prnths_pos) && (begin_prnths_pos < number_start_pos)) {

			string sub_expression_str{ expression.substr(begin_prnths_pos + 1, end_prnths_pos - (begin_prnths_pos + 1)) };

			sub_expression_results.emplace_back(evaluate_expression_in_parenthesis(move(sub_expression_str)));

			const size_t operation_pos = expression.find_first_of("+-*/", end_prnths_pos + 1);

			begin_prnths_pos = expression.find('(', end_prnths_pos + 1);

			number_start_pos = expression.find_first_of("0123456789", end_prnths_pos + 1);

			if (string::npos == operation_pos || string::npos == number_start_pos) break;

			switch (expression[operation_pos]) {

				case '+':
					operations.emplace_back(operation::plus);
					plus_minus_op_count++;
					break;

				case '-':
					operations.emplace_back(operation::minus);
					plus_minus_op_count++;
					break;

				case '*':
					operations.emplace_back(operation::multiplies);
					multiply_divide_op_count++;
					break;

				case '/':
					operations.emplace_back(operation::divides);
					multiply_divide_op_count++;
					break;

				default:
					break;

			}

			expression.erase(begin(expression), begin(expression) + min(begin_prnths_pos, number_start_pos));

			continue;

		}		

		const size_t number_end_pos { expression.find_first_not_of("0123456789", number_start_pos + 1) };

		int number_value = stoi(expression.substr(number_start_pos, number_end_pos - number_start_pos));

		size_t operation_pos { expression.find_first_of("+-*/") };

		if (string::npos == operation_pos) {

			sub_expression_results.emplace_back(number_value);
			break;

		}
		
		if (operation_pos < number_start_pos) {

			for (size_t i { operation_pos }; i < number_start_pos; i++) {

				if ('-' == expression[i]) number_value = -number_value;

			}

			operation_pos = expression.find_first_of("+-*/", number_end_pos);

			if (string::npos == operation_pos) {

				sub_expression_results.emplace_back(number_value);
				break;

			}

		}


		sub_expression_results.emplace_back(number_value);

		switch (expression[operation_pos]) {

			case '+':
				operations.emplace_back(operation::plus);
				plus_minus_op_count++;
				break;

			case '-':
				operations.emplace_back(operation::minus);
				plus_minus_op_count++;
				break;

			case '*':
				operations.emplace_back(operation::multiplies);
				multiply_divide_op_count++;
				break;

			case '/':
				operations.emplace_back(operation::divides);
				multiply_divide_op_count++;
				break;

			default:
				break;

		}

		expression.erase( begin(expression), begin(expression) + expression.find_first_of("+-*/()0123456789", operation_pos + 1) );

	}

		while (multiply_divide_op_count) {

			for (size_t i{}; i < sub_expression_results.size() - 1; i++) {

				if (operation::multiplies == operations[i]) {

					sub_expression_results[i] *= sub_expression_results[i + 1];
					sub_expression_results.erase(begin(sub_expression_results) + i + 1);
					operations.erase(begin(operations) + i);
					multiply_divide_op_count--;
					break;


				}
				
				if (operation::divides == operations[i]) {

					sub_expression_results[i] /= sub_expression_results[i + 1];
					sub_expression_results.erase(begin(sub_expression_results) + i + 1);
					operations.erase(begin(operations) + i);
					multiply_divide_op_count--;
					break;
				}

			}

		}

		while (plus_minus_op_count) {

			for (size_t i{}; i < sub_expression_results.size() - 1; i++) {

				if (operation::plus == operations[i]) {

					sub_expression_results[i] += sub_expression_results[i + 1];
					sub_expression_results.erase(begin(sub_expression_results) + i + 1);
					operations.erase(begin(operations) + i);
					plus_minus_op_count--;
					break;


				}
				
				if (operation::minus == operations[i]) {

					sub_expression_results[i] -= sub_expression_results[i + 1];
					sub_expression_results.erase(begin(sub_expression_results) + i + 1);
					operations.erase(begin(operations) + i);
					plus_minus_op_count--;
					break;
				}

			}

		}


	return sub_expression_results[0];

}


string calculator(string str) {

	str = trim(str);

	const size_t operation_pos { str.find_first_of("+-*/") };

	const size_t number_start_pos{str.find_first_of("0123456789")};

	size_t number_end_pos{string::npos};

	if (string::npos != number_start_pos) number_end_pos = str.find_first_not_of("0123456789", number_start_pos + 1);

	const size_t next_number_start_pos { number_end_pos != string::npos ? str.find_first_of("0123456789", number_end_pos + 1) : string::npos };

	if (string::npos == operation_pos) {

		if (string::npos == number_start_pos) return "0";

		if (string::npos == number_end_pos) return str.substr(number_start_pos);

		return str.substr(number_start_pos, number_end_pos - number_start_pos);
	
	} else if ((string::npos != number_start_pos) && (string::npos == next_number_start_pos)) {

		int number_value { stoi(str.substr(number_start_pos, number_end_pos - number_start_pos)) };

		for (size_t i{}; i < number_start_pos; i++) {

			if ('-' == str[i]) number_value = -number_value;
		}

		return to_string(number_value);
	}

	insert_missing_multiplication_symbols(str);

	return to_string(evaluate_expression_in_parenthesis(move(str)));

}

int main() {

	// cout << calculator(move(string{gets(stdin)}));
	cout << calculator(move(string{ "2+(3-1)*3" })) << '\n';    // expected output: "8"
	cout << calculator(move(string{ "(2-0)*(6/2)" })) << '\n';  // expected output: "6"
	cout << calculator(move(string{ "6*(4/2)+3*1" })) << '\n';  // expected output: "15"
	cout << calculator(move(string{ "6/3-1" })) << '\n';        // expected output: "1"	
	cout << calculator(move(string{ "7-4-1+8(3)/2" })) << '\n'; // expected output: "14"
	cout << calculator(move(string{ "20" })) << '\n';          // expected output: "20"
	cout << calculator(move(string{ "(20)" })) << '\n';        // expected output: "20"
	cout << calculator(move(string{ "-20" })) << '\n';         // expected output: "-20"
	cout << calculator(move(string{ "(-20)" })) << '\n';       // expected output: "-20"
	
	return 0;
}
