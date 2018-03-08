/*
Coderbyte coding challenge: Three Sum

Using the C++ language, have the function ThreeSum(arr) take the array of
integers stored in arr, and determine if any three distinct numbers (excluding
the first element) in the array can sum up to the first element in the array.
For example: if arr is [8, 2, 1, 4, 10, 5, -1, -1] then there are actually three
sets of triplets that sum to the number 8: [2, 1, 5], [4, 5, -1] and [10, -1,
-1]. Your program should return the string true if 3 distinct elements sum to
the first element, otherwise your program should return the string false. The
input array will always contain at least 4 elements.

Sample test cases:

Input:  10, 2, 3, 1, 5, 3, 1, 4, -4, -3, -2
Output: "true"

Input:  12, 3, 1, -5, -4, 7
Output: "false"
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

string ThreeSum_v1(const int* arr, const size_t arr_size) {
  if (arr_size < 4)
    return "false";

  const int sum{arr[0]};

  set<int, greater<int>> sorted_sequence(arr + 1, arr + arr_size);

  vector<int> numbers(begin(sorted_sequence), end(sorted_sequence));
  sort(begin(numbers), end(numbers), [](const int l, const int r) {

    return l > r;

  });

  const bool no_negative_numbers{
      end(numbers) ==
      find_if(begin(numbers), end(numbers), [](const int n) { return n < 0; })};

  const size_t ns{numbers.size()};

  if (ns < 3)
    return "false";

  for (size_t i{}; i < ns - 2; i++) {
    for (size_t j{i + 1}; j < ns - 1; j++) {
      for (size_t k{j + 1}; k < ns; k++) {
        const int current_sum{numbers[i] + numbers[j] + numbers[k]};

        if (sum == current_sum)
          return "true";

        if (no_negative_numbers && (current_sum < sum))
          return "false";
      }
    }
  }

  return "false";
}

bool check_if_three_numbers_exist(const int* arr,
                                  const size_t arr_size,
                                  const size_t pos,
                                  const size_t iter_count = 1,
                                  const int current_sum = 0) {
  for (size_t i{pos}; i < arr_size; i++) {
    if ((current_sum + arr[i] == arr[0]) && (3 == iter_count))
      return true;

    else if (iter_count < 3) {
      if (check_if_three_numbers_exist(arr, arr_size, i + 1, iter_count + 1,
                                       current_sum + arr[i]))
        return true;
    }
  }

  return false;
}

string ThreeSum_v2(const int* arr, const size_t arr_size) {
  if (arr_size < 4)
    return "false";

  if (check_if_three_numbers_exist(arr, arr_size, 1, 1, 0))
    return "true";

  return "false";
}

int main() {
  // const int A[] = gets(stdin);
  // cout << ThreeSum_v2(A, sizeof(A)/sizeof(*A));
  const int B[] = {8, 2, 1, 4, 10, 5, -1, -1};
  cout << ThreeSum_v2(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "true"
  const int C[] = {10, 2, 3, 1, 5, 3, 1, 4, -4, -3, -2};
  cout << ThreeSum_v2(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "true"
  const int D[] = {12, 3, 1, -5, -4, 7};
  cout << ThreeSum_v2(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "false"
  const int E[] = {10, 5, 5, 5, 5};
  cout << ThreeSum_v2(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: "false"
  const int F[] = {10, 2, 2, 2, 2, 2, 2,  2,  2,  2,  2,  5,
                   5,  5, 5, 5, 5, 8, -2, -2, -2, -2, -1, 7};
  cout << ThreeSum_v2(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: "true"
  const int G[] = {5, -6, 4, -5, -3, -2, 7, 1, 2, 12, 8, 14};
  cout << ThreeSum_v2(G, sizeof(G) / sizeof(*G))
       << '\n';  // expected output: "true"

  return 0;
}
