/*
Coderbyte coding challenge: Array Rotation

Using the C++ language, have the function ArrayRotation(arr) take the arr
parameter being passed which will be an array of non-negative integers and
circularly rotate the array starting from the Nth element where N is equal to
the first integer in the array. For example: if arr is [2, 3, 4, 1, 6, 10] then
your program should rotate the array starting from the 2nd position because the
first element in the array is 2. The final array will therefore be [4, 1, 6, 10,
2, 3], and your program should return the new array as a string, so for this
example your program would return 4161023. The first element in the array will
always be an integer greater than or equal to 0 and less than the size of the
array.

Sample test cases:

Input:  2,3,4,1,6,10
Output: "4161023"

Input:  3,2,1,6
Output: "6321"

Input:  4,3,4,3,1,2
Output: "124343"
*/

#include <deque>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <typename _Container>
string join(const _Container& items, const string& needle = "") {
  ostringstream oss{};

  auto start = begin(items);

  const auto last = end(items);

  while (start != last) {
    if (!needle.empty())
      oss << *start << needle;
    else
      oss << *start;

    ++start;
  }

  string result{oss.str()};

  const size_t needle_len{needle.length()};

  if (!needle_len)
    return result;

  result.erase(result.length() - needle_len, needle_len);

  return result;
}

bool rotate_array_elements(deque<int>& deq, const size_t k) {
  if (!k || deq.size() < 2)
    return false;

  for (size_t i{}; i < k; i++) {
    const int number{deq.front()};
    deq.pop_front();
    deq.emplace_back(number);
  }

  return true;
}

string ArrayRotation(const int* arr, const size_t arr_size) {
  deque<int> numbers(arr, arr + arr_size);

  const size_t number_of_shifts{numbers[0] % numbers.size()};

  rotate_array_elements(numbers, number_of_shifts);

  return join(numbers);
}

int main() {
  // const int A[] = gets(stdin);
  // cout << ArrayRotation(A, sizeof(A)/sizeof(*A));
  const int B[] = {2, 3, 4, 1, 6, 10};
  cout << ArrayRotation(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "4161023"
  const int C[] = {3, 2, 1, 6};
  cout << ArrayRotation(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "6321"
  const int D[] = {4, 3, 4, 3, 1, 2};
  cout << ArrayRotation(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "124343"

  return 0;
}
