/*
Coderbyte coding challenge: Even Pairs

Using the C++ language, have the function EvenPairs(str) take the str parameter
being passed and determine if a pair of adjacent even numbers exists anywhere in
the string. If a pair exists, return the string true, otherwise return false.
For example: if str is "f178svg3k19k46" then there are two even numbers at the
end of the string, "46" so your program should return the string true. Another
example: if str is "7r5gg812" then the pair is "812" (8 and 12) so your program
should return the string true.

Sample test cases:

Input:  "3gy41d216"
Output: "true"

Input:  "f09r27i8e67"
Output: "false"
*/

#include <cctype>
#include <iostream>
#include <string>

using namespace std;

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (!str_len)
    return string{};

  size_t first{}, last{str_len - 1};

  for (; first <= last; ++first) {
    if (!isspace(str[first]))
      break;
  }

  if (first > last)
    return string{};

  for (; last > first; --last) {
    if (!isspace(str[last]))
      break;
  }

  return str.substr(first, last - first + 1);
}

bool check_if_num_str_consists_of_two_even_numbers(const string& num_str) {
  size_t num1_ei{};

  for (; num1_ei < num_str.length(); num1_ei++) {
    if (num_str[num1_ei] % 2 == 0)
      break;
  }

  if (num1_ei >= num_str.length() - 1)
    return false;

  if (num_str[num_str.length() - 1] % 2 == 1)
    return false;

  return true;
}

string EvenPairs(string str) {
  str = trim(str);

  if (str.length() < 2)
    return "false";

  size_t start{};

  while (true) {
    start = str.find_first_of("123456789", start);

    if (string::npos == start)
      return "false";

    const size_t last{str.find_first_not_of("0123456789", start + 1)};

    if (string::npos == last) {
      const string num_str{str.substr(start)};

      if (check_if_num_str_consists_of_two_even_numbers(num_str))
        return "true";

      return "false";
    }
    const string num_str{str.substr(start, last - start)};

    if (check_if_num_str_consists_of_two_even_numbers(num_str))
      return "true";

    start = last;
  }
}

int main() {
  // cout << EvenPairs(move(string{gets(stdin)}));
  cout << EvenPairs(move(string{"f178svg3k19k46"}))
       << '\n';  // expected output: "true"
  cout << EvenPairs(move(string{"7r5gg812"}))
       << '\n';  // expected output: "true"
  cout << EvenPairs(move(string{"3gy41d216"}))
       << '\n';  // expected output: "true"
  cout << EvenPairs(move(string{"f09r27i8e67"}))
       << '\n';  // expected output: "false"

  return 0;
}
