/*
Coderbyte coding challenge: Number Stream

Using the C++ language, have the function NumberStream(str) take the str
parameter being passed which will contain the numbers 2 through 9, and determine
if there is a consecutive stream of digits of at least N length where N is the
actual digit value. If so, return the string true, otherwise return the string
false.

For example: if str is "6539923335" then your program should return the string
true because there is a consecutive stream of 3's of length 3. The input string
will always contain at least one digit.

Sample test cases:

Input:  "5556293383563665"
Output: "false"

Input:  "5788888888882339999"
Output: "true"
*/

#include <cctype>
#include <iostream>
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

string NumberStream_v1(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  for (size_t i{}; i < str_len - 1; i++) {
    const char digit{str[i]};
    const size_t rep{static_cast<size_t>(str[i] - '0')};

    if (i + rep > str_len) {
      if (str_len - 2 == i)
        return "false";

      continue;
    }

    bool is_seq_correct{true};

    for (size_t j{i + 1}; j < i + rep; j++) {
      if (digit != str[j]) {
        is_seq_correct = false;
        i = j - 1;
        break;
      }
    }

    if (is_seq_correct)
      return "true";
  }

  return "false";
}

string NumberStream_v2(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  for (char digit{'2'}; digit <= '9'; digit++) {
    size_t start_pos{};

    while (true) {
      start_pos = str.find(digit, start_pos);

      if (string::npos == start_pos)
        break;

      size_t last_pos{str.find_first_not_of(digit, start_pos + 1)};

      if (string::npos == last_pos) {
        if (digit != str[str_len - 1])
          break;

        last_pos = str_len - 1;

        if (last_pos - start_pos + 1 >= static_cast<size_t>(digit - '0'))
          return "true";

        break;
      }

      if (last_pos - start_pos >= static_cast<size_t>(digit - '0'))
        return "true";

      start_pos = last_pos + 1;
    }
  }

  return "false";
}

int main() {
  // cout << NumberStream_v2(move(string{gets(stdin)}));
  cout << NumberStream_v2(move(string{"6539923335"}))
       << '\n';  // expected output: "true"
  cout << NumberStream_v2(move(string{"5556293383563665"}))
       << '\n';  // expected output: "false"
  cout << NumberStream_v2(move(string{"5788888888882339999"}))
       << '\n';  // expected output: "true"

  return 0;
}
