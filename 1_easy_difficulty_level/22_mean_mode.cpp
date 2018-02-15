/*
Coderbyte coding challenge: Mean Mode

Using the C++ language, have the function MeanMode(arr) take the array of
numbers stored in arr and return 1 if the mode equals the mean, 0 if they don't
equal each other (ie. [5, 3, 3, 3, 1] should return 1 because the mode (3)
equals the mean (3)). The array will not be empty, will only contain positive
integers, and will not contain more than one mode.

Sample test cases:

Input:  1, 2, 3
Output: 0

Input:  4, 4, 4, 6, 2
Output: 1
*/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

using namespace std;

int MeanMode(vector<int> numbers) {
  sort(begin(numbers), end(numbers));

  const int sum{accumulate(begin(numbers), end(numbers), 0)};

  const int mean = sum / numbers.size();

  unordered_map<int, size_t> number_frequency{};

  for (const int n : numbers)
    number_frequency[n]++;

  vector<pair<int, size_t>> number_frequency_sorted{};

  for (const auto& nf : number_frequency)
    number_frequency_sorted.emplace_back(nf);

  sort(begin(number_frequency_sorted), end(number_frequency_sorted),
       [](const pair<int, size_t>& l, const pair<int, size_t>& r) {
         return (l.second > r.second);
       });

  if (mean == number_frequency_sorted[0].first)
    return 1;

  return 0;
}

int main() {
  // cout << MeanMode(move(vector<int>{gets(stdin)}));
  cout << MeanMode(move(vector<int>{5, 3, 3, 3, 1}))
       << '\n';                                          // expected output: 1
  cout << MeanMode(move(vector<int>{1, 2, 3})) << '\n';  // expected output: 0
  cout << MeanMode(move(vector<int>{4, 4, 4, 6, 2}))
       << '\n';                                         // expected output: 1
  cout << MeanMode(move(vector<int>{10, 10})) << '\n';  // expected output: 1
  cout << MeanMode(move(vector<int>{1, 1, 1, 1, 1}))
       << '\n';  // expected output: 1
  cout << MeanMode(move(vector<int>{10, 10, 10, 10, 10, 10, 10, 20, 9, 1}))
       << '\n';  // expected output: 1

  return 0;
}
