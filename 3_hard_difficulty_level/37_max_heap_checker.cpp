/*
Coderbyte coding challenge: Max Heap Checker

Using the C++ language, have the function MaxHeapChecker(arr) take arr
which represents a heap data structure and determine whether or not it is a max
heap. A max heap has the property that all nodes in the heap are either greater
than or equal to each of its children. For example: if arr is [100,19,36,17]
then this is a max heap and your program should return the string max. If the
input is not a max heap then your program should return a list of nodes in
string format, in the order that they appear in the tree, that currently do not
satisfy the max heap property because the child nodes are larger than their
parent. For example: if arr is [10,19,52,13,16] then your program should return
19,52.

Another example: if arr is [10,19,52,104,14] then your program should return
19,52,104

Sample test cases:

Input:  73,74,75,7,2,107
Output: 74,75,107

Input:  1,5,10,2,3,10,1
Output: 5,10
*/

#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

using namespace std;

template <typename _Container>
string join(const _Container& items, const string& needle) {
  ostringstream oss{};

  auto start = begin(items);

  const auto last = end(items);

  while (start != last) {
    oss << *start << needle;

    ++start;
  }

  string result{oss.str()};

  const size_t needle_len{needle.length()};

  result.erase(result.length() - needle_len, needle_len);

  return result;
}

void find_incorrect_max_heap_values(const int* arr,
                                    const size_t arr_size,
                                    const size_t pos,
                                    vector<int>& found_elements) {
  if (pos >= arr_size)
    return;

  if (arr[pos] > arr[pos / 2])
    found_elements.emplace_back(arr[pos]);

  if (pos + 1 < arr_size && arr[pos + 1] > arr[pos / 2])
    found_elements.emplace_back(arr[pos + 1]);

  if (2 * pos + 1 < arr_size)
    find_incorrect_max_heap_values(arr, arr_size, 2 * pos + 1, found_elements);

  if (2 * (pos + 1) + 1 < arr_size)
    find_incorrect_max_heap_values(arr, arr_size, 2 * (pos + 1) + 1,
                                   found_elements);
}

string MaxHeapChecker(const int* arr, const size_t arr_size) {
  if (1 == arr_size)
    return "max";

  vector<int> found_elements{};

  find_incorrect_max_heap_values(arr, arr_size, 1, found_elements);

  if (found_elements.empty())
    return "max";

  return join(found_elements, ",");
}

int main() {
  // const int A[] = gets(stdin);
  // cout << MaxHeapChecker(A, sizeof(A)/sizeof(*A));
  const int B[] = {100, 19, 36, 17};
  cout << MaxHeapChecker(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "max"
  const int C[] = {10, 19, 52, 13, 16};
  cout << MaxHeapChecker(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "19,52"
  const int D[] = {10, 19, 52, 104, 14};
  cout << MaxHeapChecker(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "19,52,104"
  const int E[] = {73, 74, 75, 7, 2, 107};
  cout << MaxHeapChecker(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: "74,75,107"
  const int F[] = {1, 5, 10, 2, 3, 10, 1};
  cout << MaxHeapChecker(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: "5,10"
  const int G[] = {5, 2, 1, 1, 1};
  cout << MaxHeapChecker(G, sizeof(G) / sizeof(*G))
       << '\n';  // expected output: "max"
  const int H[] = {73, 72, 1, 79, 90};
  cout << MaxHeapChecker(H, sizeof(H) / sizeof(*H))
       << '\n';  // expected output: "79,90"
  const int I[] = {100, 99, 98, 97, 96, 95, 94};
  cout << MaxHeapChecker(I, sizeof(I) / sizeof(*I))
       << '\n';  // expected output: "max"
  const int J[] = {73, 74, 81, 79, 90};
  cout << MaxHeapChecker(J, sizeof(J) / sizeof(*J))
       << '\n';  // expected output: "74,81,79,90"

  return 0;
}
