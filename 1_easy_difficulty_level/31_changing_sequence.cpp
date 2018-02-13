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
#include <string>
#include <vector>

using namespace std;

int ChangingSequence(vector<int> numbers) {
  size_t si{1u};

  for (; si != numbers.size(); si++) {
    if (numbers[0] != numbers[si])
      break;
  }

  const bool ascending_order{numbers[0] < numbers[si]};

  for (size_t i{si}; i != numbers.size(); i++) {
    if (ascending_order && (numbers[i - 1] > numbers[i]))
      return (i - 1);

    if (!ascending_order && (numbers[i - 1] < numbers[i]))
      return (i - 1);
  }

  return -1;
}

int main() {
  // cout << ChangingSequence(move(vector<int>{gets(stdin)}));
  cout << ChangingSequence(move(vector<int>{1, 2, 4, 6, 4, 3, 1}))
       << '\n';  // expected output: 3
  cout << ChangingSequence(move(vector<int>{-4, -2, 9, 10}))
       << '\n';  // expected output: -1
  cout << ChangingSequence(move(vector<int>{5, 4, 3, 2, 10, 11}))
       << '\n';  // expected output: 3
       
  return 0;
}
