/*
Coderbyte coding challenge: Look Say Sequence

Using the C++ language, have the function LookSaySequence(num) take the num
parameter being passed and return the next number in the sequence according to
the following rule: to generate the next number in a sequence read off the
digits of the given number, counting the number of digits in groups of the same
digit. For example, the sequence beginning with 1 would be: 1, 11, 21, 1211, ...
The 11 comes from there being "one 1" before it and the 21 comes from there
being "two 1's" before it. So your program should return the next number in the
sequence given num.

Sample test cases:

Input:  1211
Output: 111221

Input:  2466
Output: 121426
*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string LookSaySequence_v1(const int num) {
  string num_str{to_string(num)};

  ostringstream oss{};

  for (size_t i{}; i < num_str.length(); i++) {
    size_t count{1};

    while ((i < num_str.length() - 1) && (num_str[i] == num_str[i + 1])) {
      count++;
      i++;
    }

    oss << count << num_str[i];
  }

  return oss.str();
}

string LookSaySequence_v2(const int num) {
  string num_str{to_string(num)};

  ostringstream oss{};

  char prev_digit{num_str[0]};
  size_t start_pos{};

  while (true) {
    const size_t end_pos{num_str.find_first_not_of(prev_digit, start_pos)};

    if (string::npos == end_pos) {
      oss << num_str.length() - start_pos << prev_digit;
      break;
    }

    oss << end_pos - start_pos << prev_digit;
    prev_digit = num_str[end_pos];
    start_pos = end_pos;
  }

  return oss.str();
}

string LookSaySequence_v3(int num) {
  ostringstream oss{};

  int prev_digit{num % 10};
  num /= 10;
  size_t count{1};

  while (true) {
    const int current_digit{num % 10};
    num /= 10;

    if (current_digit == prev_digit)
      count++;

    else {
      oss << prev_digit << count;
      prev_digit = current_digit;
      count = 1;
    }

    if (!num) {
      oss << prev_digit << count;
      break;
    }
  }

  string result_num{oss.str()};
  reverse(begin(result_num), end(result_num));
  return result_num;
}

int main() {
  // cout << LookSaySequence_v2(gets(stdin));
  cout << LookSaySequence_v2(1211) << '\n';  // expected output: 111221
  cout << LookSaySequence_v2(2466) << '\n';  // expected output: 121426

  return 0;
}
