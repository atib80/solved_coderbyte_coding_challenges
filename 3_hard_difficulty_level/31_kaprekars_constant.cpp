/*
Coderbyte coding challenge: Kaprekars Constant

Using the C++ language, have the function KaprekarsConstant(num) take the num
parameter being passed which will be a 4-digit number with at least two distinct
digits. Your program should perform the following routine on the number: Arrange
the digits in descending order and in ascending order (adding zeroes to fit it
to a 4-digit number), and subtract the smaller number from the bigger number.
Then repeat the previous step. Performing this routine will always cause you to
reach a fixed number: 6174. Then performing the routine on 6174 will always give
you 6174 (7641 - 1467 = 6174). Your program should return the number of times
this routine must be performed until 6174 is reached. For example: if num is
3524 your program should return 3 because of the following steps: (1) 5432 -
2345 = 3087, (2) 8730 - 0378 = 8352, (3) 8532 - 2358 = 6174.

Sample test cases:

Input:  2111
Output: 5

Input:  9831
Output: 7
*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

size_t KaprekarsConstant(int num) {
  size_t iter_count{};

  while (num != 6174) {
    string number_str{to_string(num)};
    const size_t number_str_len{number_str.length()};

    if (number_str_len < 4) {
      number_str.insert(begin(number_str), 4 - number_str_len, '0');
    }

    sort(begin(number_str), end(number_str),
         [](const char lc, const char rc) { return lc > rc; });

    const int lhs_num{stoi(number_str)};
    reverse(begin(number_str), end(number_str));
    const int rhs_num{stoi(number_str)};
    num = lhs_num - rhs_num;
    iter_count++;
  }

  return iter_count;
}

int main() {
  // cout << KaprekarsConstant(gets(stdin));
  cout << KaprekarsConstant(3524) << '\n';  // expected output: 3
  cout << KaprekarsConstant(2111) << '\n';  // expected output: 5
  cout << KaprekarsConstant(9831) << '\n';  // expected output: 7

  return 0;
}
