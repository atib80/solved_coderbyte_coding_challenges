/*
Coderbyte coding challenge: Number Addition

Using the C++ language, have the function NumberSearch(str) take the str
parameter, search for all the numbers in the string, add them together, then
return that final number. For example: if str is "88Hello 3World!" the output
should be 91. You will have to differentiate between single digit numbers and
multiple digit numbers like in the example above. So "55Hello" and "5Hello 5"
should return two different answers. Each string will contain at least one
letter or symbol.

Sample test cases:

Input:  "75Number9"
Output: 84

Input:  "75Number-9"
Output: 66

Input:  "-75Number-9"
Output: -84

Input:  "10 2One Number*1*"
Output: 13
*/

#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

std::string trim(const std::string& src,
                 const char* chars_to_trim = " \t\n\f\v\r") {
  if (0U == src.length())
    return {};

  const std::unordered_set<char> trimmed_chars(
      chars_to_trim, chars_to_trim + strlen(chars_to_trim));

  const auto first{std::find_if(
      std::cbegin(src), std::cend(src), [&trimmed_chars](const char ch) {
        return trimmed_chars.find(ch) == std::cend(trimmed_chars);
      })};

  if (first == std::cend(src))
    return {};

  const auto last{std::find_if(std::crbegin(src), std::crend(src),
                               [&trimmed_chars](const char ch) {
                                 return trimmed_chars.find(ch) ==
                                        std::cend(trimmed_chars);
                               })
                      .base()};

  return {first, last};
}

string NumberAddition(string str) {
  str = trim(str);

  const size_t str_len{str.length()};
  size_t pos{};
  int64_t sum{};

  while (pos < str_len) {
    size_t start_digit{str.find_first_of("+-0123456789", pos)};

    if (string::npos == start_digit)
      return to_string(sum);

    if ('-' == str[start_digit] || '+' == str[start_digit]) {
      if (start_digit + 1 == str_len || !isdigit(str[start_digit + 1])) {
        pos = start_digit + 1;
        continue;
      }
    }

    size_t end_digit{str.find_first_not_of("0123456789", start_digit + 1)};

    if (string::npos == end_digit)
      end_digit = str_len;

    sum += stoll(str.substr(start_digit, end_digit - start_digit));

    pos = end_digit;
  }

  return to_string(sum);
}

int main() {
  // cout << NumberAddition(gets(stdin));
  cout << NumberAddition("88Hello 3World!") << '\n';    // expected output: 91
  cout << NumberAddition("55Hello") << '\n';            // expected output: 55
  cout << NumberAddition("5Hello 5") << '\n';           // expected output: 10
  cout << NumberAddition("75Number9") << '\n';          // expected output: 84
  cout << NumberAddition("-75Number9") << '\n';         // expected output: -66
  cout << NumberAddition("75Number-9") << '\n';         // expected output: 66
  cout << NumberAddition("-75Number-9") << '\n';        // expected output: -84
  cout << NumberAddition("10 2One Number*1*") << '\n';  // expected output: 13

  return 0;
}
