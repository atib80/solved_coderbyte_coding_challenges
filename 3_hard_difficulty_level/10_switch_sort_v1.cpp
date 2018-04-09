/*
Coderbyte coding challenge: Switch Sort v1

(recursive solution)

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
#include <vector>

using namespace std;

void find_min_number_of_iterations(vector<int>& numbers,
                                   const int numbers_size,
                                   const int si,
                                   size_t& min_number_of_iterations,
                                   const size_t iter = 0) {
  if (iter + 1 >= min_number_of_iterations)
    return;

  for (int i{si}; i <= numbers_size; i++) {
    if (i == numbers[i - 1])
      continue;

    for (int j{1}; j < numbers_size; j++) {
      const int li{i - j <= 0 ? numbers_size - (j - i) : i - j};

      if (li != numbers[li - 1]) {
        swap(numbers[i - 1], numbers[li - 1]);

        if (is_sorted(begin(numbers), end(numbers))) {
          if (iter + 1 < min_number_of_iterations)
            min_number_of_iterations = iter + 1;

          swap(numbers[i - 1], numbers[li - 1]);
          return;
        }

        find_min_number_of_iterations(numbers, numbers.size(), i + 1,
                                      min_number_of_iterations, iter + 1);

        swap(numbers[i - 1], numbers[li - 1]);
      }

      const int ri{(i + j) > numbers_size ? i + j - numbers_size : i + j};

      if (ri != numbers[ri - 1]) {
        swap(numbers[i - 1], numbers[ri - 1]);

        if (is_sorted(begin(numbers), end(numbers))) {
          if (iter + 1 < min_number_of_iterations)
            min_number_of_iterations = iter + 1;

          swap(numbers[i - 1], numbers[ri - 1]);
          return;
        }

        find_min_number_of_iterations(numbers, numbers.size(), i + 1,
                                      min_number_of_iterations, iter + 1);

        swap(numbers[i - 1], numbers[ri - 1]);
      }
    }
  }
}

int SwitchSort_v1(const int* arr, const int arr_size) {
  vector<int> numbers(arr, arr + arr_size);

  if (is_sorted(begin(numbers), end(numbers))) {
    return 0;
  }

  size_t min_number_of_iterations{string::npos};

  find_min_number_of_iterations(numbers, numbers.size(), 1,
                                min_number_of_iterations);

  if (string::npos != min_number_of_iterations)
    return static_cast<int>(min_number_of_iterations);

  return -1;
}

int main() {
  // int A[] = gets(stdin);
  // cout << SwitchSort_v1(A, sizeof(A)/sizeof(*A));
  const int B[] = {1, 3, 4, 2};
  cout << SwitchSort_v1(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 2
  const int C[] = {3, 1, 2};
  cout << SwitchSort_v1(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 2
  const int D[] = {1, 3, 4, 2};
  cout << SwitchSort_v1(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 2
  const int E[] = {3, 4, 2, 1};
  cout << SwitchSort_v1(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: 3
  const int F[] = {4, 3, 2, 1};
  cout << SwitchSort_v1(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: 2
  const int G[] = {3, 4, 2, 1};
  cout << SwitchSort_v1(G, sizeof(G) / sizeof(*G))
       << '\n';  // expected output: 3
  const int H[] = {4, 3, 2, 1};
  cout << SwitchSort_v1(H, sizeof(H) / sizeof(*H))
       << '\n';  // expected output: 2
  const int I[] = {5, 4, 3, 2, 1};
  cout << SwitchSort_v1(I, sizeof(I) / sizeof(*I))
       << '\n';  // expected output: 2
  const int J[] = {5, 3, 4, 1, 2};
  cout << SwitchSort_v1(J, sizeof(J) / sizeof(*J))
       << '\n';  // expected output: 4
  const int K[] = {5, 4, 3, 1, 2};
  cout << SwitchSort_v1(K, sizeof(K) / sizeof(*K))
       << '\n';  // expected output: 3

  return 0;
}
