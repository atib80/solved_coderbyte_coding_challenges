/*
Coderbyte coding challenge: Formatted Number

Using the C++ language, have the function FormattedNumber(strArr) take the
strArr parameter being passed, which will only contain a single element, and
return the string true if it is a valid number that contains only digits with
properly placed decimals and commas, otherwise return the string false. For
example: if strArr is ["1,093,222.04"] then your program should return the
string true, but if the input were ["1,093,22.04"] then your program should
return the string false. The input may contain characters other than digits.

Sample test cases:

Input:  "0.232567"
Output: "true"

Input:  "2,567.00.2"
Output: "false"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string trim(const string& input) {
  string output{input};
  output.erase(begin(output),
               find_if(begin(output), end(output),
                       [](const char ch) { return !isspace(ch); }));

  output.erase(find_if(output.rbegin(), output.rend(),
                       [](const char ch) { return !isspace(ch); })
                   .base(),
               end(output));

  return output;
}

vector<string> split(const string& source,
                     const char* needle,
                     size_t const max_count = string::npos) {
  vector<string> parts{};

  string needle_st{needle};

  const size_t source_len{source.length()};

  const size_t needle_len{needle_st.length()};

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

    if (string::npos != max_count && parts.size() == max_count)
      break;

    if (current - prev > 0)
      parts.emplace_back(source.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (prev < source_len) {
    if (string::npos == max_count)
      parts.emplace_back(source.substr(prev));

    else if (parts.size() < max_count)
      parts.emplace_back(source.substr(prev));
  }

  return parts;
}

string FormattedNumber(string* str_arr) {
  *str_arr = trim(*str_arr);

  const auto number_of_dots = count(begin(*str_arr), end(*str_arr), '.');

  if (number_of_dots > 1)
    return "false";

  const size_t dot_pos{str_arr->find('.')};

  if (string::npos != dot_pos &&
      (dot_pos == str_arr->length() - 1 ||
       str_arr->find_first_of("0123456789", dot_pos + 1) != dot_pos + 1))
    return "false";

  const size_t scientific_sign_pos{str_arr->find_first_of("eE")};

  const size_t sign_pos{str_arr->find_first_of("+-")};

  if (string::npos == scientific_sign_pos && string::npos != sign_pos &&
      0 != sign_pos)
    return "false";

  if (scientific_sign_pos == str_arr->length() - 1 ||
      str_arr->find_first_of("+-0123456789", scientific_sign_pos + 1) !=
          scientific_sign_pos + 1)
    return "false";

  if (str_arr->find_first_of("+-", scientific_sign_pos + 1) ==
          scientific_sign_pos + 1 &&
      (str_arr[0][scientific_sign_pos + 2] < '0' ||
       str_arr[0][scientific_sign_pos + 2] > '9'))
    return "false";

  if (string::npos != str_arr->find_first_not_of("1234567890,.+-eE"))
    return "false";

  const auto number_of_commas = count(begin(*str_arr), end(*str_arr), ',');

  const size_t whole_number_part_len{string::npos != dot_pos
                                         ? dot_pos
                                         : scientific_sign_pos != string::npos
                                               ? scientific_sign_pos
                                               : str_arr->length()};

  if (number_of_commas != 0) {
    const string whole_number_part{str_arr->substr(0, whole_number_part_len)};

    const vector<string> number_parts{split(whole_number_part, ",")};

    for (size_t i{number_parts.size() - 1}; i > 0; i--) {
      if (3 != number_parts[i].length())
        return "false";
    }

  } else if (whole_number_part_len > 3)
    return "false";

  return "true";
}

int main() {
  // string A[] = gets(stdin);
  // cout << FormattedNumber(A);
  string B[] = {"1,093,222.04"};
  cout << FormattedNumber(B) << '\n';  // expected output: "true"
  string C[] = {"1,093,22.04"};
  cout << FormattedNumber(C) << '\n';  // expected output: "false"
  string D[] = {"0.232567"};
  cout << FormattedNumber(D) << '\n';  // expected output: "true"
  string E[] = {"2,567.00.2"};
  cout << FormattedNumber(E) << '\n';  // expected output: "false"
  string F[] = {"898989898"};
  cout << FormattedNumber(F) << '\n';  // expected output: "false"

  return 0;
}
