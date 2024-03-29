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
// #include <iostream>
#include <string>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

using namespace std;

string array_addition_1_v3(int* arr, const size_t arr_size) {
  if (arr_size < 2)
    return "false";

  sort(arr, arr + arr_size);

  const int max_number{arr[arr_size - 1]};

  const bool has_negative_numbers{arr[0] < 0};

  do {
    int current_sum{};

    for (size_t i{}; i < arr_size - 1; ++i) {
      current_sum += arr[i];

      if (max_number == current_sum)
        return "true";
      if (!has_negative_numbers && current_sum > max_number)
        break;
    }

  } while (next_permutation(arr, arr + arr_size - 1));

  return "false";
}

TEST_CASE("Array Addition I : array_addition_1_v3") {
  int A[] = {4, 6, 23, 10, 1, 3};
  CHECK(array_addition_1_v3(A, sizeof(A) / sizeof(A[0])) == "true");
  int B[] = {5, 7, 16, 1, 2};
  CHECK(array_addition_1_v3(B, sizeof(B) / sizeof(B[0])) == "false");
  int C[] = {3, 5, -1, 8, 12};
  CHECK(array_addition_1_v3(C, sizeof(C) / sizeof(C[0])) == "true");
  int D[] = {3, 4, 5, 7};
  CHECK(array_addition_1_v3(D, sizeof(D) / sizeof(D[0])) == "true");
  int E[] = {1, 1, 1, 1, 6};
  CHECK(array_addition_1_v3(E, sizeof(E) / sizeof(E[0])) == "false");
  int F[] = {2, 4, 6, 12, 92};
  CHECK(array_addition_1_v3(F, sizeof(F) / sizeof(F[0])) == "false");
  int G[] = {1, 2, 3, 4};
  CHECK(array_addition_1_v3(G, sizeof(G) / sizeof(G[0])) == "true");
  int H[] = {54, 49, 1, 0, 7, 4};
  CHECK(array_addition_1_v3(H, sizeof(H) / sizeof(H[0])) == "true");
}

// int main() {
//   // int A[] = gets(stdin);
//   // cout << array_addition_1_v3(A, sizeof(A)/sizeof(A[0]));
//   int A[] = {4, 6, 23, 10, 1, 3};
//   cout << array_addition_1_v3(A, sizeof(A) / sizeof(A[0]))
//        << '\n';  // expected output: "true"
//   int B[] = {5, 7, 16, 1, 2};
//   cout << array_addition_1_v3(B, sizeof(B) / sizeof(B[0]))
//        << '\n';  // expected output: "false"
//   int C[] = {3, 5, -1, 8, 12};
//   cout << array_addition_1_v3(C, sizeof(C) / sizeof(C[0]))
//        << '\n';  // expected output: "true"
//   int D[] = {3, 4, 5, 7};
//   cout << array_addition_1_v3(D, sizeof(D) / sizeof(D[0]))
//        << '\n';  // expected output: "true"
//   int E[] = {1, 1, 1, 1, 6};
//   cout << array_addition_1_v3(E, sizeof(E) / sizeof(E[0]))
//        << '\n';  // expected output: "false"
//   int F[] = {2, 4, 6, 12, 92};
//   cout << array_addition_1_v3(F, sizeof(F) / sizeof(F[0]))
//        << '\n';  // expected output: "false"
//   int G[] = {1, 2, 3, 4};
//   cout << array_addition_1_v3(G, sizeof(G) / sizeof(G[0]))
//        << '\n';  // expected output: "true"
//   int H[] = {54, 49, 1, 0, 7, 4};
//   cout << array_addition_1_v3(H, sizeof(H) / sizeof(H[0]))
//        << '\n';  // expected output: "true"

//   return 0;
// }
