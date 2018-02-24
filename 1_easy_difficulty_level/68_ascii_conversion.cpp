/*
Coderbyte coding challenge: ASCII Conversion

Using the C++ language, have the function ASCIIConversion(str) take the str
parameter being passed and return a new string where every character, aside from
the space character, is replaced with its corresponding decimal character code.
For example: if str is "dog" then your program should return the string
100111103 because d = 100, o = 111, g = 103.

Sample test cases:

Input:  "hello world"
Output: "104101108108111 119111114108100"

Input:  "abc **"
Output: "979899 4242"
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
                     const char* needle = "",
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

template <typename Container>
string join(const Container& items, const string& needle = "") {
  ostringstream oss{};

  auto start = begin(items);

  const auto last = end(items);

  const size_t needle_len{needle.length()};

  while (start != last) {
    if (needle_len)
      oss << *start << needle;
    else
      oss << *start;

    ++start;
  }

  string result{oss.str()};

  if (!needle_len)
    return result;

  result.erase(result.length() - needle_len, needle_len);

  return result;
}

string ASCIIConversion_v1(string str) {
  str = trim(str);

  string result{};
  result.reserve(3 * str.length());

  char buffer[4];

  for (const char ch : str) {
    if (' ' == ch) {
      result.push_back(' ');
      continue;
    }

    sprintf(buffer, "%d", ch);

    result += buffer;
  }

  result.shrink_to_fit();
  return result;
}

string ASCIIConversion_v2(string str) {
  str = trim(str);

  ostringstream oss{};

  for (const char ch : str) {
    if (' ' == ch) {
      oss << ' ';
      continue;
    }

    oss << static_cast<int>(ch);
  }

  return oss.str();
}

string ASCIIConversion_v3(string str) {
  str = trim(str);

  vector<string> chars{split(str)};

  transform(begin(chars), end(chars), begin(chars), [](const string& ch) {
    if (" " == ch)
      return ch;
    return to_string(static_cast<int>(ch[0]));
  });

  return join(chars);
}

int main() {
  // cout << ASCIIConversion_v3(move(string{gets(stdin)}));
  cout << ASCIIConversion_v2(move(string{"dog"}))
       << '\n';  // expected output: "100111103"
  cout << ASCIIConversion_v2(move(string{"hello world"}))
       << '\n';  // expected output: "104101108108111 119111114108100"
  cout << ASCIIConversion_v2(move(string{"abc **"}))
       << '\n';  // expected output: "979899 4242"

  return 0;
}
