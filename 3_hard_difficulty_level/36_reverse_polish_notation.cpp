/*
Coderbyte coding challenge: Reverse Polish Notation

Using the C++ language, have the function ReversePolishNotation(str) read str which will be an arithmetic expression composed of only integers and the operators:
+,-,* and / and the input expression will be in postfix notation (Reverse Polish notation), an example: (1 + 2) * 3 would be 1 2 + 3 * in postfix notation.
Your program should determine the answer for the given postfix expression. For example: if str is 2 12 + 7 / then your program should output 2.

Sample test cases:

Input:  "1 1 + 1 + 1 +"
Output: 4

Input:  "4 5 + 2 1 + *"
Output: 27
*/

#include <cctype>
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

string trim(const string &str)
{
    const size_t str_len{str.length()};

    if (!str_len)
        return string{};

    size_t first{}, last{str_len - 1};

    for (; first <= last; ++first)
    {
        if (!isspace(str[first]))
            break;
    }

    if (first > last)
        return string{};

    for (; last > first; --last)
    {
        if (!isspace(str[last]))
            break;
    }

    return str.substr(first, last - first + 1);
}

int evaluate_simple_math_expression(const int first_number, const int second_number, const char operation)
{
    switch (operation)
    {
    case '+':
        return (first_number + second_number);

    case '-':
        return (first_number - second_number);

    case '*':
        return (first_number * second_number);

    case '/':
        if (!second_number)
            throw runtime_error{"Division by zero is not allowed!"};
        return (first_number / second_number);

    default:
        throw invalid_argument{"Specified mathematical operation is not valid!"};
    }
}

bool process_reverse_polish_notation_sub_expression(string &expression, string &expression_result)
{
    size_t si{};

    while (string::npos != si)
    {
        size_t si1{expression.find_first_of("0123456789", si)};

        if (string::npos == si1)
            break;

        const size_t ei1{expression.find_first_not_of("0123456789", si1 + 1)};

        if (string::npos == ei1)
            break;

        int first_number{stoi(expression.substr(si1, ei1 - si1))};

        size_t si2{expression.find_first_of("+-*/0123456789", ei1 + 1)};

        if ('+' == expression[si2] || '-' == expression[si2] ||
            '*' == expression[si2] || '/' == expression[si2])
        {
            si = expression.find_first_of("+-*/", si2 + 1);
            continue;
        }

        size_t ei2{expression.find_first_not_of("0123456789", si2 + 1)};
        int second_number{stoi(expression.substr(si2, ei2 - si2))};

        if (string::npos == ei2)
            break;

        si = expression.find_first_of("+-*/0123456789", ei2 + 1);

        if (string::npos == si)
            break;

        while (('+' != expression[si]) && ('-' != expression[si]) && ('*' != expression[si]) && ('/' != expression[si]))
        {
            si1 = si2;
            si2 = si;
            first_number = second_number;
            ei2 = expression.find_first_not_of("0123456789", si2 + 1);
            second_number = stoi(expression.substr(si2, ei2 - si2));

            si = expression.find_first_of("+-*/0123456789", ei2 + 1);

            if (string::npos == si)
                return false;
        }

        const string result{to_string(evaluate_simple_math_expression(first_number, second_number, expression[si]))};

        expression.replace(si1, si - si1 + 1, result);

        if (string::npos == expression.find_first_of("+-*/"))
        {
            expression_result = result;
            return true;
        }

        if (process_reverse_polish_notation_sub_expression(expression, expression_result))
            return true;
    }

    return false;
}

string ReversePolishNotation(string str)
{
    str = trim(str);

    string result{};
    process_reverse_polish_notation_sub_expression(str, result);

    return result;
}

int main()
{
    // cout << ReversePolishNotation(move(string{gets(stdin)}));
    cout << ReversePolishNotation(move(string{"1 2 + 3 *"})) << '\n';     // expected output: 9
    cout << ReversePolishNotation(move(string{"1 1 + 1 + 1 +"})) << '\n'; // expected output: 4
    cout << ReversePolishNotation(move(string{"4 5 + 2 1 + *"})) << '\n'; // expected output: 27

    return 0;
}
