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
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (!str_len)
    return string{};

  size_t first{}, last{str_len - 1};

  for (; first <= last; ++first) {
    if (!isspace(str[first]))
      break;
  }

  if (first > last)
    return string{};

  for (; last > first; --last) {
    if (!isspace(str[last]))
      break;
  }

  return str.substr(first, last - first + 1);
}

vector<string> split(const string& source,
                     const char* needle,
                     size_t const max_count = string::npos) {
  vector<string> parts{};

  string needle_st{needle};

  const size_t source_len{source.length()};

  const size_t needle_len{needle_st.size()};

  if (!source_len)
    return parts;

  if (!needle_len) {
    const size_t upper_limit{max_count < source_len ? max_count : source_len};
    for (size_t i{}; i < upper_limit; i++)
      parts.emplace_back(1, source[i]);
    return parts;
  }

  size_t number_of_parts{}, prev{};

  while (true) {
    const size_t current{source.find(needle_st, prev)};

    if (string::npos == current)
      break;

    number_of_parts++;

    if ((string::npos != max_count) && (parts.size() == max_count))
      break;

    if ((current - prev) > 0)
      parts.emplace_back(source.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (prev < source_len) {
    if (string::npos == max_count)
      parts.emplace_back(source.substr(prev));

    else if ((string::npos != max_count) && (parts.size() < max_count))
      parts.emplace_back(source.substr(prev));
  }

  return parts;
}

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

string ArrayMatching(const string* str_arr, const size_t str_arr_size) {
  if (str_arr_size < 2)
    return "Not possible!";

  string numbers1_str{trim(str_arr[0])};
  string numbers2_str{trim(str_arr[1])};

  numbers1_str.erase(begin(numbers1_str));
  numbers1_str.erase(--end(numbers1_str));

  numbers2_str.erase(begin(numbers2_str));
  numbers2_str.erase(--end(numbers2_str));

  vector<string> numbers_left_str{split(numbers1_str, ", ")};
  vector<string> numbers_right_str{split(numbers2_str, ", ")};

  vector<long> ln(numbers_left_str.size());
  vector<long> rn(numbers_right_str.size());

  for (size_t i{}; i < numbers_left_str.size(); i++)
    ln[i] = stol(numbers_left_str[i]);
  for (size_t i{}; i < numbers_right_str.size(); i++)
    rn[i] = stol(numbers_right_str[i]);

  const size_t ln_size{ln.size()};
  const size_t rn_size{rn.size()};

  const size_t min_len{min(ln_size, rn_size)};

  vector<long> sum(max(ln_size, rn_size));

  for (size_t i{}; i < min_len; i++)
    sum[i] = ln[i] + rn[i];

  if (ln_size != rn_size) {
    if (ln_size < rn_size) {
      for (size_t i{ln_size}; i < rn_size; i++)
        sum[i] = rn[i];
    } else {
      for (size_t i{rn_size}; i < ln_size; i++)
        sum[i] = ln[i];
    }
  }

  return join(sum, "-");
}

int main() {
  // const string A[] = gets(stdin);
  // cout << ArrayMatching(A, sizeof(A)/sizeof(*A));
  const string b[] = {"[1, 2, 5, 6]", "[5, 2, 8, 11]"};
  cout << ArrayMatching(b, sizeof(b) / sizeof(*b))
       << '\n';  // expected output: "6-4-13-17"
  const string c[] = {"[5, 2, 3]", "[2, 2, 3, 10, 6]"};
  cout << ArrayMatching(c, sizeof(c) / sizeof(*c))
       << '\n';  // expected output: "7-4-6-10-6"
  const string d[] = {"[1, 2, 1]", "[2, 1, 5, 2]"};
  cout << ArrayMatching(d, sizeof(d) / sizeof(*d))
       << '\n';  // expected output: "3-3-6-2"
  const string e[] = {"[2]", "[1, 1]"};
  cout << ArrayMatching(e, sizeof(e) / sizeof(*e))
       << '\n';  // expected output: "3-1"
  const string f[] = {"[2]", "[2]"};
  cout << ArrayMatching(f, sizeof(f) / sizeof(*f))
       << '\n';  // expected output: "4"
  const string g[] = {"[1]", "[5, 6, 2, 1, 5, 3]"};
  cout << ArrayMatching(g, sizeof(g) / sizeof(*g))
       << '\n';  // expected output: "6-6-2-1-5-3"
  const string h[] = {"[7, 7, 7, 7]", "[2]"};
  cout << ArrayMatching(h, sizeof(h) / sizeof(*h))
       << '\n';  // expected output: "9-7-7-7"

  return 0;
}
