/*
Coderbyte coding challenge: Missing Digit II

Using the C++ language, have the function MissingDigitII(str) take the str parameter, which will be a simple mathematical formula with three numbers, 
a single operator (+, -, *, or /) and an equal sign (=) and return the two digits that complete the equation. In two of the numbers in the equation, 
there will be a single ? character, and your program should determine what digits are missing and return them separated by a space. 
For example, if str is "38?5 * 3 = 1?595" then your program should output 6 1.

The ? character will always appear in both the first number and the last number in the mathematical expression. 
There will always be a unique solution.

Sample test cases:

Input:  "56? * 106 = 5?678"
Output: "3 9"

Input:  "18?1 + 9 = 189?"
Output: "8 0"
*/

#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <stdexcept>

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

string MissingDigitII(string str) {

  str = trim(str);

  size_t start{str.find_first_of("?1234567890")};

  if (string::npos == start) return string{"Not possible!"};

  size_t last{str.find_first_not_of("?1234567890")};

  if (string::npos == last) return string{"Not possible!"};

  string first_number_str {str.substr(start, last - start)};

  start = str.find_first_of("+-*/", last);

  if (string::npos == start) return string{"Not possible!"};

  const char operation_sign { str[start] };

  start = str.find_first_of("1234567890", start + 1);

  if (string::npos == start) return string{"Not possible!"};

  size_t second_number_end_pos { str.find(' ', start + 1 ) };

  string second_number_str { str.substr(start, second_number_end_pos - start) };

  start = str.find_first_of("?1234567890", second_number_end_pos + 1);

  string result_number_str { str.substr(start) };

  string first_number_digits{"0123456789"};

  const size_t first_number_question_mark_pos { first_number_str.find('?') };
  const size_t result_number_question_mark_pos { result_number_str.find('?') };

  if (0u == first_number_question_mark_pos) first_number_digits.erase(begin(first_number_digits));

  string result_number_digits{"0123456789"};

  if (0u == result_number_question_mark_pos) result_number_digits.erase(begin(result_number_digits));

  const int second_number { stoi(second_number_str) };

  for (size_t i{}; i != first_number_digits.length(); ++i) {

    for (size_t j{}; j != result_number_digits.length(); ++j) {

      string first_num_str{first_number_str};
      first_num_str.replace(first_number_question_mark_pos, 1u, 1u, first_number_digits[i]);
      const int first_number {stoi(first_num_str)};

      string result_num_str{result_number_str};
      result_num_str.replace(result_number_question_mark_pos, 1u,  1u, result_number_digits[j]);
      const int result_number{stoi(result_num_str)};
      
      ostringstream oss{};

      switch (operation_sign) {

        case '+':
          if (result_number == (first_number + second_number)) {
            oss <<  first_number_digits[i] << ' ' << result_number_digits[j];
            return oss.str();
          }          
          break;

        case '-':
          if (result_number == (first_number - second_number)) {
            oss <<  first_number_digits[i] << ' ' << result_number_digits[j];
            return oss.str();
          } 
          break;

        case '*':
        case 'x':
          if (result_number == (first_number * second_number)) {
            oss <<  first_number_digits[i] << ' ' << result_number_digits[j];
            return oss.str();
          }
          break;

        case '/':
          if (result_number == (first_number / second_number)) {
            oss <<  first_number_digits[i] << ' ' << result_number_digits[j];
            return oss.str();
          }
          break;

        default:
          throw runtime_error("Illegal unsupported math operation has been specified!");
      }

    }

  }

  return string{"Not possible!"};

}

int main() { 
  
  // cout << MissingDigitII(move(string{gets(stdin)}));
  cout << MissingDigitII(move(string{"38?5 * 3 = 1?595"}))  << '\n';  // expected output: "6 1"
  cout << MissingDigitII(move(string{"56? * 106 = 5?678"})) << '\n';  // expected output: "3 9"
  cout << MissingDigitII(move(string{"18?1 + 9 = 189?"}))   << '\n';  // expected output: "8 0"
  cout << MissingDigitII(move(string{"50? / 5 = ?00"})) << '\n';      // expected output: "0 1"

  return 0;    
}
