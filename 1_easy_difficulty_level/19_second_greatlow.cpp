/*
Coderbyte coding challenge: Second Greatlow

Using the C++ language, have the function SecondGreatLow(arr) take the array of
numbers stored in arr and return the second lowest and second greatest numbers,
respectively, separated by a space. For example: if arr contains [7, 7, 12, 98,
106] the output should be 12 98. The array will not be empty and will contain at
least 2 numbers. It can get tricky if there's just two numbers!

Sample test cases:

Input:  1, 42, 42, 180
Output: "42 42"

Input:  4, 90
Output: "90 4"
*/

#include <algorithm>
// #include <iostream>
#include <string>

#include <stl_helper_functions.hpp>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

using namespace std;

string second_great_low(int* arr, const int arr_size) {
  if (1 == arr_size)
    return "Array argument has only 1 element!";

  sort(arr, arr + arr_size);

  if (2 == arr_size)
    return to_string(arr[1]) + " " + to_string(arr[0]);

  int second_min_element{arr[0]};
  int second_max_element{arr[arr_size - 1]};
  int x{};

  // 1 2 5
  // 1   5
  //  second_min_element = 2, x = 1
  // 1, 1 >= 1, 1--
  // 2 < 5 ? 2
  // second_max_element = 2

  for (int i{1}; i < arr_size; ++i) {
    if (arr[i] > second_min_element) {
      second_min_element = arr[i];
      x = i;
      break;
    }
  }

  for (int j{arr_size - 2}; j >= x; --j) {
    if (arr[j] < second_max_element) {
      second_max_element = arr[j];
      break;
    }
  }

  return to_string(second_min_element) + " " + to_string(second_max_element);
}

TEST_CASE("Second Greatlow : second_great_low") {
  int a[] = {7, 7, 12, 98, 106};
  CHECK(second_great_low(a, sizeof(a) / sizeof(*a)) == "12 98");
  int b[] = {1, 42, 42, 180};
  CHECK(second_great_low(b, sizeof(b) / sizeof(*b)) == "42 42");
  int c[] = {4, 90};
  CHECK(second_great_low(c, sizeof(c) / sizeof(*c)) == "90 4");
  int d[] = {1, 2, 5};
  CHECK(second_great_low(d, sizeof(d) / sizeof(*d)) == "2 2");
}

// int main() {
//   // int A[] = gets(stdin);
//   // cout << second_great_low(A, sizeof(A) / sizeof(*A));
//   int a[] = {7, 7, 12, 98, 106};
//   cout << second_great_low(a, sizeof(a) / sizeof(*a))
//        << '\n';  // expected output: "12 98"
//   int b[] = {1, 42, 42, 180};
//   cout << second_great_low(b, sizeof(b) / sizeof(*b))
//        << '\n';  // expected output: "42 42"
//   int c[] = {4, 90};
//   cout << second_great_low(c, sizeof(c) / sizeof(*c))
//        << '\n';  // expected output: "90 4"
//   int d[] = {1, 2, 5};
//   cout << second_great_low(d, sizeof(d) / sizeof(*d))
//        << '\n';  // expected output: "2 2"

//   return 0;
// }
