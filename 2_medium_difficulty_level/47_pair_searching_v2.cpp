/*
Coderbyte coding challenge: Pair Searching v2

(iterative solution using std::queue<T>)

Using the C++ language, have the function PairSearching(num) take the num
parameter being passed and perform the following steps. First take all the
single digits of the input number (which will always be a positive integer
greater than 1) and add each of them into a list. Then take the input number and
multiply it by any one of its own integers, then take this new number and append
each of the digits onto the original list. Continue this process until an
adjacent pair of the same number appears in the list. Your program should return
the least number of multiplications it took to find an adjacent pair of
duplicate numbers.

For example: if num is 134 then first append each of the integers into a list:
[1, 3, 4]. Now if we take 134 and multiply it by 3 (which is one of its own
integers), we get 402. Now if we append each of these new integers to the list,
we get: [1, 3, 4, 4, 0, 2]. We found an adjacent pair of duplicate numbers,
namely 4 and 4. So for this input your program should return 1 because it only
took 1 multiplication to find this pair.

Another example: if num is 46 then we append these integers onto a list: [4, 6].
If we multiply 46 by 6, we get 276, and appending these integers onto the list
we now have: [4, 6, 2, 7, 6]. Then if we take this new number, 276, and multiply
it by 2 we get 552. Appending these integers onto the list we get: [4, 6, 2, 7,
6, 5, 5, 2]. Your program should therefore return 2 because it took 2
multiplications to find a pair of adjacent duplicate numbers (5 and 5 in this
case).

Sample test cases:

Input:  8
Output: 3

Input:  198
Output: 2
*/

#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

int PairSearching_v2(const int num) {
  size_t min_number_of_iterations{string::npos};

  queue<tuple<int, int, size_t>> q{{make_tuple(-1, num, 0)}};

  while (!q.empty()) {
    int prev_num, next_num;
    size_t iter_count;

    tie(prev_num, next_num, iter_count) = q.front();
    q.pop();

    const string next_num_str{to_string(next_num)};

    if (-1 != prev_num) {
      if ((prev_num % 10) + '0' == next_num_str[0]) {
        if (iter_count < min_number_of_iterations)
          min_number_of_iterations = iter_count;
        continue;
      }
    }

    vector<int> digits{};

    int prev_digit{-1};

    for (const char c : next_num_str) {
      const int digit{static_cast<int>(c - '0')};

      if (digit == prev_digit) {
        if (iter_count < min_number_of_iterations)
          min_number_of_iterations = iter_count;
        continue;
      }

      prev_digit = digit;

      digits.emplace_back(digit);
    }

    if (iter_count + 1 >= min_number_of_iterations)
      continue;

    for (size_t i{}; i < digits.size(); i++) {
      const int temp_num{next_num * digits[i]};

      if (temp_num == next_num)
        continue;

      const string temp_num_str{to_string(temp_num)};

      if (next_num_str.back() == temp_num_str[0]) {
        if (iter_count + 1 < min_number_of_iterations)
          min_number_of_iterations = iter_count + 1;
        break;
      }

      prev_digit = -1;

      for (const char c : temp_num_str) {
        const int digit{static_cast<int>(c - '0')};

        if (digit == prev_digit) {
          if (iter_count + 1 < min_number_of_iterations)
            min_number_of_iterations = iter_count + 1;
          break;
        }

        prev_digit = digit;
      }

      q.emplace(make_tuple(next_num, temp_num, iter_count + 1));
    }
  }

  return min_number_of_iterations;
}

int main() {
  // cout << PairSearching_v1(gets(stdin));
  cout << PairSearching_v2(134) << '\n';  // expected output: 1
  cout << PairSearching_v2(46) << '\n';   // expected output: 2
  cout << PairSearching_v2(8) << '\n';    // expected output: 3
  cout << PairSearching_v2(198) << '\n';  // expected output: 2

  return 0;
}