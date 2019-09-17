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

int MeanMode_v1(vector<int> numbers) {
  if (numbers.size() < 2U)
    return -1;

  const int mean = accumulate(begin(numbers), end(numbers), 0) / numbers.size();

  unordered_map<int, size_t> number_frequency{};

  int max_frequency_number{numbers.front()};
  size_t max_frequency{1U};

  for (const int n : numbers) {
    number_frequency[n]++;
    if (number_frequency[n] > max_frequency) {
      max_frequency = number_frequency[n];
      max_frequency_number = n;
    }
  }

  return mean == max_frequency_number ? 1 : 0;
}

int main() {
  // cout << MeanMode_v1(vector<int>{gets(stdin)});
  cout << MeanMode_v1({5, 3, 3, 3, 1}) << '\n';  // expected output: 1
  cout << MeanMode_v1({1, 2, 3}) << '\n';        // expected output: 0
  cout << MeanMode_v1({4, 4, 4, 6, 2}) << '\n';  // expected output: 1
  cout << MeanMode_v1({10, 10}) << '\n';         // expected output: 1
  cout << MeanMode_v1({1, 1, 1, 1, 1}) << '\n';  // expected output: 1
  cout << MeanMode_v1({10, 10, 10, 10, 10, 10, 10, 20, 9, 1})
       << '\n';  // expected output: 1

  return 0;
}
