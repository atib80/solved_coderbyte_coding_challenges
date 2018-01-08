/*
Coderbyte coding challenge: String Expression

Using the C++ language, have the function StringExpression(str) read the str parameter being passed which will contain the written out version of the numbers 0-9 
and the words "minus" or "plus" and convert the expression into an actual final number written out as well. For example: if str is "foursixminustwotwoplusonezero" 
then this converts to "46 - 22 + 10" which evaluates to 34 and your program should return the final string threefour. If your final answer is negative 
it should include the word "negative."

Sample test cases:

Input:  "foursixminustwotwoplusonezero"
Output: "threefour"

Input:  "onezeropluseight"
Output: "oneeight"

Input:  "oneminusoneone"
Output: "negativeonezero"
*/

#include <iostream>
#include <sstream>
#include <cctype>
#include <string>
#include <vector>

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

int convert_digit_words_into_decimal_number(const string& number_str) {

	int number{};  	
  	const size_t number_str_len { number_str.length() };
  	size_t index{};

	while (index < number_str_len) {

		if (index == number_str.find("one", index)) {

		    number *= 10;
		    number++;
		    index += 3;
		
		} else if (index == number_str.find("two", index)) {

			number *= 10;
		    number += 2;
		    index += 3;

		} else if (index == number_str.find("three", index)) {

			number *= 10;
		    number += 3;
		    index += 5;

		} else if (index == number_str.find("four", index)) {

			number *= 10;
		    number += 4;
		    index += 4;

		} else if (index == number_str.find("five", index)) {

			number *= 10;
		    number += 5;
		    index += 4;

		} else if (index == number_str.find("six", index)) {

			number *= 10;
		    number += 6;
		    index += 3;

		} else if (index == number_str.find("seven", index)) {

			number *= 10;
		    number += 7;
		    index += 5;

		} else if (index == number_str.find("eight", index)) {

			number *= 10;
		    number += 8;
		    index += 5;

		} else if (index == number_str.find("nine", index)) {

			number *= 10;
		    number += 9;
		    index += 4;

		} else if (index == number_str.find("zero", index)) {

			number *= 10;
			index += 4;
		}  		
	}

	return number;
}

string print_out_number_digits_in_text_format(const int number) {	

	const string number_str { to_string(number) };

	ostringstream oss{};
	
	for (const char d : number_str) {
		
		switch (d) {

			case '-':
				oss << "negative";
				break;

			case '0': 
				oss << "zero";
				break;

			case '1':
				oss << "one";
				break;

			case '2':
				oss << "two";
				break;
			
			case '3': 
				oss << "three";
				break;

			case '4':
				oss << "four";
				break;

			case '5':
				oss << "five";
				break;

			case '6': 
				oss << "six";
				break;

			case '7':
				oss << "seven";
				break;

			case '8':
				oss << "eight";
				break;

			case '9':
				oss << "nine";
				break;
			
			default:
				break;
		}
	}

	return oss.str();
}

string StringExpression(string str) {

  str = trim(str);

  size_t operation_word_plus_offset { str.find("plus") };
  size_t operation_word_minus_offset { str.find("minus") };

  size_t operation_word_offset { operation_word_plus_offset < operation_word_minus_offset ? operation_word_plus_offset : operation_word_minus_offset };

   if (string::npos == operation_word_offset) return "not possible";

  size_t operation_word_len { operation_word_plus_offset < operation_word_minus_offset ? 4u : 5u};
  bool is_add_operation { operation_word_plus_offset < operation_word_minus_offset ? true : false }; 

  vector<bool> operations{};
  vector<string> numbers_str{};

  operations.push_back(is_add_operation);

  string number_str{};

  while (true) {

  	number_str = str.substr(0, operation_word_offset);

  	numbers_str.emplace_back(number_str);

  	number_str = str.substr(operation_word_offset + operation_word_len);

  	operation_word_plus_offset = number_str.find("plus");
    operation_word_minus_offset = number_str.find("minus");
    operation_word_offset = operation_word_plus_offset < operation_word_minus_offset ? operation_word_plus_offset : operation_word_minus_offset;

    if (string::npos == operation_word_offset) break;

    operation_word_len = operation_word_plus_offset < operation_word_minus_offset ? 4u : 5u;
    is_add_operation = operation_word_plus_offset < operation_word_minus_offset ? true : false;
    operations.push_back(is_add_operation);

    str = number_str;
  }

  if (!number_str.empty()) numbers_str.emplace_back(number_str);

  vector<int> number_values{};  

  for (size_t i{}; i != numbers_str.size(); i++) number_values.emplace_back(convert_digit_words_into_decimal_number(numbers_str[i]));  	

  int result{number_values[0]};

  for (size_t i{}; i < operations.size(); i++) {

	if (operations[i]) 
		result += number_values[i + 1];
	else 
		result -= number_values[i + 1];
  }

  return print_out_number_digits_in_text_format(result);            

}

int main() {  
  // cout << StringExpression(move(string{gets(stdin)}));
  cout << StringExpression(move(string{"foursixminustwotwoplusonezero"})) << '\n'; // expected output: "threefour"
  cout << StringExpression(move(string{"onezeropluseight"})) << '\n'; // expected output: "oneeight"
  cout << StringExpression(move(string{"oneminusoneone"})) << '\n';   // expected output: "negativeonezero"
  return 0;
}
