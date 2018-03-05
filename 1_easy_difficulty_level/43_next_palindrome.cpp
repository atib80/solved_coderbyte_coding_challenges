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

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

bool is_next_number_palindrome(const string& num_str) {
  string reversed_num_str{num_str};

  reverse(begin(reversed_num_str), end(reversed_num_str));

  if (num_str == reversed_num_str)
    return true;

  return false;
}

int NextPalindrome_v1(int num) {
  num = abs(num);

  if (num < 9)
    return num + 1;

  string num_str{};

  do {
    num++;

    num_str = to_string(num);
  } while (!is_next_number_palindrome(num_str));

  return num;
}

int NextPalindrome_v2(int num) {
  num = abs(num);

  if (num < 9)
    return num + 1;

  do {
    num++;

    int original_num{num};
    int palindromic_num{};

    while (original_num) {
      palindromic_num *= 10;
      palindromic_num += original_num % 10;
      original_num /= 10;
    }

    if (num == palindromic_num)
      return num;

  } while (true);
}

int main() {
  // cout << NextPalindrome_v2(gets(stdin));
  cout << NextPalindrome_v2(24) << '\n';   // expected output: 33
  cout << NextPalindrome_v2(2) << '\n';    // expected output: 3
  cout << NextPalindrome_v2(180) << '\n';  // expected output: 181

  return 0;
}
