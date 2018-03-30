/*
Coderbyte coding challenge: Plus Minus

Using the C++ language, have the function PlusMinus(num) read the num parameter
being passed which will be a combination of 1 or more single digits, and
determine if it's possible to separate the digits with either a plus or minus
sign to get the final expression to equal zero. For example: if num is 35132
then it's possible to separate the digits the following way, 3 - 5 + 1 + 3 - 2,
and this expression equals zero. Your program should return a string of the
signs you used, so for this example your program should return -++-. If it's not
possible to get the digit expression to equal zero, return the string not
possible.

Sample test cases:

Input:  199
Output: "not possible"

Input:  26712
Output: "-+--"
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

string PlusMinus_v1(const int num) {
  const string num_str{to_string(num)};
  const size_t num_digits_size{num_str.length()};
  if (1 == num_digits_size)
    return "not possible";
  const size_t max_operations{num_digits_size - 1};

  string op_seq{string(max_operations, '-') + string(max_operations, '+')};

  sort(begin(op_seq), end(op_seq));

  vector<string> result_op_seq_strings{};

  do {
    int result{static_cast<int>(num_str[0] - '0')};
    string current_operations_seq{};
    bool is_result_zero{};

    for (size_t i{}; i < max_operations && !is_result_zero; i++) {
      switch (op_seq[i]) {
        case '-':
          current_operations_seq.push_back('-');
          result -= static_cast<int>(num_str[i + 1] - '0');
          if (!result) {
            is_result_zero = true;
            if (current_operations_seq.length() == max_operations)
              result_op_seq_strings.emplace_back(current_operations_seq);
          }
          break;

        case '+':
          current_operations_seq.push_back('+');
          result += static_cast<int>(num_str[i + 1] - '0');
          if (!result) {
            is_result_zero = true;
            if (current_operations_seq.length() == max_operations)
              result_op_seq_strings.emplace_back(current_operations_seq);
          }
          break;

        default:
          return "not possible";
          break;
      }
    }

  } while (next_permutation(begin(op_seq), end(op_seq)));

  if (result_op_seq_strings.empty())
    return "not possible";

  return result_op_seq_strings.back();
}

string dec2bin(size_t decimal_number,
               bool pad_binary_number_string_with_leading_zeroes = false,
               const size_t max_pad_length = 32) {
  const size_t base_capacity_size{max_pad_length};
  size_t index{max_pad_length - 1};
  string result_number(base_capacity_size, '0');

  while (decimal_number) {
    if (decimal_number % 2 == 1)
      result_number[index] = '1';
    if (!index)
      break;
    index--;
    decimal_number /= 2;
  }

  if (!pad_binary_number_string_with_leading_zeroes) {
    const size_t first_non_zero_digit_pos{result_number.find('1', 0)};

    if (string::npos == first_non_zero_digit_pos)
      return "0";

    result_number = result_number.substr(first_non_zero_digit_pos);
  }

  return result_number;
}

string PlusMinus_v2(const int num) {
  const string num_str{to_string(num)};
  const size_t num_digits_size{num_str.length()};
  if (1 == num_digits_size)
    return "not possible";
  const size_t max_operations{num_digits_size - 1};
  const size_t max_operations_limit{1u << max_operations};

  size_t op_seq{};

  do {
    int result{static_cast<int>(num_str[0] - '0')};
    string current_operations_seq{};

    const string op_seq_bin_str{dec2bin(op_seq, true, max_operations)};
    unordered_map<char, int> op_seq_count{
        {'0', count(begin(op_seq_bin_str), end(op_seq_bin_str), '0')},
        {'1', count(begin(op_seq_bin_str), end(op_seq_bin_str), '1')}};

    for (size_t i{}; i < max_operations; i++) {
      if (op_seq & (1u << i)) {
        current_operations_seq.push_back('-');
        result -= static_cast<int>(num_str[i + 1] - '0');
        if (!result && current_operations_seq.length() == max_operations)
          return current_operations_seq;

      } else {
        current_operations_seq.push_back('+');
        result += static_cast<int>(num_str[i + 1] - '0');
        if (!result && current_operations_seq.length() == max_operations)
          return current_operations_seq;
      }

      op_seq_count[op_seq_bin_str[i]]--;
      if (result > 0 && 0 == op_seq_count['1'])
        break;
      else if (result < 0 && 0 == op_seq_count['0'])
        break;
    }

  } while (++op_seq < max_operations_limit);

  return "not possible";
}

int main() {
  // cout << PlusMinus_v2(gets(stdin));
  cout << PlusMinus_v2(35132) << '\n';  // expected output: "-++-"
  cout << PlusMinus_v2(199) << '\n';    // expected output: "not possible"
  cout << PlusMinus_v2(26712) << '\n';  // expected output: "-+--"

  return 0;
}
