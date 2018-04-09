/*
Coderbyte coding challenge: Switch Sort v2

(iterative solution implemented by using queue)

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
#include <limits>
#include <queue>
#include <sstream>
#include <tuple>
#include <unordered_set>
#include <vector>

using namespace std;

int find_min_number_of_iterations(vector<int> numbers) {
  int min_number_of_iterations{numeric_limits<int>::max()};
  const int numbers_size = numbers.size();
  queue<tuple<int, int, vector<int>>> q{{make_tuple(1, 0, move(numbers))}};

  unordered_set<string> previously_visited{};

  while (!q.empty()) {
    const int si{get<0>(q.front())};
    const int iter{get<1>(q.front())};
    vector<int> numbers_next{move(get<2>(q.front()))};
    q.pop();

    if (iter + 1 >= min_number_of_iterations) {
      continue;
    }

    for (int i{si}; i <= numbers_size; i++) {
      if (i == numbers_next[i - 1]) {
        continue;
      }

      for (int j{1}; j < numbers_size; j++) {
        const int li{i - j <= 0 ? numbers_size - (j - i) : i - j};

        if (li != numbers_next[li - 1]) {
          swap(numbers_next[i - 1], numbers_next[li - 1]);
          if (is_sorted(begin(numbers_next), end(numbers_next))) {
            if (iter + 1 < min_number_of_iterations) {
              min_number_of_iterations = iter + 1;
            }
            swap(numbers_next[i - 1], numbers_next[li - 1]);
          }

          ostringstream oss{};
          oss << i + 1 << iter + 1;
          for (const auto n : numbers_next) {
            oss << n;
          }

          if (previously_visited.find(oss.str()) == end(previously_visited)) {
            q.emplace(make_tuple(i + 1, iter + 1, numbers_next));
            previously_visited.insert(oss.str());
          }

          swap(numbers_next[i - 1], numbers_next[li - 1]);
        }

        const int ri{i + j > numbers_size ? i + j - numbers_size : i + j};

        if (ri != numbers_next[ri - 1]) {
          swap(numbers_next[i - 1], numbers_next[ri - 1]);
          if (is_sorted(begin(numbers_next), end(numbers_next))) {
            if (iter + 1 < min_number_of_iterations) {
              min_number_of_iterations = iter + 1;
            }
            swap(numbers_next[i - 1], numbers_next[ri - 1]);
          }

          ostringstream oss{};
          oss << i + 1 << iter + 1;
          for (const auto n : numbers_next) {
            oss << n;
          }

          if (previously_visited.find(oss.str()) == end(previously_visited)) {
            q.emplace(make_tuple(i + 1, iter + 1, numbers_next));
            previously_visited.insert(oss.str());
          }

          swap(numbers_next[i - 1], numbers_next[ri - 1]);
        }
      }
    }
  }

  if (numeric_limits<int>::max() != min_number_of_iterations) {
    return min_number_of_iterations;
  }

  return -1;
}

int SwitchSort_v2(const int* arr, const int arr_size) {
  vector<int> numbers(arr, arr + arr_size);

  if (is_sorted(begin(numbers), end(numbers))) {
    return 0;
  }

  return find_min_number_of_iterations(move(numbers));
}

int main() {
  // int A[] = gets(stdin);
  // cout << SwitchSort_v2(A, sizeof(A)/sizeof(*A));
  const int B[] = {1, 3, 4, 2};
  cout << SwitchSort_v2(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 2
  const int C[] = {3, 1, 2};
  cout << SwitchSort_v2(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 2
  const int D[] = {1, 3, 4, 2};
  cout << SwitchSort_v2(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 2
  const int E[] = {3, 4, 2, 1};
  cout << SwitchSort_v2(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: 3
  const int F[] = {4, 3, 2, 1};
  cout << SwitchSort_v2(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: 2
  const int G[] = {3, 4, 2, 1};
  cout << SwitchSort_v2(G, sizeof(G) / sizeof(*G))
       << '\n';  // expected output: 3
  const int H[] = {4, 3, 2, 1};
  cout << SwitchSort_v2(H, sizeof(H) / sizeof(*H))
       << '\n';  // expected output: 2
  const int I[] = {5, 4, 3, 2, 1};
  cout << SwitchSort_v2(I, sizeof(I) / sizeof(*I))
       << '\n';  // expected output: 2
  const int J[] = {5, 3, 4, 1, 2};
  cout << SwitchSort_v2(J, sizeof(J) / sizeof(*J))
       << '\n';  // expected output: 4
  const int K[] = {5, 4, 3, 1, 2};
  cout << SwitchSort_v2(K, sizeof(K) / sizeof(*K))
       << '\n';  // expected output: 3

  return 0;
}
