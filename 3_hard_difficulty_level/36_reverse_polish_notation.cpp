/*
Coderbyte coding challenge: Reverse Polish Notation

Using the C++ language, have the function ReversePolishNotation(str) read str
which will be an arithmetic expression composed of only integers and the
operators:
+,-,* and / and the input expression will be in postfix notation (Reverse Polish
notation), an example: (1 + 2) * 3 would be 1 2 + 3 * in postfix notation. Your
program should determine the answer for the given postfix expression. For
example: if str is 2 12 + 7 / then your program should output 2.

Sample test cases:

Input:  "1 1 + 1 + 1 +"
Output: 4

Input:  "4 5 + 2 1 + *"
Output: 27
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <stack>
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

int evaluate_simple_math_expression(const int first_number,
                                    const int second_number,
                                    const char operation) {
  switch (operation) {
    case '+':
      return first_number + second_number;

    case '-':
      return first_number - second_number;

    case '*':
      return first_number * second_number;

    case '/':
      if (!second_number)
        throw runtime_error{"Division by zero is not allowed!"};
      return first_number / second_number;

    default:
      throw invalid_argument{"Specified mathematical operation is not valid!"};
  }
}

string evaluate_reverse_polish_notation_math_expression(string expression) {
  const size_t expression_len{expression.length()};
  size_t current_pos{};
  stack<int> result{};

  while (current_pos < expression_len) {
    current_pos = expression.find_first_of("-+*/1234567890", current_pos);

    if (string::npos == current_pos)
      break;

    if (('-' == expression[current_pos] || '+' == expression[current_pos] ||
         '*' == expression[current_pos] || '/' == expression[current_pos]) &&
        (current_pos + 1 == expression_len ||
         ' ' == expression[current_pos + 1])) {
      if (result.size() < 2)
        throw runtime_error{
            "Input math expression is not formatted correctly according to the "
            "rules imposed by the reverse polish notation!"};
      const int second_number{result.top()};
      result.pop();
      const int first_number{result.top()};
      result.pop();
      result.emplace(evaluate_simple_math_expression(
          first_number, second_number, expression[current_pos]));
      current_pos++;

    } else {
      const size_t next_pos{expression.find(' ', current_pos + 1)};
      result.emplace(
          stoi(expression.substr(current_pos, next_pos - current_pos)));
      current_pos = next_pos + 1;
    }
  }

  if (result.size() > 1)
    throw runtime_error{
        "Input math expression is not formatted correctly according to the "
        "rules imposed by the reverse polish notation!"};

  return to_string(result.top());
}

string ReversePolishNotation(string str) {
  str = trim(str);
  return evaluate_reverse_polish_notation_math_expression(move(str));
}

int main() {
  // cout << ReversePolishNotation(move(string{gets(stdin)}));
  cout << ReversePolishNotation(move(string{"1 2 + 3 *"}))
       << '\n';  // expected output: 9
  cout << ReversePolishNotation(move(string{"1 1 + 1 + 1 +"}))
       << '\n';  // expected output: 4
  cout << ReversePolishNotation(move(string{"4 5 + 2 1 + *"}))
       << '\n';  // expected output: 27

  return 0;
}
