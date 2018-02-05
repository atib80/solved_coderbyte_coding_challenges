/*
Coderbyte coding challenge: Simple SAT 

(I must admit, that it is not so simple after all :), 
although it's not the hardest coding challenge I've faced so far either.
The solution to this coding challenge is based upon my earlier submitted
solution for the 'Calculator' coding challenge. This program uses one of 
'Calculator's most significat functions (evaluate_expression_in_parenthesis) 
with a few small changes made to its code and a couple of additional
useful functions added to it to make it work with boolean expressions correctly 
for this coding challenge.)


Problem statement:

Using the C++ language, have the function SimpleSAT(str) read str which will be
a string consisting of letters, parenthesis, logical operators and tilde's
representing a Boolean formula. For example: str may be "(a&b)|c" which means (a
AND b) OR c. Your program should output the string yes if there is some
arrangement of replacing the letters with TRUE or FALSE in such a way that the
formula equates to TRUE. If there is no possible way of assigning TRUE or FALSE
to the letters, then your program should output the string no. In the example
above, your program would return yes because a=TRUE, b=TRUE and c=FALSE would
make the formula TRUE. Another example: if str is "((a&c)&~a)" which means ((a
AND c) AND NOT a) then your program should output no because it is not possible
to assign TRUE or FALSE values to the letters to produce a TRUE output.

A Boolean formula will always have at most 5 letters, i.e. a, b, c, d and e.
A tilde will never appear outside of a parenthesis, i.e. ~(a&b).

Sample test cases:

Input:  "(a&b&c)|~a"
Output: "yes"

Input:  "a&(b|c)&~b&~c"
Output: "no"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (!str_len)
    return string{};

  size_t first{}, last{str_len - 1};

  for (; first <= last; ++first) {
    if (!isspace(str[first]))
      break;
  }

  if (first > last)
    return string{};

  for (; last > first; --last) {
    if (!isspace(str[last]))
      break;
  }

  return str.substr(first, last - first + 1);
}

enum class operation { bool_and, bool_or, bool_not };

bool evaluate_boolean_expression_in_parenthesis(string expression) {
  vector<operation> operations{};
  vector<bool> sub_expression_results{};
  int boolean_and_or_op_count{};

  while (true) {
    size_t operation_pos{expression.find_first_of("&|")};

    size_t number_pos{expression.find_first_of("01")};

    if (string::npos == number_pos)
      break;

    size_t begin_prnths_pos{expression.find('(')};

    size_t end_prnths_pos{string::npos};

    if (string::npos != begin_prnths_pos)
      end_prnths_pos = expression.find(')', begin_prnths_pos + 1);

    if ((string::npos != begin_prnths_pos) &&
        (string::npos != end_prnths_pos) && (begin_prnths_pos < number_pos)) {
      string sub_expression_str{expression.substr(
          begin_prnths_pos + 1, end_prnths_pos - (begin_prnths_pos + 1))};

      const int result{
          evaluate_boolean_expression_in_parenthesis(move(sub_expression_str))};

      sub_expression_results.push_back(result);

      operation_pos = expression.find_first_of("&|", end_prnths_pos + 1);

      begin_prnths_pos = expression.find('(', end_prnths_pos + 1);

      number_pos = expression.find_first_of("01", end_prnths_pos + 1);

      if (string::npos == operation_pos || string::npos == number_pos)
        break;

      switch (expression[operation_pos]) {
        case '&':
          operations.emplace_back(operation::bool_and);
          boolean_and_or_op_count++;
          break;

        case '|':
          operations.emplace_back(operation::bool_or);
          boolean_and_or_op_count++;
          break;

        default:
          break;
      }

      expression.erase(begin(expression),
                       begin(expression) + min(begin_prnths_pos, number_pos));

      continue;
    }

    const bool logical_value{'0' != expression[number_pos] ? true : false};

    if (string::npos == operation_pos) {
      sub_expression_results.push_back(logical_value);
      break;
    }

    sub_expression_results.push_back(logical_value);

    switch (expression[operation_pos]) {
      case '&':
        operations.emplace_back(operation::bool_and);
        boolean_and_or_op_count++;
        break;

      case '|':
        operations.emplace_back(operation::bool_or);
        boolean_and_or_op_count++;
        break;

      default:
        break;
    }

    const size_t right_side_start_offset{
        expression.find_first_of("&|()01", operation_pos + 1)};

    expression.erase(begin(expression),
                     begin(expression) + right_side_start_offset);
  }

  while (boolean_and_or_op_count) {
    for (size_t i{}; i < sub_expression_results.size() - 1; i++) {
      if (operation::bool_and == operations[i]) {
        sub_expression_results[i] =
            sub_expression_results[i] && sub_expression_results[i + 1];
        sub_expression_results.erase(begin(sub_expression_results) + i + 1);
        operations.erase(begin(operations) + i);
        boolean_and_or_op_count--;
        break;
      }

      if (operation::bool_or == operations[i]) {
        sub_expression_results[i] =
            sub_expression_results[i] || sub_expression_results[i + 1];
        sub_expression_results.erase(begin(sub_expression_results) + i + 1);
        operations.erase(begin(operations) + i);
        boolean_and_or_op_count--;
        break;
      }
    }
  }

  return sub_expression_results[0];
}

void process_negation_unary_operations(string& expression) {
  size_t start{};

  while ((start = expression.find("~0", start)) != string::npos) {
    expression.replace(start, 2, 1, '1');
    start++;
  }

  start = 0;

  while ((start = expression.find("~1", start)) != string::npos) {
    expression.replace(start, 2, 1, '0');
    start++;
  }
}

void replace_var_letter_with_numeric_digit(string& expression,
                                           const char var_letter,
                                           const char digit) {
  for (size_t i{}; i < expression.length(); i++) {
    if (var_letter == expression[i]) {
      if ((0 != i) && isalnum(expression[i - 1]))
        continue;
      if ((expression.length() - 1 != i) && isalnum(expression[i + 1]))
        continue;
      expression[i] = digit;
    }
  }
}

string SimpleSAT(string str) {
  str = trim(str);

  set<char> variable_names{};

  for (const char ch : str) {
    if (isalpha(ch))
      variable_names.insert(ch);
  }

  const size_t operation_pos{str.find_first_of("~&|")};

  if (((string::npos == operation_pos) || ('~' == str[operation_pos])) &&
      (1 == variable_names.size()))
    return "yes";

  const size_t combinations{1u << variable_names.size()};

  for (size_t i{}; i < combinations; i++) {
    string expression{str};

    size_t current_sequence{i};

    for (const char ch : variable_names) {
      const char value{current_sequence & 1 ? '1' : '0'};

      current_sequence >>= 1;

      replace_var_letter_with_numeric_digit(expression, ch, value);
    }

    process_negation_unary_operations(expression);

    const bool result{evaluate_boolean_expression_in_parenthesis(expression)};

    if (result)
      return "yes";
  }

  return "no";
}

int main() {
  // cout << SimpleSAT(move(string{gets(stdin)}));	
  cout << SimpleSAT(move(string{"(a&b)|c"})) 
       << '\n';  // expected output: "yes"
  cout << SimpleSAT(move(string{"(a&b&c)|~a"}))
       << '\n';  // expected output: "yes"
  cout << SimpleSAT(move(string{"a&(b|c)&~b&~c"}))
       << '\n';  // expected output: "no"

  return 0;
}
