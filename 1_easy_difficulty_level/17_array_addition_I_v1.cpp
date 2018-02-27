/*
Coderbyte coding challenge: Array Addition I

Using the C++ language, have the function ArrayAdditionI(arr) take the array of
numbers stored in arr and return the string true if any combination of numbers
in the array can be added up to equal the largest number in the array, otherwise
return the string false. For example: if arr contains [4, 6, 23, 10, 1, 3] the
output should return true because 4 + 6 + 10 + 3 = 23. The array will not be
empty, will not contain all the same elements, and may contain negative numbers.

Sample test cases:

Input:  5,7,16,1,2
Output: "false"

Input:  3,5,-1,8,12
Output: "true"
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string array_addition_1(const int* arr, const size_t arr_size) {
  if (arr_size < 2)
    return "false";

  vector<int> numbers(arr, arr + arr_size);

  sort(begin(numbers), end(numbers),
       [](const int lhs, const int rhs) { return (lhs > rhs); });

  const int maximum{numbers[0]};

  auto negative_pos = find_if(begin(numbers), end(numbers),
                              [](const int& n) { return (n < 0); });

  for (size_t i{1}; i < numbers.size(); i++) {
    int current_sum{};

    for (size_t j{i}; j < numbers.size(); j++) {
      current_sum += numbers[j];

      if (maximum == current_sum)
        return "true";

      if (current_sum > maximum) {
        if (negative_pos != end(numbers)) {
          int csum{current_sum};

          for (auto start = negative_pos; start != end(numbers); ++start) {
            csum += *start;

            if (maximum == csum)
              return "true";
          }

          if (csum > maximum)
            current_sum -= numbers[j];

        } else {
          current_sum -= numbers[j];
        }
      }
    }
  }

  return "false";
}

int main() {
  // int A[] = gets(stdin);
  // cout << array_addition_1(A, sizeof(A)/sizeof(A[0]));
  const int A[] = {4, 6, 23, 10, 1, 3};
  cout << array_addition_1(A, sizeof(A) / sizeof(A[0]))
       << '\n';  // expected output: "true"
  const int B[] = {5, 7, 16, 1, 2};
  cout << array_addition_1(B, sizeof(B) / sizeof(B[0]))
       << '\n';  // expected output: "false"
  const int C[] = {3, 5, -1, 8, 12};
  cout << array_addition_1(C, sizeof(C) / sizeof(C[0]))
       << '\n';  // expected output: "true"
  const int D[] = {3, 4, 5, 7};
  cout << array_addition_1(D, sizeof(D) / sizeof(D[0]))
       << '\n';  // expected output: "true"
  const int E[] = {1, 1, 1, 1, 6};
  cout << array_addition_1(E, sizeof(E) / sizeof(E[0]))
       << '\n';  // expected output: "false"
  const int F[] = {2, 4, 6, 12, 92};
  cout << array_addition_1(F, sizeof(F) / sizeof(F[0]))
       << '\n';  // expected output: "false"
  const int G[] = {1, 2, 3, 4};
  cout << array_addition_1(G, sizeof(G) / sizeof(G[0]))
       << '\n';  // expected output: "true"
  const int H[] = {54, 49, 1, 0, 7, 4};
  cout << array_addition_1(H, sizeof(H) / sizeof(H[0]))
       << '\n';  // expected output: "true"

  return 0;
}
