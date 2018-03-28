/*
Coderbyte coding challenge: Simple Password

Using the C++ language, have the function SimplePassword(str) take the str
parameter being passed and determine if it passes as a valid password that
follows the list of constraints:

1. It must have a capital letter.
2. It must contain at least one number.
3. It must contain a punctuation mark.
4. It cannot have the word "password" in the string.
5. It must be longer than 7 characters and shorter than 31 characters.

If all the above constraints are met within the string, then your program should
return the string true, otherwise your program should return the string false.
For example: if str is "apple!M7" then your program should return "true".

Sample test cases:

Input:  "passWord123!!!!"
Output: "false"

Input:  "turkey90AAA="
Output: "true"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <locale>
#include <string>

using namespace std;

template <typename CharType>
bool is_ws_char(CharType ch) {
  switch (ch) {
    case static_cast<CharType>(' '):
    case static_cast<CharType>('\t'):
    case static_cast<CharType>('\n'):
    case static_cast<CharType>('\r'):
    case static_cast<CharType>('\f'):
    case static_cast<CharType>('\v'):
      return true;

    default:
      return false;
  }
}

template <typename StringType>
StringType trim(const StringType& input) {
  using char_type = typename StringType::value_type;
  StringType output{input};
  output.erase(begin(output),
               find_if(begin(output), end(output),
                       [](const char_type ch) { return !is_ws_char(ch); }));

  output.erase(find_if(output.rbegin(), output.rend(),
                       [](const char_type ch) { return !is_ws_char(ch); })
                   .base(),
               end(output));

  return output;
}

template <typename StringType>
size_t strstri(const StringType& src,
               typename StringType::const_pointer needle,
               const std::locale& loc = std::locale{}) {
  using char_type = typename StringType::value_type;
  StringType src_lc{src};
  StringType needle_str{needle};
  StringType needle_lc{needle};

  transform(begin(src), end(src), begin(src_lc),
            [&](const char_type ch) { return tolower(ch, loc); });

  transform(begin(needle_str), end(needle_str), begin(needle_lc),
            [&](const char_type ch) { return tolower(ch, loc); });

  return src_lc.find(needle_lc);
}

string SimplePassword(string str) {
  str = trim(str);
  const size_t str_len{str.length()};

  if (str_len < 7 || str_len > 31)
    return "false";

  if (string::npos != strstri(str, "password"))
    return "false";

  if (!any_of(begin(str), end(str), [](const char ch) { return isupper(ch); }))
    return "false";

  if (!any_of(begin(str), end(str), [](const char ch) { return isdigit(ch); }))
    return "false";

  if (!any_of(begin(str), end(str), [](const char ch) { return ispunct(ch); }))
    return "false";

  return "true";
}

int main() {
  // cout << SimplePassword(move(string{gets(stdin)}));
  cout << SimplePassword(move(string{"apple!M7"}))
       << '\n';  // expected output: "true"
  cout << SimplePassword(move(string{"passWord123!!!!"}))
       << '\n';  // expected output: "false"
  cout << SimplePassword(move(string{"turkey90AAA="}))
       << '\n';  // expected output: "true"
  cout << SimplePassword(move(string{"!!!!!!+++++++++AMAMAM9"}))
       << '\n';  // expected output: "true"

  return 0;
}
