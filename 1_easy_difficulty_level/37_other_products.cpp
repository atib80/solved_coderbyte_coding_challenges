/*
Coderbyte coding challenge: Other Products

Using the C++ language, have the function OtherProducts(arr) take the array of
numbers stored in arr and return a new list of the products of all the other
numbers in the array for each element. For example: if arr is [1, 2, 3, 4, 5]
then the new array, where each location in the new array is the product of all
other elements, is [120, 60, 40, 30, 24]. The following calculations were
performed to get this answer: [(2*3*4*5), (1*3*4*5), (1*2*4*5), (1*2*3*5),
(1*2*3*4)]. You should generate this new array and then return the numbers as a
string joined by a hyphen: 120-60-40-30-24. The array will contain at most 10
elements and at least 1 element of only positive integers.

Sample test cases:

Input:  1,4,3
Output: "12-3-4"

Input:  3,1,2,6
Output: "12-36-18-6"
*/

#include <iostream>
#include <sstream>
#include <string>
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

string OtherProducts(const int* numbers, const size_t numbers_size) {
  if (!numbers_size)
    return string{"Not possible!"};

  if (1 == numbers_size)
    return to_string(numbers[0]);

  vector<int> products(numbers_size);

  for (size_t i{}; i < numbers_size; i++) {
    int product{1};

    for (size_t j{}; j < numbers_size; j++) {
      if (j == i)
        continue;

      product *= numbers[j];
    }

    products[i] = product;
  }

  return join(products, "-");
}

int main() {
  // const int A[] = gets(stdin);
  // cout << OtherProducts(A, sizeof(A)/sizeof(*A));
  const int B[] = {1, 2, 3, 4, 5};
  cout << OtherProducts(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "120-60-40-30-24"
  const int C[] = {1, 4, 3};
  cout << OtherProducts(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "12-3-4"
  const int D[] = {3, 1, 2, 6};
  cout << OtherProducts(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "12-36-18-6"

  return 0;
}
