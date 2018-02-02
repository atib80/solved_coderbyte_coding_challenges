/*
Coderbyte coding challenge: Array Couples

Using the C++ language, have the function ArrayCouples(arr) take the arr
parameter being passed which will be an array of an even number of positive
integers, and determine if each pair of integers, [k, k+1], [k+2, k+3], etc. in
the array has a corresponding reversed pair somewhere else in the array. For
example: if arr is [4, 5, 1, 4, 5, 4, 4, 1] then your program should output the
string yes because the first pair 4, 5 has the reversed pair 5, 4 in the array,
and the next pair, 1, 4 has the reversed pair 4, 1 in the array as well. But if
the array doesn't contain all pairs with their reversed pairs, then your program
should output a string of the integer pairs that are incorrect, in the order
that they appear in the array.

For example: if arr is [6, 2, 2, 6, 5, 14, 14, 1] then your program should
output the string 5,14,14,1 with only a comma separating the integers.

Sample test cases:

Input:  4, 5, 1, 4, 5, 4, 4, 1
Output: "yes"

Input:  6, 2, 2, 6, 5, 14, 14, 1
Output: "5,14,14,1"

Input:  2,1,1,2,3,3
Output: "3,3"

Input:  5,4,6,7,7,6,4,5
Output: "yes"
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string ArrayCouples(const int* arr, const size_t arr_size) {
  if (1 == arr_size % 2)
    return "not possible";

  vector<int> numbers(arr, arr + arr_size);

  ostringstream oss{};

  while (!numbers.empty()) {
    const pair<int, int> couple{make_pair(numbers[0], numbers[1])};
    numbers.erase(begin(numbers), begin(numbers) + 2);
    if (numbers.empty()) {
      oss << couple.first << ',' << couple.second;
      break;
    }

    bool found{};
    for (size_t j{}; j < numbers.size() - 1; j += 2) {
      if ((couple.first == numbers[j + 1]) && (couple.second == numbers[j])) {
        found = true;
        numbers.erase(begin(numbers) + j, begin(numbers) + j + 2);
        break;
      }
    }

    if (!found) {
      oss << couple.first << ',' << couple.second << ',';
    }

    else if (numbers.empty())
      return "yes";
  }

  return oss.str();
}

int main() {
  // int A[] = gets(stdin);
  // cout << ArrayCouples(A, sizeof(A)/sizeof(*A));
  const int B[] = {4, 5, 1, 4, 5, 4, 4, 1};
  cout << ArrayCouples(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "yes"
  const int C[] = {6, 2, 2, 6, 5, 14, 14, 1};
  cout << ArrayCouples(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "5,14,14,1"
  const int D[] = {2, 1, 1, 2, 3, 3};
  cout << ArrayCouples(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "3,3"
  const int E[] = {5, 4, 6, 7, 7, 6, 4, 5};
  cout << ArrayCouples(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: "yes"
  const int F[] = {5, 4};
  cout << ArrayCouples(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: "5,4"
  const int G[] = {1, 3, 5};
  cout << ArrayCouples(G, sizeof(G) / sizeof(*G))
       << '\n';  // expected output: "not possible"

  return 0;
}
