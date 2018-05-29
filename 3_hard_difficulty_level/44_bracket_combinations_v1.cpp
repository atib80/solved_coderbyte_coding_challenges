/*
Coderbyte coding challenge: Bracket Combinations
(simplified, terse recursive solution)

Using the C++ language, have the function BracketCombinations(num) read num
which will be an integer greater than or equal to zero, and return the number of
valid combinations that can be formed with num pairs of parentheses. For
example, if the input is 3, then the possible combinations of 3 pairs of
parenthesis, namely:
()()(), are ()()(), ()(()), (())(), ((())), and (()()).
There are 5 total combinations when the input is 3, so your program should
return 5.

Sample test cases:

Input:  3
Output: 5

Input:  2
Output: 2
*/

#include <iostream>

using std::cout;

size_t find_number_of_possible_combinations(
    const size_t number_of_pairs,
    const size_t used_open_prnths = 0,
    const size_t used_close_prnths = 0) {
  if (number_of_pairs == used_close_prnths)
    return 1;

  size_t combinations{};

  if (used_open_prnths < number_of_pairs)
    combinations += find_number_of_possible_combinations(
        number_of_pairs, used_open_prnths + 1, used_close_prnths);

  if (used_close_prnths < used_open_prnths)
    combinations += find_number_of_possible_combinations(
        number_of_pairs, used_open_prnths, used_close_prnths + 1);

  return combinations;
}

size_t BracketCombinations_v1(const size_t num) {
  const size_t combinations{find_number_of_possible_combinations(num, 0, 0)};

  return combinations;
}

int main() {
  // cout << BracketCombinations_v1(gets(stdin));
  cout << BracketCombinations_v1(2) << '\n';   // expected output: 2
  cout << BracketCombinations_v1(3) << '\n';   // expected output: 5
  cout << BracketCombinations_v1(4) << '\n';   // expected output: 14
  cout << BracketCombinations_v1(5) << '\n';   // expected output: 42
  cout << BracketCombinations_v1(6) << '\n';   // expected output: 132
  cout << BracketCombinations_v1(7) << '\n';   // expected output: 429
  cout << BracketCombinations_v1(8) << '\n';   // expected output: 1430
  cout << BracketCombinations_v1(9) << '\n';   // expected output: 4862
  cout << BracketCombinations_v1(10) << '\n';  // expected output: 16796
  cout << BracketCombinations_v1(11) << '\n';  // expected output: 58786
  cout << BracketCombinations_v1(12) << '\n';  // expected output: 208012

  return 0;
}
