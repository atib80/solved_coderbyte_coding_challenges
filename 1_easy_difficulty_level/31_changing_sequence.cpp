/*
Coderbyte coding challenge: Changing Sequence

Using the C++ language, have the function ChangingSequence(arr) take the array
of numbers stored in arr and return the index at which the numbers stop
increasing and begin decreasing or stop decreasing and begin increasing. For
example: if arr is [1, 2, 4, 6, 4, 3, 1] then your program should return 3
because 6 is the last point in the array where the numbers were increasing and
the next number begins a decreasing sequence. The array will contain at least 3
numbers and it may contain only a single sequence, increasing or decreasing. If
there is only a single sequence in the array, then your program should return
-1. Indexing should begin with 0.

Sample test cases:

Input:  -4, -2, 9, 10
Output: -1

Input:  5, 4, 3, 2, 10, 11
Output: 3
*/

#include <iostream>
#include <vector>

using namespace std;

int ChangingSequence_v1(vector<int> numbers) {
  if (numbers.size() < 3U)
    return -1;
  const size_t numbers_size{numbers.size()};
  size_t si{1};

  for (; si < numbers_size; si++) {
    if (numbers[0] != numbers[si])
      break;
  }

  const bool ascending_order{numbers[0] < numbers[si]};

  for (size_t i{si}; i < numbers.size(); ++i) {
    if (ascending_order) {
      if (numbers[i] < numbers[i - 1])
        return i - 1;
    }

    if (!ascending_order) {
      if (numbers[i] > numbers[i - 1])
        return i - 1;
    }
  }

  return -1;
}

int ChangingSequence_v2(vector<int> numbers) {
  if (numbers.size() < 3U)
    return -1;
  const size_t numbers_size{numbers.size()};

  for (size_t i{1}; i < numbers_size - 1; ++i) {
    if (numbers[i] > numbers[i - 1] && numbers[i] > numbers[i + 1])
      return i;

    if (numbers[i] < numbers[i - 1] && numbers[i] < numbers[i + 1])
      return i;
  }

  return -1;
}

int main() {
  // cout << ChangingSequence_v2(gets(stdin));
  cout << ChangingSequence_v2({1, 2, 4, 6, 4, 3, 1})
       << '\n';                                          // expected output: 3
  cout << ChangingSequence_v2({-4, -2, 9, 10}) << '\n';  // expected output: -1
  cout << ChangingSequence_v2({5, 4, 3, 2, 10, 11})
       << '\n';  // expected output: 3

  return 0;
}
