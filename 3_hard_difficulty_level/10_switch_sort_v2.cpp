/*
Coderbyte coding challenge: Switch Sort

Using the C++ language, have the function SwitchSort(arr) take arr which will be
an an array consisting of integers 1...size(arr) and determine what the fewest
number of steps is in order to sort the array from least to greatest using the
following technique: Each element E in the array can swap places with another
element that is arr[E] spaces to the left or right of the chosen element. You
can loop from one end of the array to the other. For example: if arr is the
array [1, 3, 4, 2] then you can choose the second element which is the number 3,
and if you count 3 places to the left you'll loop around the array and end up at
the number 4. Then you swap these elements and arr is then [1, 4, 3, 2]. From
here only one more step is required, you choose the last element which is the
number 2, count 2 places to the left and you'll reach the number 4, then you
swap these elements and you end up with a sorted array [1, 2, 3, 4]. Your
program should return an integer that specifies the least amount of steps needed
in order to sort the array using the following switch sort technique.

The array arr will at most contain five elements and will contain at least two
elements.

Sample test cases:

Input:  3,1,2
Output: 2

Input:  1,3,4,2
Output: 2
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int SwitchSort(const size_t* arr, const size_t arr_size) {
  vector<size_t> numbers(arr, arr + arr_size);

  if (is_sorted(begin(numbers), end(numbers)))
    return 0;

  vector<size_t> numbers_reversed{numbers};
  reverse(begin(numbers_reversed), end(numbers_reversed));
  if (is_sorted(begin(numbers_reversed), end(numbers_reversed)))
    return arr_size / 2;

  vector<pair<size_t, size_t>> indices{};
  // indices = { (0,1), (0,2), (0,N-1) ... (N-2,N-2), (N-2,N-1) }

  for (size_t i{}; i < arr_size - 1; i++) {
    for (size_t j{i + 1}; j < arr_size; j++)
      indices.emplace_back(make_pair(i, j));
  }

  sort(begin(indices), end(indices));

  size_t min_number_of_iterations{string::npos};

  do {
    size_t iter{};

    for (const pair<size_t, size_t>& pi : indices) {
      if (pi.first + 1 == numbers[pi.first])
        continue;
      if (pi.second + 1 == numbers[pi.second])
        continue;
      swap(numbers[pi.first], numbers[pi.second]);
      iter++;
      if (iter >= min_number_of_iterations)
        break;

      if (is_sorted(begin(numbers), end(numbers))) {
        min_number_of_iterations = iter;
        break;
      }
    }

    numbers.assign(arr, arr + arr_size);
  } while (next_permutation(begin(indices), end(indices)));

  if (string::npos != min_number_of_iterations)
    return min_number_of_iterations;

  return -1;
}

int main() {
  // const size_t A[] = gets(stdin);
  // cout << SwitchSort(A, sizeof(A)/sizeof(*A));
  const size_t B[] = {1, 3, 4, 2};
  cout << SwitchSort(B, sizeof(B) / sizeof(*B)) << '\n';  // expected output: 2
  const size_t C[] = {3, 1, 2};
  cout << SwitchSort(C, sizeof(C) / sizeof(*C)) << '\n';  // expected output: 2
  const size_t D[] = {1, 3, 4, 2};
  cout << SwitchSort(D, sizeof(D) / sizeof(*D)) << '\n';  // expected output: 2
  const size_t E[] = {3, 4, 2, 1};
  cout << SwitchSort(E, sizeof(E) / sizeof(*E)) << '\n';  // expected output: 3
  const size_t F[] = {4, 3, 2, 1};
  cout << SwitchSort(F, sizeof(F) / sizeof(*F)) << '\n';  // expected output: 2
  const size_t G[] = {3, 4, 2, 1};
  cout << SwitchSort(G, sizeof(G) / sizeof(*G)) << '\n';  // expected output: 3
  const size_t H[] = {4, 3, 2, 1};
  cout << SwitchSort(H, sizeof(H) / sizeof(*H)) << '\n';  // expected output: 2
  const size_t I[] = {5, 4, 3, 2, 1};
  cout << SwitchSort(I, sizeof(I) / sizeof(*I)) << '\n';  // expected output: 2
  const size_t J[] = {5, 3, 4, 1, 2};
  cout << SwitchSort(J, sizeof(J) / sizeof(*J)) << '\n';  // expected output: 4
  const size_t K[] = {5, 4, 3, 1, 2};
  cout << SwitchSort(K, sizeof(K) / sizeof(*K)) << '\n';  // expected output: 3

  return 0;
}
