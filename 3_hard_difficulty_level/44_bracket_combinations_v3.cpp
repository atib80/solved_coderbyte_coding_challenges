/*
Coderbyte coding challenge: Bracket Combinations
(alternative iterative solution implemented by using queue)

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
#include <queue>
#include <utility>

using std::cout;
using std::make_pair;
using std::pair;
using std::queue;

size_t find_number_of_possible_combinations(const size_t number_of_pairs) {
  size_t combinations{};
  queue<pair<size_t, size_t>> q{{make_pair(0, 0)}};

  while (!q.empty()) {
    const size_t used_open_prnths{q.front().first};
    const size_t used_close_prnths{q.front().second};
    q.pop();

    if (number_of_pairs == used_close_prnths)
      combinations++;

    else {
      if (used_open_prnths < number_of_pairs)
        q.emplace(make_pair(used_open_prnths + 1, used_close_prnths));
      if (used_close_prnths < used_open_prnths)
        q.emplace(make_pair(used_open_prnths, used_close_prnths + 1));
    }
  }

  return combinations;
}

size_t BracketCombinations_v3(const size_t num) {
  return find_number_of_possible_combinations(num);
}

int main() {
  // cout << BracketCombinations_v3(gets(stdin));
  cout << BracketCombinations_v3(2) << '\n';   // expected output: 2
  cout << BracketCombinations_v3(3) << '\n';   // expected output: 5
  cout << BracketCombinations_v3(4) << '\n';   // expected output: 14
  cout << BracketCombinations_v3(5) << '\n';   // expected output: 42
  cout << BracketCombinations_v3(6) << '\n';   // expected output: 132
  cout << BracketCombinations_v3(7) << '\n';   // expected output: 429
  cout << BracketCombinations_v3(8) << '\n';   // expected output: 1430
  cout << BracketCombinations_v3(9) << '\n';   // expected output: 4862
  cout << BracketCombinations_v3(10) << '\n';  // expected output: 16796
  cout << BracketCombinations_v3(11) << '\n';  // expected output: 58786
  cout << BracketCombinations_v3(12) << '\n';  // expected output: 208012

  return 0;
}
