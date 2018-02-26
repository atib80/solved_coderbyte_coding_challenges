/*
Coderbyte coding challenge: Moving Median

Using the C++ language, have the function MovingMedian(arr) read the array of
numbers stored in arr which will contain a sliding window size, N, as the first
element in the array and the rest will be a list of numbers. Your program should
return the Moving Median for each element based on the element and its N-1
predecessors, where N is the sliding window size. The final output should be a
string with the moving median corresponding to each entry in the original array
separated by commas.

Note that for the first few elements (until the window size is reached), the
median is computed on a smaller number of entries. For example: if arr is [3, 1,
3, 5, 10, 6, 4, 3, 1] then your program should output "1,2,3,5,6,6,4,3"

Sample test cases:

Input:  5, 2, 4, 6
Output: "2,3,4"

Input:  3, 0, 0, -2, 0, 2, 0, -2
Output: "0,0,0,0,0,0,0"
*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string MovingMedian_v1(vector<long> numbers) {
  const size_t numbers_size{numbers.size()};

  const size_t window_size{static_cast<size_t>(numbers[0])};

  string answer{};

  for (size_t i{1}; i < numbers_size; i++) {
    vector<long> window{};

    for (size_t j{}; (j < window_size) && (j < i); j++) {
      window.emplace_back(numbers[i - j]);
    }

    sort(begin(window), end(window));

    const size_t ws{window.size()};

    if (ws % 2 == 1)
      answer += to_string(window[ws / 2]);
    else
      answer += to_string((window[ws / 2 - 1] + window[ws / 2]) / 2);

    if (i < numbers_size - 1)
      answer.push_back(',');
  }

  return answer;
}

string MovingMedian_v2(vector<long> numbers) {
  const size_t numbers_size{numbers.size()};

  const size_t max_window_size{static_cast<size_t>(numbers[0])};

  size_t cws{1};

  ostringstream oss{};

  for (size_t i{1}; i < numbers_size; i++) {
    vector<long> window{};

    for (size_t j{i + 1 - cws}; j < i + 1; j++) {
      window.emplace_back(numbers[j]);
    }

    sort(begin(window), end(window));

    if (cws % 2 == 1)
      oss << window[cws / 2];
    else
      oss << (window[cws / 2 - 1] + window[cws / 2]) / 2;

    if (i < numbers_size - 1)
      oss << ',';

    if (cws < max_window_size)
      cws++;
  }

  return oss.str();
}

int main() {
  // cout << MovingMedian_v2(move(vector<long>{gets(stdin)}));
  cout << MovingMedian_v2(move(vector<long>{3, 1, 3, 5, 10, 6, 4, 3, 1}))
       << '\n';  // expected output: "1,2,3,5,6,6,4,3"
  cout << MovingMedian_v2(move(vector<long>{5, 2, 4, 6}))
       << '\n';  // expected output: "2,3,4"
  cout << MovingMedian_v2(move(vector<long>{3, 0, 0, -2, 0, 2, 0, -2}))
       << '\n';  // expected output: "0,0,0,0,0,0,0"

  return 0;
}
