/*
Coderbyte coding challenge: Superincreasing

Using the C++ language, have the function Superincreasing(arr) take the array of
numbers stored in arr and determine if the array forms a superincreasing
sequence where each element in the array is greater than the sum of all previous
elements. The array will only consist of positive integers. For example: if arr
is [1, 3, 6, 13, 54] then your program should return the string "true" because
it forms a superincreasing sequence. If a superincreasing sequence isn't formed,
then your program should return the string "false".

Sample test cases:

Input:  1,2,3,4
Output: "false"

Input:  1,2,5,10
Output: "true"
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

string Superincreasing(vector<int64_t> numbers) {
  if (numbers.empty())
    return "not possible";

  int64_t prev_sum{numbers.front()};

  for (size_t i{1}; i < numbers.size(); ++i) {
    if (numbers[i] <= prev_sum)
      return "false";

    prev_sum += numbers[i];
  }

  return "true";
}

int main() {
  // cout << Superincreasing(gets(stdin));
  cout << Superincreasing({1, 3, 6, 13, 54})
       << '\n';                                    // expected output: "true"
  cout << Superincreasing({1, 2, 3, 4}) << '\n';   // expected output: "false"
  cout << Superincreasing({1, 2, 5, 10}) << '\n';  // expected output: "true"

  return 0;
}
