/*
Coderbyte coding challenge: Run Length

Using the C++ language, have the function RunLength(str) take the str parameter
being passed and return a compressed version of the string using the Run-length
encoding algorithm. This algorithm works by taking the occurrence of each
repeating character and outputting that number along with a single character of
the repeating sequence. For example: "wwwggopp" would return 3w2g1o2p. The
string will not contain any numbers, punctuation, or symbols.

Sample test cases:

Input:  "aabbcde"
Output: "2a2b1c1d1e"

Input:  "wwwbbbw"
Output: "3w3b1w"
*/

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

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

string run_length_v1(string str) {
  str = trim(str);

  if (str.empty())
    return string{};

  const size_t str_len{str.length()};

  ostringstream oss{};

  if (1 == str_len) {
    oss << '1' << str[0];
    return oss.str();
  }

  char current_ch{str[0]};
  size_t current_ch_count{1};

  for (size_t i{1}; i < str_len; i++) {
    if (current_ch == str[i]) {
      current_ch_count++;
      continue;
    }

    oss << current_ch_count << current_ch;
    current_ch = str[i];
    current_ch_count = 1;
  }

  oss << current_ch_count << current_ch;

  return oss.str();
}

string run_length_v2(string str) {
  str = trim(str);

  if (str.empty())
    return string{};

  const size_t str_len{str.length()};

  if (1 == str_len)
    return string({'1', str.front()});

  ostringstream oss{};
  size_t start_pos{}, end_pos{1};

  while (string::npos != end_pos) {
    end_pos = str.find_first_not_of(str[start_pos], end_pos);

    if (string::npos == end_pos) {
      oss << (str_len - start_pos) << str[start_pos];
      break;
    }

    oss << (end_pos - start_pos) << str[start_pos];
    start_pos = end_pos;
  }

  return oss.str();
}

int main() {
  // cout << run_length_v2(move(string{gets(stdin)}));
  cout << run_length_v2(move(string{"wwwggopp"}))
       << '\n';  // expected output: "3w2g1o2p"
  cout << run_length_v2(move(string{"aabbcde"}))
       << '\n';  // expected output: "2a2b1c1d1e"
  cout << run_length_v2(move(string{"wwwbbbw"}))
       << '\n';  // expected output: "3w3b1w"

  return 0;
}
