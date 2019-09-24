/*
Coderbyte coding challenge: Array Matching

Using the C++ language, have the function ArrayMatching(strArr) read the array
of strings stored in strArr which will contain only two elements, both of which
will represent an array of positive integers. For example: if strArr is ["[1, 2,
5, 6]", "[5, 2, 8, 11]"], then both elements in the input represent two integer
arrays, and your goal for this challenge is to add the elements in corresponding
locations from both arrays. For the example input, your program should do the
following additions: [(1 + 5), (2 + 2), (5 + 8), (6 + 11)] which then equals [6,
4, 13, 17]. Your program should finally return this resulting array in a string
format with each element separated by a hyphen: 6-4-13-17.

If the two arrays do not have the same amount of elements, then simply append
the remaining elements onto the new array (example shown below). Both arrays
will be in the format: [e1, e2, e3, ...] where at least one element will exist
in each array.

Sample test cases:

Input:  "[5, 2, 3]", "[2, 2, 3, 10, 6]"
Output: "7-4-6-10-6"

Input:  "[1, 2, 1]", "[2, 1, 5, 2]"
Output: "3-3-6-2"
*/

#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

template <typename ContainerType>
string join(const ContainerType& items, const char* needle) {
  ostringstream oss{};
  auto start = cbegin(items);
  const auto last = cend(items);

  while (start != last) {
    oss << *start;
    ++start;
    if (start != last)
      oss << needle;
  }

  return oss.str();
}

string ArrayMatching(const string* str_arr, const size_t str_arr_size) {
  if (str_arr_size < 2U)
    return "not possible";

  const auto count_of_numbers_left_str =
      count(cbegin(str_arr[0]), cend(str_arr[0]), ',') + 1;
  const auto count_of_numbers_right_str =
      count(cbegin(str_arr[1]), cend(str_arr[1]), ',') + 1;

  array<vector<int64_t>, 2U> numbers{
      {vector<int64_t>(count_of_numbers_left_str),
       vector<int64_t>(count_of_numbers_right_str)}};

  for (size_t i{}; i < 2U; ++i) {
    size_t first{};
    for (size_t j{}; j < numbers[i].size(); ++j) {
      first = str_arr[i].find_first_of("-0123456789", first);

      if (string::npos == first)
        break;

      const size_t last{str_arr[i].find_first_not_of("-0123456789", first + 1)};

      if (string::npos == last) {
        numbers[i][j] = stoll(str_arr[i].substr(first));
        break;
      }

      numbers[i][j] = stoll(str_arr[i].substr(first, last - first));

      first = last + 1;
    }
  }

  const size_t ln_size{numbers[0].size()};
  const size_t rn_size{numbers[1].size()};

  const size_t min_len{min(ln_size, rn_size)};

  vector<int64_t> sum(max(ln_size, rn_size));

  for (size_t i{}; i < min_len; ++i)
    sum[i] = numbers[0][i] + numbers[1][i];

  if (ln_size != rn_size) {
    if (ln_size < rn_size) {
      for (size_t i{ln_size}; i < rn_size; ++i)
        sum[i] = numbers[1][i];
    } else {
      for (size_t i{rn_size}; i < ln_size; ++i)
        sum[i] = numbers[0][i];
    }
  }

  return join(sum, "-");
}

int main() {
  // const string A[] = gets(stdin);
  // cout << ArrayMatching(A, sizeof(A)/sizeof(*A));
  const string b[]{"[1, 2, 5, 6]", "[5, 2, 8, 11]"};
  cout << ArrayMatching(b, sizeof(b) / sizeof(*b))
       << '\n';  // expected output: "6-4-13-17"
  const string c[]{"[5, 2, 3]", "[2, 2, 3, 10, 6]"};
  cout << ArrayMatching(c, sizeof(c) / sizeof(*c))
       << '\n';  // expected output: "7-4-6-10-6"
  const string d[]{"[1, 2, 1]", "[2, 1, 5, 2]"};
  cout << ArrayMatching(d, sizeof(d) / sizeof(*d))
       << '\n';  // expected output: "3-3-6-2"
  const string e[]{"[2]", "[1, 1]"};
  cout << ArrayMatching(e, sizeof(e) / sizeof(*e))
       << '\n';  // expected output: "3-1"
  const string f[]{"[2]", "[2]"};
  cout << ArrayMatching(f, sizeof(f) / sizeof(*f))
       << '\n';  // expected output: "4"
  const string g[]{"[1]", "[5, 6, 2, 1, 5, 3]"};
  cout << ArrayMatching(g, sizeof(g) / sizeof(*g))
       << '\n';  // expected output: "6-6-2-1-5-3"
  const string h[]{"[7, 7, 7, 7]", "[2]"};
  cout << ArrayMatching(h, sizeof(h) / sizeof(*h))
       << '\n';  // expected output: "9-7-7-7"

  return 0;
}
