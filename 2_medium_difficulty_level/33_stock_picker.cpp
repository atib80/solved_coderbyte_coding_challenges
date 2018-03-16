/*
Coderbyte coding challenge: Stock Picker

Using the C++ language, have the function StockPicker(arr) take the array of
numbers stored in arr which will contain integers that represent the amount in
dollars that a single stock is worth, and return the maximum profit that could
have been made by buying stock on day x and selling stock on day y where y > x.
For example: if arr is [44, 30, 24, 32, 35, 30, 40, 38, 15] then your program
should return 16 because at index 2 the stock was worth $24 and at index 6 the
stock was then worth $40, so if you bought the stock at 24 and sold it at 40,
you would have made a profit of $16, which is the maximum profit that could have
been made with this list of stock prices.

If there is not profit that could have been made with the stock prices, then
your program should return -1. For example: arr is [10, 9, 8, 2] then your
program should return -1.

Sample test cases:

Input:  10,12,4,5,9
Output: 5

Input:  14,20,4,12,5,11
Output: 8
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int StockPicker_v1(const int* arr, const int arr_size) {
  if (arr_size < 2)
    return -1;

  int current_max_profit{};
  int current_minimum{arr[0]};

  for (int i{1}; i < arr_size; i++) {
    if (arr[i] - current_minimum > current_max_profit)
      current_max_profit = arr[i] - current_minimum;

    else if (arr[i] < current_minimum)
      current_minimum = arr[i];
  }

  if (!current_max_profit)
    return -1;

  return current_max_profit;
}

int StockPicker_v2(const int* arr, const size_t arr_size) {
  int current_max_profit{-1};

  for (size_t i{}; i < arr_size - 1; i++) {
    for (size_t j{i + 1}; j < arr_size; j++) {
      if (arr[j] <= arr[i])
        continue;

      if (arr[j] - arr[i] > current_max_profit)
        current_max_profit = arr[j] - arr[i];
    }
  }

  return current_max_profit;
}

int main() {
  // const int A[] = gets(stdin);
  // cout << StockPicker_v2(A, sizeof(A)/sizeof(*A));
  const int B[] = {44, 30, 24, 32, 35, 30, 40, 38, 15};
  cout << StockPicker_v2(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 16
  const int C[] = {10, 12, 4, 5, 9};
  cout << StockPicker_v2(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 5
  const int D[] = {14, 20, 4, 12, 5, 11};
  cout << StockPicker_v2(D, sizeof(D) / sizeof(*D))
       << '\n';                      // expected output: 8
  const int E[] = {5, 10, 4, 6, 7};  // 4, 5, 6, 7, 10
  cout << StockPicker_v2(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: 5

  return 0;
}
