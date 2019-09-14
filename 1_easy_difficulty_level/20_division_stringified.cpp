/*
Coderbyte coding challenge: Division Stringified

Using the C++ language, have the function DivisionStringified(num1,num2) take
both parameters being passed, divide num1 by num2, and return the result as a
string with properly formatted commas. If an answer is only 3 digits long,
return the number with no commas (ie. 2 / 3 should output "1"). For example: if
num1 is 123456789 and num2 is 10000 the output should be "12,346".

Sample test cases:

Input:  5 & num2 = 2
Output: "3"

Input:  6874 & num2 = 67
Output: "103"
*/

#include <cmath>
#include <cstdint>
#include <exception>
#include <iostream>
#include <string>

using namespace std;

string DivisionStringified(const int64_t numerator, const int64_t denumerator) {
  constexpr static size_t buffer_size{32U};
  char buffer[buffer_size];

  if (0 == denumerator)
    return "Not possible!";
  int64_t whole_part{static_cast<int64_t>(
      round(static_cast<double>(numerator) / denumerator))};

  const bool is_negative{whole_part < 0};
  if (is_negative)
    whole_part = abs(whole_part);

  size_t j{buffer_size - 1}, digit_count{1};
  buffer[j] = 0;

  while (true) {
    buffer[--j] = static_cast<char>('0' + whole_part % 10);
    whole_part /= 10;

    if (0 == whole_part)
      break;

    if (0U == digit_count % 3)
      buffer[--j] = ',';

    digit_count++;
  }

  if (is_negative)
    buffer[--j] = '-';

  return buffer + j;
}

int main() {
  try {
    // const vector<int64_t> numbers { gets(stdin) };
    // cout << DivisionStringified(numbers[0], numbers[1]);
    cout << DivisionStringified(1, 10) << '\n';    // expected output: "0"
    cout << DivisionStringified(5, 54) << '\n';    // expected output: "0"
    cout << DivisionStringified(175, 24) << '\n';  // expected output: "7"
    cout << DivisionStringified(101077282, 21123)
         << '\n';  // expected output: "4,785"
    cout << DivisionStringified(-101077282, 21123)
         << '\n';  // expected output: "-4,785"
    cout << DivisionStringified(101077282, -21123)
         << '\n';  // expected output: "-4,785"
    cout << DivisionStringified(-101077282, -21123)
         << '\n';  // expected output: "4,785"
    cout << DivisionStringified(100000, 1)
         << '\n';  // expected output: "100,000"
    cout << DivisionStringified(10000000, 10)
         << '\n';  // expected output: "1,000,000"
  } catch (exception& e) {
    cerr << "Exception occured in function int main(): " << e.what() << endl;
  }

  return 0;
}
