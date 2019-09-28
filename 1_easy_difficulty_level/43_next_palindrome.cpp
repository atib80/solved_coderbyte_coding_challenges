/*
Coderbyte coding challenge: Next Palindrome

Using the C++ language, have the function NextPalindrome(num) take the num
parameter being passed and return the next largest palindromic number. The input
can be any positive integer. For example: if num is 24, then your program should
return 33 because that is the next largest number that is a palindrome.

Sample test cases:

Input:  2
Output: 3

Input:  180
Output: 181
*/

#include <array>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

bool is_next_number_palindrome(const string& num_str) {
  for (size_t i{}, j{num_str.length() - 1}; i < j; ++i, --j) {
    if (num_str[i] != num_str[j])
      return false;
  }

  return true;
}

int NextPalindrome_v1(int num) {
  num = abs(num);

  if (num < 9)
    return num + 1;

  do {
    ++num;
  } while (!is_next_number_palindrome(to_string(num)));

  return num;
}

int NextPalindrome_v2(int num) {
  num = abs(num);

  if (num < 9)
    return num + 1;

  do {
    ++num;

    int original_num{num};
    int palindromic_num{};

    while (0 != original_num) {
      palindromic_num *= 10;
      palindromic_num += original_num % 10;
      original_num /= 10;
    }

    if (num == palindromic_num)
      return num;

  } while (true);
}

int NextPalindrome_v3(int num) {
  num = abs(num);

  if (num < 9)
    return num + 1;

  array<int, 10U> next_num_digits{};

  do {
    ++num;
    int next_num{num};
    size_t last{};

    while (0 != next_num) {
      next_num_digits[last++] = next_num % 10;
      next_num /= 10;
    }

    for (size_t i{}, j{last - 1}; i < j; ++i, --j) {
      if (next_num_digits[i] != next_num_digits[j]) {
        next_num = -1;
        break;
      }
    }

    if (0 == next_num)
      return num;

  } while (true);
}

int main() {
  // cout << NextPalindrome_v3(gets(stdin));
  cout << NextPalindrome_v3(24) << '\n';   // expected output: 33
  cout << NextPalindrome_v3(2) << '\n';    // expected output: 3
  cout << NextPalindrome_v3(180) << '\n';  // expected output: 181

  return 0;
}
