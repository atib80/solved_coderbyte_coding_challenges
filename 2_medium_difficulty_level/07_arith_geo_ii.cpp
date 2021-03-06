/*
Coderbyte coding challenge: Arith Geo II

Using the C++ language, have the function ArithGeoII(arr) take the array of
numbers stored in arr and return the string "Arithmetic" if the sequence follows
an arithmetic pattern or return "Geometric" if it follows a geometric pattern.
If the sequence doesn't follow either pattern return -1.
An arithmetic sequence is one where the difference between each of the numbers
is consistent, where as in a geometric sequence, each term after the first is
multiplied by some constant or common ratio. Arithmetic example: [2, 4, 6, 8]
and Geometric example: [2, 6, 18, 54]. Negative numbers may be entered as
parameters, 0 will not be entered, and no array will contain all the same
elements.

Sample test cases:

Input:  5,10,15
Output: "Arithmetic"

Input:  2,4,16,24
Output: "-1"
*/

#include <iostream>
#include <string>

using namespace std;

string ArithGeoII(const int* arr, const size_t arr_size) {
  if (arr_size < 2)
    return "-1";

  bool is_arithmetic{true};
  bool is_geometric{true};

  const int diff{arr[1] - arr[0]};
  int factor{1};

  if (!arr[0] || !arr[1])
    is_geometric = false;
  else
    factor = arr[1] / arr[0];

  for (size_t i{1}; (i < arr_size && (is_arithmetic || is_geometric)); i++) {
    if (is_arithmetic && (diff != (arr[i] - arr[i - 1]))) {
      is_arithmetic = false;
    }

    if (is_geometric && (factor != (arr[i] / arr[i - 1]))) {
      is_geometric = false;
    }
  }

  if (is_arithmetic)
    return "Arithmetic";
  if (is_geometric)
    return "Geometric";

  return "-1";
}

int main() {
  // const int A[] = gets(stdin);
  // cout << ArithGeoII(A, sizeof(A)/sizeof(*A));
  const int B[] = {2, 4, 6, 8};
  cout << ArithGeoII(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "Arithmetic"
  const int C[] = {2, 6, 18, 54};
  cout << ArithGeoII(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "Geometric"
  const int D[] = {5, 10, 15};
  cout << ArithGeoII(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "Arithmetic"
  const int E[] = {2, 4, 16, 24};
  cout << ArithGeoII(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: "-1"

  return 0;
}
