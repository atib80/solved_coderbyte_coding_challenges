/*
Coderbyte coding challenge: Ex Oh

Using the C++ language, have the function ExOh(str) take the str parameter being
passed and return the string true if there is an equal number of x's and o's,
otherwise return the string false. Only these two letters will be entered in the
string, no punctuation or numbers. For example: if str is "xooxxxxooxo" then the
output should return false because there are 6 x's and 5 o's.

Sample test cases:

Input:  "xooxxo"
Output: "true"

Input:  "x"
Output: "false"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <locale>
#include <string>
#include <unordered_set>

using namespace std;

string trim(const string& str, const locale& loc = locale{}) {
  const size_t str_len{str.length()};

  if (0U == str_len)
    return {};

  size_t begin_str{};
  size_t end_str{str_len - 1};

  for (; begin_str <= end_str; ++begin_str) {
    if (!isspace(str[begin_str], loc))
      break;
  }

  if (begin_str > end_str)
    return {};

  for (; end_str > begin_str; --end_str) {
    if (!isspace(str[end_str], loc))
      break;
  }

  return str.substr(begin_str, end_str - begin_str + 1);
}

string ex_oh_v1(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (0U == str_len || str_len % 2 == 1)
    return "false";

  static size_t char_count[128];
  char_count['o'] = 0U;
  char_count['x'] = 0U;

  for (const char ch : str)
    ++char_count[static_cast<size_t>(ch)];

  if (char_count['o'] == char_count['x'])
    return "true";
  return "false";
}

string ex_oh_v2(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (0U == str_len || str_len % 2 == 1)
    return "false";

  sort(begin(str), end(str));

  if (str[str_len / 2 - 1] != 'o' && str[str_len / 2] != 'x')
    return "false";

  return "true";
}

string ex_oh_v3(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (0U == str_len || str_len % 2 == 1)
    return "false";

  unordered_multiset<char> char_freq{cbegin(str), cend(str)};

  if (char_freq.count('o') != char_freq.count('x'))
    return "false";

  return "true";
}

int main() {
  // cout << ex_oh_v1(gets(stdin));
  cout << ex_oh_v3("xooxxxxooxo") << '\n';  // expected output: "false"
  cout << ex_oh_v3("xooxxo") << '\n';       // expected output: "true"
  cout << ex_oh_v3("x") << '\n';            // expected output: "false"

  return 0;
}
