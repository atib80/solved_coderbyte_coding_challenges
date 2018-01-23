/*
Coderbyte coding challenge: Roman Numeral Reduction

Using the C++ language, have the function RomanNumeralReduction(str) read str which will be a string of roman numerals in decreasing order.
The numerals being used are: I for 1, V for 5, X for 10, L for 50, C for 100, D for 500 and M for 1000.
Your program should return the same number given by str using a smaller set of roman numerals.
For example: if str is "LLLXXXVVVV" this is 200, so your program should return CC because this is the shortest way to write 200
using the roman numeral system given above. If a string is given in its shortest form, just return that same string.

Sample test cases:

Input:  "XXXVVIIIIIIIIII"
Output: "L"

Input:  "DDLL"
Output: "MC"
*/

#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

string trim(const string& str)
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

size_t convert_roman_numeral_string_to_whole_number(const string& rnns)
{
    const unordered_map<char, size_t> roman_numerals{
        {'I', 1},{'V', 5},{'X', 10},{'L', 50},{'C', 100},{'D', 500},{'M', 1000}
    };

    size_t number{};

    for (const auto ch : rnns)
    {
        const auto itr = roman_numerals.find(ch);

        if (itr != end(roman_numerals)) number += itr->second;
    }

    return number;
}

string find_least_number_of_roman_numeral_characters_that_represent_number(const size_t number)
{
    const unordered_map<size_t, char> roman_numerals{
        {1, 'I'},{5, 'V'},{10, 'X'},{50, 'L'},{100, 'C'},{500, 'D'},{1000, 'M'}
    };
    const vector<size_t> values{1000, 500, 100, 50, 10, 5, 1};

    for (const auto value : values)
    {
        if (number % value == 0)
        {
            const auto itr = roman_numerals.find(value);
            if (itr != end(roman_numerals)) return string(number / value, itr->second);
        }
        else if (value < number) break;
    }

    string result{"-1"};

    size_t min_length{string::npos};

    string min_number_str{};

    for (size_t i{}; i < values.size(); i++)
    {
        size_t amount{number};
        string number_str{};

        bool skip_iteration{false};

        for (size_t j{i}; j < values.size(); j++)
        {
            if (values[j] > amount) continue;

            const size_t factor{amount / values[j]};

            if ((string::npos != min_length) && ((number_str.length() + factor) >= min_length))
            {
                skip_iteration = true;
                break;
            }

            number_str.append(factor, roman_numerals.find(values[j])->second);

            amount %= values[j];

            if (!amount) break;
        }

        if (!skip_iteration && (number_str.length() < min_length))
        {
            min_length = number_str.length();
            min_number_str = number_str;
        }
    }

    return min_number_str;
}

string RomanNumeralReduction(string str)
{
    str = trim(str);

    const size_t number{convert_roman_numeral_string_to_whole_number(str)};

    return find_least_number_of_roman_numeral_characters_that_represent_number(number);
}

int main()
{
    // cout << RomanNumeralReduction(move(string{gets(stdin)}));
    cout << RomanNumeralReduction(move(string{"LLLXXXVVVV"})) << '\n';      // expected output: "CC"
    cout << RomanNumeralReduction(move(string{"XXXVVIIIIIIIIII"})) << '\n'; // expected output: "L"
    cout << RomanNumeralReduction(move(string{"DDLL"})) << '\n';            // expected output: MC
    cout << RomanNumeralReduction(move(string{"MMM"})) << '\n';             // expected output: MMM

    return 0;
}
