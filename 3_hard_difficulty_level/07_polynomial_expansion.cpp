/*
Coderbyte coding challenge: Polynomial Expansion

Using the C++ language, have the function PolynomialExpansion(str) take str
which will be a string representing a polynomial containing only (+/-) integers,
a letter, parenthesis, and the symbol "^", and return it in expanded form.
For example: if str is "(2x^2+4)(6x^3+3)", then the output should be
"12x^5+24x^3+6x^2+12". Both the input and output should contain no spaces. The
input will only contain one letter, such as "x", "y", "b", etc. There will only
be four parenthesis in the input and your output should contain no parenthesis.
The output should be returned with the highest exponential element first down to
the lowest.

More generally, the form of str will be:
([+/-]{num}[{letter}[{^}[+/-]{num}]]...[[+/-]{num}]...)(copy) where "[]"
represents optional features,
"{}" represents mandatory features, "num" represents integers and "letter"
represents letters such as "x".

Sample test cases:

Input:  "(1x)(2x^-2+1)"
Output: "x+2x^-1"

Input:  "(-1x^3)(3x^3+2)"
Output: "-3x^6-2x^3"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
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

    if ((string::npos != max_count) && (parts.size() == max_count))
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

string clean_and_correctly_format_input_string(const string& input) {
  string output{};
  output.reserve(input.length());
  bool is_prev_char_sign_symbol{};
  bool is_number_negative{};

  for (auto ch : input) {
    if (!isspace(ch)) {
      if (('-' == ch || '+' == ch) && !is_prev_char_sign_symbol) {
        if ('-' == ch)
          is_number_negative = !is_number_negative;
        if (is_number_negative)
          output.push_back('-');
        else
          output.push_back('+');
        is_prev_char_sign_symbol = true;
        continue;
      }

      if (('-' == ch || '+' == ch) && is_prev_char_sign_symbol) {
        if ('-' == ch) {
          is_number_negative = !is_number_negative;
          if (is_number_negative)
            output.back() = '-';
          continue;
        }
      }

      ch = static_cast<char>(tolower(ch));
      output.push_back(ch);
      is_prev_char_sign_symbol = false;
      is_number_negative = false;
    }
  }

  return output;
}

// program can now accept and solve polynomial expressions of arbitrary length:
// "(2x^2+4)(6x^3+3)...(...)"
string PolynomialExpansion(string str) {
  const auto no_of_open_prnths = count(begin(str), end(str), '(');
  const auto no_of_close_prnths = count(begin(str), end(str), ')');

  if (no_of_open_prnths != no_of_close_prnths && no_of_open_prnths != 2)
    return "not possible";

  if ('(' == str.front())
    str.erase(begin(str));
  if (')' == str.back())
    str.erase(--end(str));

  const string expression_str{clean_and_correctly_format_input_string(str)};

  const vector<string> expressions_str{split(expression_str, ")(")};

  const size_t letter_pos{
      expression_str.find_first_of("abcdefghijklmnopqrstuvwxyz")};

  const char var_letter{string::npos != letter_pos ? expression_str[letter_pos]
                                                   : '\0'};

  const string expression_pattern{string{"+-0123456789"} +
                                  string(1, var_letter)};

  vector<vector<pair<int, int>>> expression_parts(expressions_str.size(),
                                                  vector<pair<int, int>>{});

  for (size_t i{}; i < expressions_str.size(); i++) {
    vector<pair<int, int>> expr_parts{};

    size_t start_pos{};

    do {
      start_pos =
          expressions_str[i].find_first_of(expression_pattern, start_pos);

      if (string::npos == start_pos)
        break;

      bool is_number_negative{false};

      if ('-' == expressions_str[i][start_pos] ||
          '+' == expressions_str[i][start_pos]) {
        while ('-' == expressions_str[i][start_pos] ||
               '+' == expressions_str[i][start_pos]) {
          if ('-' == expressions_str[i][start_pos])
            is_number_negative = !is_number_negative;
          start_pos++;
        }
      }

      size_t current_pos{start_pos};
      int multiply_factor{1};
      int exponent_factor{1};

      if (var_letter == expressions_str[i][current_pos]) {
        current_pos++;
      } else if (isdigit(expressions_str[i][start_pos])) {
        current_pos =
            expressions_str[i].find_first_not_of("0123456789", start_pos + 1);

        multiply_factor =
            stoi(expressions_str[i].substr(start_pos, current_pos - start_pos));

        if (current_pos < expressions_str[i].length() &&
            var_letter == expressions_str[i][current_pos])
          current_pos++;

        else
          exponent_factor = 0;
      }

      if (is_number_negative)
        multiply_factor = -multiply_factor;

      if (string::npos != current_pos && exponent_factor &&
          current_pos < expressions_str[i].length() - 1 &&
          '^' == expressions_str[i][current_pos]) {
        start_pos = current_pos + 1;

        bool is_exponent_negative{};

        if ('-' == expressions_str[i][start_pos] ||
            '+' == expressions_str[i][start_pos]) {
          while ('-' == expressions_str[i][start_pos] ||
                 '+' == expressions_str[i][start_pos]) {
            if ('-' == expressions_str[i][start_pos])
              is_exponent_negative = !is_exponent_negative;

            start_pos++;
          }
        }

        current_pos =
            expressions_str[i].find_first_not_of("0123456789", start_pos);

        exponent_factor =
            stoi(expressions_str[i].substr(start_pos, current_pos - start_pos));

        if (is_exponent_negative)
          exponent_factor = -exponent_factor;
      }

      expr_parts.emplace_back(make_pair(multiply_factor, exponent_factor));

      if (string::npos == current_pos)
        break;

      start_pos = current_pos;
    } while (true);

    stable_sort(begin(expr_parts), end(expr_parts),
                [](const pair<int, int>& lhs, const pair<int, int>& rhs) {
                  return lhs.second > rhs.second;
                });

    expression_parts[i] = expr_parts;
  }

  vector<pair<int, int>> result{};

  for (size_t k{}; k < expressions_str.size() - 1; k++) {
    for (size_t i{}; i < expression_parts[0].size(); i++) {
      for (size_t j{}; j < expression_parts[k + 1].size(); j++) {
        result.emplace_back(make_pair(
            expression_parts[0][i].first * expression_parts[k + 1][j].first,
            expression_parts[0][i].second + expression_parts[k + 1][j].second));
      }
    }

    swap(expression_parts[0], result);
    result.clear();
  }

  swap(result, expression_parts[0]);

  stable_sort(begin(result), end(result),
              [](const pair<int, int>& lhs, const pair<int, int>& rhs) {
                return lhs.second > rhs.second;
              });

  for (size_t i{}; i < result.size() - 1; i++) {
    for (size_t j{i + 1}; j < result.size(); j++) {
      if (result[i].second == result[j].second) {
        result[i].first += result[j].first;
        result.erase(begin(result) + j);
        j--;
      } else
        break;
    }
  }

  ostringstream oss{};

  bool is_first_number{true};

  for (const auto& p : result) {
    if (p.first) {
      if (-1 == p.first)
        oss << '-';

      else if (1 == p.first && !is_first_number)
        oss << '+';

      else if (p.first > 0 && !is_first_number)
        oss << '+' << p.first;

      else if (1 != p.first)
        oss << p.first;

      if (!p.second && (1 == p.first || -1 == p.first))
        oss << 1;

      else if (1 == p.second)
        oss << var_letter;

      else if (p.second)
        oss << var_letter << '^' << p.second;

      is_first_number = false;
    }
  }

  return oss.str();
}

int main() {
  // cout << PolynomialExpansion(move(string{gets(stdin)}));
  cout << PolynomialExpansion(move(string{"(2x^2+4)(6x^3+3)"}))
       << '\n';  // expected output: "12x^5+24x^3+6x^2+12"
  cout << PolynomialExpansion(move(string{"(-1x^3)(3x^3+2)"}))
       << '\n';  // expected output: "-3x^6-2x^3"
  cout << PolynomialExpansion(move(string{"(1x)(2x^-2+1)"}))
       << '\n';  // expected output: "x+2x^-1"

  return 0;
}
