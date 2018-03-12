/*
Coderbyte coding challenge: Formatted Division

Using the C++ language, have the function FormattedDivision(num1,num2) take both
parameters being passed, divide num1 by num2, and return the result as a string
with properly formatted commas and 4 significant digits after the decimal place.
For example: if num1 is 123456789 and num2 is 10000 the output should be
"12,345.6789". The output must contain a number in the one's place even if it is
a zero.

Sample test cases:

Input:  2 & num2 = 3
Output: "0.6667"

Input:  10 & num2 = 10
Output: "1.0000"
*/

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string FormattedDivision(const long num1, const long num2) {
  if (!num2)
    return !num1 ? "NaN" : num1 < 0 ? "-Inf" : "+Inf";

  if (!num1)
    return "0.0000";

  const double result{static_cast<double>(num1) / num2};
  // char buffer[32];
  // sprintf(buffer, "%.4lf", result);

  ostringstream oss1{};
  oss1 << fixed << setprecision(4) << result;

  string result_str{oss1.str()};

  size_t start{result_str.find('.')};

  if (string::npos == start)
    start = result_str.length();

  int number_of_commas = start / 3;

  int leading_no_of_ch = start % 3;

  if (!leading_no_of_ch) {
    number_of_commas--;
    leading_no_of_ch = 3;
  }

  ostringstream oss2{};

  oss2 << result_str.substr(0, leading_no_of_ch);

  int j{leading_no_of_ch};

  while (number_of_commas > 0) {
    oss2 << ',' << result_str.substr(j, 3);
    j += 3;
    number_of_commas--;
  }

  if (start < result_str.length())
    oss2 << result_str.substr(start);

  return oss2.str();
}

int main() {
  // cout << FormattedDivision(gets(stdin));
  cout << FormattedDivision(123456789, 10000)
       << '\n';                               // expected output: 12,345.6789
  cout << FormattedDivision(2, 3) << '\n';    // expected output: 0.6667
  cout << FormattedDivision(10, 10) << '\n';  // expected output: 1.0000

  return 0;
}
