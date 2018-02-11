/*
Coderbyte coding challenge: AB Check (v1, v2)

Using the C++ language, have the function ABCheck(str) take the str parameter
being passed and return the string true if the characters a and b are separated
by exactly 3 places anywhere in the string at least once (ie. "lane borrowed"
would result in true because there is exactly three characters between a and b).
Otherwise return the string false.

Sample test cases:

Input:  "after badly"
Output: "false"

Input:  "Laura sobs"
Output: "true"
*/

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (0u == str.length())
    return string{};

  size_t begin_str{};
  size_t end_str{str_len - 1};

  for (; begin_str <= end_str; ++begin_str) {
    if (!isspace(str[begin_str]))
      break;
  }

  if (begin_str > end_str)
    return string{};

  for (; end_str > begin_str; --end_str) {
    if (!isspace(str[end_str]))
      break;
  }

  return str.substr(begin_str, end_str - begin_str + 1);
}

string ABCheck_v1(string str) {
  str = trim(str);

  vector<int> a_positions{};
  vector<int> b_positions{};

  const int str_len{static_cast<int>(str.length())};

  for (int i{}; i < str_len; i++) {
    if ('a' == str[i])
      a_positions.emplace_back(i);
    else if ('b' == str[i])
      b_positions.emplace_back(i);
  }

  // looking for any "a...b" occurrence in str

  for (const int a_pos : a_positions) {
    for (const int b_pos : b_positions) {
      if ((b_pos - a_pos) == 4)
        return "true";

      if ((b_pos - a_pos) > 4)
        break;
    }
  }

  // looking for any "b...a" occurrence in str

  for (const int b_pos : b_positions) {
    for (const int a_pos : a_positions) {
      if ((a_pos - b_pos) == 4)
        return "true";

      if ((a_pos - b_pos) > 4)
        break;
    }
  }

  return string{"false"};
}

string ABCheck_v2(string str) {
  str = trim(str);

  size_t start{str.find_first_of("ab")};

  if (string::npos == start)
    return "false";

  while (true) {
    const char prev_char{str[start]};

    const size_t next_char_pos{str.find_first_of("ab", start + 1)};

    if (string::npos == next_char_pos)
      return "false";

    if (prev_char != str[next_char_pos]) {
      if (next_char_pos - start == 4)
        return "true";
    }

    start = next_char_pos;
  }
}

int main() {
  // cout << ABCheck_v2(move(string{gets(stdin)}));
  cout << ABCheck_v2(move(string{"lane borrowed"}))
       << '\n';  // expected output: "true"
  cout << ABCheck_v2(move(string{"after badly"}))
       << '\n';  // expected output: "false"
  cout << ABCheck_v2(move(string{"Laura sobs"}))
       << '\n';  // expected output: "true"

  return 0;
}
