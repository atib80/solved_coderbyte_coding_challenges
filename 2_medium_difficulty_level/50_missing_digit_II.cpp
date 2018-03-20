/*
Coderbyte coding challenge: Missing Digit II

Using the C++ language, have the function MissingDigitII(str) take the str
parameter, which will be a simple mathematical formula with three numbers, a
single operator (+, -, *, or /) and an equal sign (=) and return the two digits
that complete the equation. In two of the numbers in the equation, there will be
a single ? character, and your program should determine what digits are missing
and return them separated by a space. For example, if str is "38?5 * 3 = 1?595"
then your program should output 6 1.

The ? character will always appear in both the first number and the last number
in the mathematical expression. There will always be a unique solution.

Sample test cases:

Input:  "56? * 106 = 5?678"
Output: "3 9"

Input:  "18?1 + 9 = 189?"
Output: "8 0"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

string trim(const string& input) {
  string output{input};
  output.erase(begin(output),
               find_if(begin(output), end(output),
                       [](const char ch) { return !isspace(ch); }));

  output.erase(find_if(output.rbegin(), output.rend(),
                       [](const char ch) { return !isspace(ch); })
                   .base(),
               end(output));

  return output;
}

string MissingDigitII(string str) {
  str = trim(str);

  size_t start{str.find_first_of("?1234567890")};

  if (string::npos == start)
    return "not possible";

  size_t last{str.find_first_not_of("?1234567890")};

  if (string::npos == last)
    return "not possible";

  string first_number_str{str.substr(start, last - start)};

  start = str.find_first_of("+-*/", last);

  if (string::npos == start)
    return "not possible";

  const char operation_sign{str[start]};

  start = str.find_first_of("1234567890", start + 1);

  if (string::npos == start)
    return "not possible";

  size_t second_number_end_pos{str.find(' ', start + 1)};

  string second_number_str{str.substr(start, second_number_end_pos - start)};

  start = str.find_first_of("?1234567890", second_number_end_pos + 1);

  string result_number_str{trim(str.substr(start))};

  string first_number_digits{"0123456789"};

  const size_t first_number_question_mark_pos{first_number_str.find('?')};
  const size_t result_number_question_mark_pos{result_number_str.find('?')};

  if (0 == first_number_question_mark_pos)
    first_number_digits.erase(begin(first_number_digits));

  string result_number_digits{"0123456789"};

  if (0 == result_number_question_mark_pos)
    result_number_digits.erase(begin(result_number_digits));

  const int second_number{stoi(second_number_str)};

  ostringstream oss{};

  for (size_t i{}; i < first_number_digits.length(); ++i) {
    for (size_t j{}; j < result_number_digits.length(); ++j) {
      swap(first_number_digits[i],
           first_number_str[first_number_question_mark_pos]);
      const int first_number{stoi(first_number_str)};

      swap(result_number_digits[j],
           result_number_str[result_number_question_mark_pos]);
      const int result_number{stoi(result_number_str)};

      switch (operation_sign) {
        case '+':
          if (result_number == first_number + second_number) {
            oss << first_number_str[first_number_question_mark_pos] << ' '
                << result_number_str[result_number_question_mark_pos];
            return oss.str();
          }
          break;

        case '-':
          if (result_number == first_number - second_number) {
            oss << first_number_str[first_number_question_mark_pos] << ' '
                << result_number_str[result_number_question_mark_pos];
            return oss.str();
          }
          break;

        case '*':
        case 'x':
          if (result_number == first_number * second_number) {
            oss << first_number_str[first_number_question_mark_pos] << ' '
                << result_number_str[result_number_question_mark_pos];
            return oss.str();
          }
          break;

        case '/':
          if (result_number == first_number / second_number) {
            oss << first_number_str[first_number_question_mark_pos] << ' '
                << result_number_str[result_number_question_mark_pos];
            return oss.str();
          }
          break;

        default:
          throw runtime_error(
              "Illegal unsupported math operation has been specified!");
      }

      swap(first_number_digits[i],
           first_number_str[first_number_question_mark_pos]);
      swap(result_number_digits[j],
           result_number_str[result_number_question_mark_pos]);
    }
  }

  return "not possible";
}

int main() {
  // cout << MissingDigitII(move(string{gets(stdin)}));
  cout << MissingDigitII(move(string{"38?5 * 3 = 1?595"}))
       << '\n';  // expected output: "6 1"
  cout << MissingDigitII(move(string{"56? * 106 = 5?678"}))
       << '\n';  // expected output: "3 9"
  cout << MissingDigitII(move(string{"18?1 + 9 = 189?"}))
       << '\n';  // expected output: "8 0"
  cout << MissingDigitII(move(string{"50? / 5 = ?00"}))
       << '\n';  // expected output: "0 1"

  return 0;
}
