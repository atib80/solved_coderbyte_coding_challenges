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

int NextPalindrome(int num) {
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

int main() {
  // cout << NextPalindrome(gets(stdin));
  cout << NextPalindrome(24) << '\n';   // expected output: 33
  cout << NextPalindrome(2) << '\n';    // expected output: 3
  cout << NextPalindrome(180) << '\n';  // expected output: 181

  return 0;
}
