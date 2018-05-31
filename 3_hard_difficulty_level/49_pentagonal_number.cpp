/*
Coderbyte coding challenge: Pentagonal Number

Using the C++ language, have the function PentagonalNumber(num) read num which
will be a positive integer and determine how many dots exist in a pentagonal
shape around a center dot on the Nth iteration. For example, in the image below
you can see that on the first iteration there is only a single dot, on the
second iteration there are 6 dots, on the third there are 16 dots, and on the
fourth there are 31 dots.

Your program should return the number of dots that exist in the whole pentagon
on the Nth iteration.

Sample test cases:

Input:  2
Output: 6

Input:  5
Output: 51
*/

#include <iostream>
#include <map>

using namespace std;

size_t pentagonal_number(const size_t number_of_iterations) {
  static map<size_t, size_t> precalculated_pentagonal_numbers{
      {1, 1}, {2, 6}, {3, 16}};

  if (end(precalculated_pentagonal_numbers) !=
      precalculated_pentagonal_numbers.find(number_of_iterations))
    return precalculated_pentagonal_numbers.at(number_of_iterations);

  auto lb_iter =
      precalculated_pentagonal_numbers.upper_bound(number_of_iterations);

  if (lb_iter != end(precalculated_pentagonal_numbers) &&
      lb_iter != begin(precalculated_pentagonal_numbers))
    --lb_iter;

  size_t number_of_dots{
      lb_iter != end(precalculated_pentagonal_numbers) ? lb_iter->second : 1};
  size_t current_level_dots{lb_iter != end(precalculated_pentagonal_numbers)
                                ? lb_iter->first * 5
                                : 5};
  size_t i{lb_iter != end(precalculated_pentagonal_numbers) ? lb_iter->first + 1
                                                            : 2};

  for (; i <= number_of_iterations; i++) {
    number_of_dots += current_level_dots;
    current_level_dots += 5;
  }

  precalculated_pentagonal_numbers[number_of_iterations] = number_of_dots;

  return number_of_dots;
}

int main() {
  // cout << pentagonal_number(gets(stdin));
  cout << pentagonal_number(1) << '\n';  // expected output: 1
  cout << pentagonal_number(2) << '\n';  // expected output: 6
  cout << pentagonal_number(3) << '\n';  // expected output: 16
  cout << pentagonal_number(4) << '\n';  // expected output: 31
  cout << pentagonal_number(5) << '\n';  // expected output: 51
  cout << pentagonal_number(6) << '\n';  // expected output: 76
  cout << pentagonal_number(7) << '\n';  // expected output: 106
  cout << pentagonal_number(8) << '\n';  // expected output: 141

  return 0;
}
