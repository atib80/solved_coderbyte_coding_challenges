/*
Coderbyte coding challenge: Calculator v2

{alternative iterative solution for the Calculator coding challenge
(simple math expression parser) implemented by using stack}

Using the C++ language, have the function Calculator(str) take the str parameter
being passed and evaluate the mathematical expression within in. For example, if
str were "2+(3-1)*3" the output should be 8. Another example: if str were
"(2-0)*(6/2)" the output should be 6. There can be parenthesis within the string
so you must evaluate it properly according to the rules of arithmetic. The
string will contain the operators: +, -, /, *, (, and ). If you have a string
like this: #/#*# or #+#(#)/#, then evaluate from left to right. So divide then
multiply, and for the second one multiply, divide, then add. The evaluations
will be such that there will not be any decimal operations, so you do not need
to account for rounding and whatnot. Hard challenges are worth 15 points and you
are not timed for them.

Sample test cases:

Input:  "6*(4/2)+3*1"
Output: "15"

Input:  "6/3-1"
Output: "1"
*/

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

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

string remove_unnecessary_white_space_characters(string str) {
  string cleaned_str{};
  cleaned_str.reserve(str.length());

  for (size_t i{}; i < str.length(); i++) {
    if (!isspace(str[i]))
      cleaned_str.push_back(str[i]);
  }

  return cleaned_str;
}

void insert_missing_multiplication_symbols(string& str) {
  size_t current_pos{};

  while (true) {
    current_pos = str.find(")(", current_pos);

    if (string::npos == current_pos)
      break;

    str.insert(current_pos + 1, 1, '*');

    current_pos += 3;
  }

  current_pos = 0u;

  while (true) {
    current_pos = str.find(") (", current_pos);

    if (string::npos == current_pos)
      break;

    str[current_pos + 1] = '*';

    current_pos += 3;
  }

  size_t number_end_pos{};

  while (true) {
    number_end_pos = str.find_first_of("0123456789", number_end_pos);

    if (string::npos == number_end_pos)
      break;

    number_end_pos = str.find_first_not_of("0123456789", number_end_pos);

    if (string::npos == number_end_pos)
      break;

    if ('(' == str[number_end_pos]) {
      str.insert(number_end_pos, 1, '*');

      number_end_pos += 2;
    } else if (number_end_pos < str.length() - 1 &&
               ' ' == str[number_end_pos] && '(' == str[number_end_pos + 1]) {
      str[number_end_pos] = '*';

      number_end_pos += 2;
    }
  }

  size_t prnths_end_pos{};

  while (true) {
    prnths_end_pos = str.find(')', prnths_end_pos);

    if (string::npos == prnths_end_pos)
      break;

    const size_t number_start_pos{
        str.find_first_of("0123456789", prnths_end_pos + 1)};

    if (string::npos == number_start_pos)
      break;

    if (')' == str[number_start_pos - 1]) {
      str.insert(number_start_pos, 1, '*');

      number_end_pos += 2;
    } else if (' ' == str[number_start_pos - 1] &&
               ')' == str[number_start_pos - 2]) {
      str[number_start_pos - 1] = '*';
    }

    prnths_end_pos += 2;
  }
}

enum class operation { plus, minus, multiplies, divides };

bool is_math_expression_correctly_formatted(const string& expression) {
  int prnths_balance_count{};

  if (')' == expression.front())
    return false;

  if ('(' == expression.back())
    return false;

  for (size_t i{}; i < expression.length(); i++) {
    if ('(' == expression[i])
      prnths_balance_count++;

    else if (')' == expression[i]) {
      if (!prnths_balance_count)
        return false;

      prnths_balance_count--;
    }
  }

  if (prnths_balance_count)
    return false;

  return true;
}

double evaluate_simple_math_expression(string expression) {
  size_t multiply_divide_op_count{};
  size_t plus_minus_op_count{};
  vector<operation> operations{};
  vector<double> sub_expression_results{};

  const char* expression_iter{expression.c_str()};
  const char* expression_last{expression_iter + expression.length()};

  while (true) {
    char* last_iter{};
    sub_expression_results.emplace_back(strtod(expression_iter, &last_iter));
    expression_iter = last_iter;

    if (expression_iter < expression_last) {
      switch (*expression_iter) {
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
          ostringstream oss{};
          oss << expression[0] << " is not a valid operator!";
          throw runtime_error{oss.str()};
      }

      expression_iter++;
    } else
      break;
  }

  size_t i{};
  while (multiply_divide_op_count && i < sub_expression_results.size() - 1) {
    if (operation::multiplies == operations[i]) {
      sub_expression_results[i] *= sub_expression_results[i + 1];
      sub_expression_results.erase(begin(sub_expression_results) + i + 1);
      operations.erase(begin(operations) + i);
      multiply_divide_op_count--;
      continue;
    }

    if (operation::divides == operations[i]) {
      sub_expression_results[i] /= sub_expression_results[i + 1];
      sub_expression_results.erase(begin(sub_expression_results) + i + 1);
      operations.erase(begin(operations) + i);
      multiply_divide_op_count--;
      continue;
    }

    i++;
  }

  i = 0;
  while (plus_minus_op_count && i < sub_expression_results.size() - 1) {
    if (operation::plus == operations[i]) {
      sub_expression_results[i] += sub_expression_results[i + 1];
      sub_expression_results.erase(begin(sub_expression_results) + i + 1);
      operations.erase(begin(operations) + i);
      plus_minus_op_count--;
      continue;
    }

    if (operation::minus == operations[i]) {
      sub_expression_results[i] -= sub_expression_results[i + 1];
      sub_expression_results.erase(begin(sub_expression_results) + i + 1);
      operations.erase(begin(operations) + i);
      plus_minus_op_count--;
      continue;
    }

    i++;
  }

  return sub_expression_results.front();
}

string evaluate_math_expression(
    string expression,
    const bool is_round_to_nearest_whole_number = false) {
  size_t open_prnths_count{}, close_prnths_count{};

  for (size_t i{}; i < expression.length(); i++) {
    if ('(' == expression[i])
      open_prnths_count++;
    else if (')' == expression[i])
      close_prnths_count++;
  }

  if (!open_prnths_count && !close_prnths_count) {
    // if there are no () symbols present in the input math expression, we
    // simply evaluate it without breaking it up into subexpression delimited by
    // ( and ) characters
    const auto result = evaluate_simple_math_expression(move(expression));
    if (is_round_to_nearest_whole_number)
      return to_string(static_cast<int64_t>(round(result)));
    return to_string(result);
  }
  if (open_prnths_count != close_prnths_count ||
      !is_math_expression_correctly_formatted(expression))
    // if the input math expression doesn't contain an equal number of '(' and
    // ')' characters or if it's not formatted correctly, we throw a runtime
    // exception
    throw runtime_error(
        "Input math expression string isn't correctly formatted!");

  stack<size_t> opening_prnths_positions{{expression.find('(')}};

  size_t prev_pos{opening_prnths_positions.top()};

  while (!opening_prnths_positions.empty()) {
    const size_t next_pos{expression.find_first_of("()", prev_pos + 1)};

    if ('(' == expression[next_pos]) {
      prev_pos = next_pos;
      opening_prnths_positions.emplace(next_pos);
      continue;
    }

    const size_t sub_expression_start{opening_prnths_positions.top() + 1};
    const size_t sub_expression_last{next_pos};

    expression.replace(
        opening_prnths_positions.top(),
        sub_expression_last - opening_prnths_positions.top() + 1,
        to_string(evaluate_simple_math_expression(move(
            expression.substr(sub_expression_start,
                              sub_expression_last - sub_expression_start)))));
    opening_prnths_positions.pop();
    prev_pos = sub_expression_start;

    if (opening_prnths_positions.empty() &&
        string::npos != expression.find('(', prev_pos + 1)) {
      prev_pos = expression.find('(', prev_pos + 1);
      opening_prnths_positions.emplace(prev_pos);
    }
  }

  const auto result = evaluate_simple_math_expression(move(expression));
  if (is_round_to_nearest_whole_number)
    return to_string(static_cast<int64_t>(round(result)));
  return to_string(result);
}

string calculator(string str) {
  str = remove_unnecessary_white_space_characters(move(str));
  insert_missing_multiplication_symbols(str);
  return evaluate_math_expression(move(str), true);
}

int main() {
  // cout << calculator(move(string{gets(stdin)}));
  cout << calculator(move(string{"2+(3-1)*3"}))
       << '\n';  // expected output: "8"
  cout << calculator(move(string{"(2-0)*(6/2)"}))
       << '\n';  // expected output: "6"
  cout << calculator(move(string{"6*(4/2)+3*1"}))
       << '\n';                                       // expected output: "15"
  cout << calculator(move(string{"6/3-1"})) << '\n';  // expected output: "1"
  cout << calculator(move(string{"7-4-1+8(3)/2"}))
       << '\n';                                       // expected output: "14"
  cout << calculator(move(string{"20"})) << '\n';     // expected output: "20"
  cout << calculator(move(string{"(20)"})) << '\n';   // expected output: "20"
  cout << calculator(move(string{"-20"})) << '\n';    // expected output: "-20"
  cout << calculator(move(string{"(-20)"})) << '\n';  // expected output: "-20"

  return 0;
}
