/*
Coderbyte coding challenge: Palindrome Two

Using the C++ language, have the function PalindromeTwo(str) take the str
parameter being passed and return the string true if the parameter is a
palindrome, (the string is the same forward as it is backward) otherwise return
the string false. The parameter entered may have punctuation and symbols but
they should not affect whether the string is in fact a palindrome. For example:
"Anne, I vote more cars race Rome-to-Vienna" should return true.

Sample test cases:

Input:  "Noel - sees Leon"
Output: "true"

Input:  "A war at Tarawa!"
Output: "true"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <locale>
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

string PalindromeTwo_v1(string str, const locale& loc = locale{}) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (1 == str_len)
    return "false";

  if (2 == str_len && str[0] == str[1])
    return "true";

  ostringstream oss{};

  for (const char c : str) {
    if (isalnum(c))
      oss << static_cast<char>(tolower(c, loc));
  }

  const string str1{oss.str()};

  string str2{str1};

  reverse(begin(str2), end(str2));

  if (str1 == str2)
    return "true";

  return "false";
}

string PalindromeTwo_v2(string str, const locale& loc = locale{}) {
  str = trim(str);

  const size_t str_len{str.length()};

  if (1 == str_len)
    return "false";

  if (2 == str_len && str[0] == str[1])
    return "true";

  size_t i{}, j{str_len - 1};

  while (i < j) {
    if (!isalnum(str[i])) {
      i++;
      continue;
    }

    if (!isalnum(str[j])) {
      j--;
      continue;
    }

    if (tolower(str[i], loc) != tolower(str[j], loc))
      return "false";

    i++;
    j--;
  }

  return "true";
}

int main() {
  // cout << PalindromeTwo_v2(move(string{gets(stdin)}));
  cout << PalindromeTwo_v2(
              move(string{"Anne, I vote more cars race Rome-to-Vienna"}))
       << '\n';  // expected: "true"
  cout << PalindromeTwo_v2(move(string{"Noel - sees Leon"}))
       << '\n';  // expected: "true"
  cout << PalindromeTwo_v2(move(string{"A war at Tarawa!"}))
       << '\n';  // expected: "true"

  return 0;
}
