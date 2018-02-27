/*
Coderbyte coding challenge: Array Addition

Using the C++ language, have the function ArrayAddition(arr) take the array of
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

string ArrayAddition_v1(const int* arr, const size_t arr_size) {
  if (arr_size < 2)
    return "false";

  vector<int> numbers(arr, arr + arr_size);

  sort(begin(numbers), end(numbers),
       [](const int lhs, const int rhs) { return (lhs > rhs); });

  const int maximum{numbers[0]};

  int current_sum{};

  auto negative_pos = find_if(begin(numbers), end(numbers),
                              [](const int& n) { return (n < 0); });

  for (size_t i{1}; i < numbers.size(); i++) {
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

    current_sum = 0;
  }

  return "false";
}

bool find_sum_of_numbers_equal_max_number(
    const vector<int>& numbers,
    const size_t start_index,
    const bool no_negative_numbers = false,
    const int current_sum = 0) {
  if (numbers[0] == current_sum)
    return true;

  if (no_negative_numbers && (current_sum > numbers[0]))
    return false;

  if (start_index == numbers.size())
    return false;

  for (size_t i{start_index}; i < numbers.size(); i++) {
    if (find_sum_of_numbers_equal_max_number(
            numbers, i + 1, no_negative_numbers, current_sum + numbers[i]))
      return true;
  }

  return false;
}

string ArrayAddition_v2(const int* arr, const size_t arr_size) {
  if (arr_size < 2)
    return "false";

  vector<int> numbers(arr, arr + arr_size);

  sort(begin(numbers), end(numbers),
       [](const int lhs, const int rhs) { return (lhs > rhs); });

  const bool no_negative_numbers{end(numbers) ==
                                 find_if(begin(numbers), end(numbers),
                                         [](const int& n) { return (n < 0); })};

  if (find_sum_of_numbers_equal_max_number(numbers, 1, no_negative_numbers, 0))
    return "true";

  return "false";
}

int main() {
  // int A[] = gets(stdin);
  // cout << ArrayAddition_v1(A, sizeof(A) / sizeof(A[0]));
  const int A[] = {4, 6, 23, 10, 1, 3};
  cout << ArrayAddition_v1(A, sizeof(A) / sizeof(A[0]))
       << '\n';  // expected: "true"
  const int B[] = {5, 7, 16, 1, 2};
  cout << ArrayAddition_v1(B, sizeof(B) / sizeof(B[0]))
       << '\n';  // expected: "false"
  const int C[] = {3, 5, -1, 8, 12};
  cout << ArrayAddition_v1(C, sizeof(C) / sizeof(C[0]))
       << '\n';  // expected: "true"

  return 0;
}
