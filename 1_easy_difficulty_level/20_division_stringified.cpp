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
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string DivisionStringified(const vector<int64_t>& numbers) {
  
  const int64_t num1{numbers[0]};
  const int64_t num2{numbers[1]};
  if (0 == num2)
    return "Not possible!";
  const double result{static_cast<double>(num1) / static_cast<double>(num2)};
  const int64_t whole_part{static_cast<int64_t>(round(result))};
  string whole_part_str{to_string(whole_part)};
  if (whole_part_str.length() <= 3)
    return whole_part_str;

  for (int i = whole_part_str.length() - 3; i > 0; i -= 3)
    whole_part_str.insert(i, 1, ',');

  return whole_part_str;
}

int main() {
  // const vector<long> numbers { gets(stdin) };
  // cout << DivisionStringified(numbers);
  cout << DivisionStringified({1, 10}) << '\n';    // expected output: "0"
  cout << DivisionStringified({5, 54}) << '\n';    // expected output: "0"
  cout << DivisionStringified({175, 24}) << '\n';  // expected output: "7"
  cout << DivisionStringified({101077282, 21123})
       << '\n';  // expected output: "4,785"
  cout << DivisionStringified({100000, 1})
       << '\n';  // expected output: "100,000"
  cout << DivisionStringified({10000000, 10})
       << '\n';  // expected output: "1,000,000"

  return 0;
}
