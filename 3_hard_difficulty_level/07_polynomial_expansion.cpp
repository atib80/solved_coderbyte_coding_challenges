/*
Coderbyte coding challenge: Polynomial Expansion

Using the C++ language, have the function PolynomialExpansion(str) take str which will be a string representing a polynomial containing only (+/-) integers,
a letter, parenthesis, and the symbol "^", and return it in expanded form.
For example: if str is "(2x^2+4)(6x^3+3)", then the output should be "12x^5+24x^3+6x^2+12". Both the input and output should contain no spaces.
The input will only contain one letter, such as "x", "y", "b", etc. There will only be four parenthesis in the input and your output should contain no parenthesis.
The output should be returned with the highest exponential element first down to the lowest.

More generally, the form of str will be: ([+/-]{num}[{letter}[{^}[+/-]{num}]]...[[+/-]{num}]...)(copy) where "[]" represents optional features,
"{}" represents mandatory features, "num" represents integers and "letter" represents letters such as "x".

Sample test cases:

Input:  "(1x)(2x^-2+1)"
Output: "x+2x^-1"

Input:  "(-1x^3)(3x^3+2)"
Output: "-3x^6-2x^3"
*/

#include <iostream>
#include <sstream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string trim(const string& str)
{
  const size_t str_len{str.length()};

  if (!str_len) return string{};

  size_t first{}, last{str_len - 1};

  for (; first <= last; ++first)
  {
    if (!isspace(str[first])) break;
  }

  if (first > last) return string{};

  for (; last > first; --last)
  {
    if (!isspace(str[last])) break;
  }

  return str.substr(first, last - first + 1);
}

vector<string> split(const string& source, const char* needle, size_t const max_count = string::npos)
{
  vector<string> parts{};

  string needle_st{needle};

  const size_t source_len{source.length()};

  const size_t needle_len{needle_st.size()};

  if ((0u == source_len) || (0u == needle_len)) return parts;

  size_t number_of_parts{}, prev{};

  while (true)
  {
    const size_t current{source.find(needle_st, prev)};

    if (string::npos == current) break;

    number_of_parts++;

    if ((string::npos != max_count) && (parts.size() == max_count)) break;

    if ((current - prev) > 0) parts.emplace_back(source.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len) break;
  }

  if (prev < source_len)
  {
    if (string::npos == max_count) parts.emplace_back(source.substr(prev));

    else if ((string::npos != max_count) && (parts.size() < max_count)) parts.emplace_back(source.substr(prev));
  }

  return parts;
}

string clean_and_correctly_format_input_string(const string& input)
{
  string output{};
  output.reserve(input.length());
  bool is_prev_char_sign_symbol{};
  bool is_number_negative{};

  for (auto ch : input)
  {
    if (!isspace(ch))
    {
      if ((('-' == ch) || ('+' == ch)) && !is_prev_char_sign_symbol)
      {
        if ('-' == ch) is_number_negative = !is_number_negative;
        if (is_number_negative) output.push_back('-');
        else output.push_back('+');
        is_prev_char_sign_symbol = true;
        continue;
      }

      if ((('-' == ch) || ('+' == ch)) && is_prev_char_sign_symbol)
      {
        if ('-' == ch)
        {
          is_number_negative = !is_number_negative;
          if (is_number_negative) output.back() = '-';
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

// input: "(2x^2+4)(6x^3+3)"

string PolynomialExpansion(string str)
{
  str = trim(str);

  const auto no_of_open_prnths = count(begin(str), end(str), '(');
  const auto no_of_close_prnths = count(begin(str), end(str), ')');

  if ((no_of_open_prnths != no_of_close_prnths) && (no_of_open_prnths != 2)) return "not possible";

  if ('(' == str.front()) str.erase(begin(str));
  if (')' == str.back()) str.erase(--end(str));

  string expression_str{clean_and_correctly_format_input_string(str)};

  vector<string> expressions_str{split(expression_str, ")(")};

  if (2 != expressions_str.size()) return "not possible";

  const size_t letter_pos{expression_str.find_first_of("abcdefghijklmnopqrstuvwxyz")};

  const char var_letter{string::npos != letter_pos ? expression_str[letter_pos] : '\0'};

  const string expression_pattern{string{"+-0123456789"} + string(1, var_letter)};

  vector<vector<pair<int, int>>> expression_parts(2u, vector<pair<int, int>>{});

  for (size_t i{}; i != 2u; i++)
  {
    vector<pair<int, int>> expr_parts{};

    size_t start_pos{};

    do
    {
      start_pos = expressions_str[i].find_first_of(expression_pattern, start_pos);

      if (string::npos == start_pos) break;

      bool is_number_negative{false};

      if ('-' == expressions_str[i][start_pos] || '+' == expressions_str[i][start_pos])
      {
        while (('-' == expressions_str[i][start_pos]) || ('+' == expressions_str[i][start_pos]))
        {
          if ('-' == expressions_str[i][start_pos]) is_number_negative = !is_number_negative;

          start_pos++;
        }
      }

      size_t current_pos{start_pos};
      int multiply_factor{1};
      int exponent_factor{1};

      if (var_letter == expressions_str[i][current_pos])
      {
        current_pos++;
      }
      else if (isdigit(expressions_str[i][start_pos]))
      {
        current_pos = expressions_str[i].find_first_not_of("0123456789", start_pos + 1);

        multiply_factor = stoi(expressions_str[i].substr(start_pos, current_pos - start_pos));

        if ((current_pos < expressions_str[i].length()) && (var_letter == expressions_str[i][current_pos])) current_pos++;

        else exponent_factor = 0;
      }

      if (is_number_negative) multiply_factor = -multiply_factor;

      if ((string::npos != current_pos) && exponent_factor && (current_pos < expressions_str[i].length() - 1) && ('^' ==
        expressions_str[i][current_pos]))
      {
        start_pos = current_pos + 1;

        bool is_exponent_negative{};

        if ('-' == expressions_str[i][start_pos] || '+' == expressions_str[i][start_pos])
        {
          while (('-' == expressions_str[i][start_pos]) || ('+' == expressions_str[i][start_pos]))
          {
            if ('-' == expressions_str[i][start_pos]) is_exponent_negative = !is_exponent_negative;

            start_pos++;
          }
        }

        current_pos = expressions_str[i].find_first_not_of("0123456789", start_pos);

        exponent_factor = stoi(expressions_str[i].substr(start_pos, current_pos - start_pos));

        if (is_exponent_negative) exponent_factor = -exponent_factor;
      }

      expr_parts.emplace_back(make_pair(multiply_factor, exponent_factor));

      if (string::npos == current_pos) break;

      start_pos = current_pos;
    }
    while (true);

    stable_sort(begin(expr_parts), end(expr_parts), [](const pair<int, int>& lhs, const pair<int, int>& rhs)
    {
      return (lhs.second > rhs.second);
    });

    expression_parts[i] = expr_parts;
  }

  vector<pair<int, int>> result{};

  for (size_t i{}; i < expression_parts[0].size(); i++)
  {
    for (size_t j{}; j < expression_parts[1].size(); j++)
    {
      result.emplace_back(make_pair(expression_parts[0][i].first * expression_parts[1][j].first,
                                    expression_parts[0][i].second + expression_parts[1][j].second));
    }
  }

  stable_sort(begin(result), end(result), [](const pair<int, int>& lhs, const pair<int, int>& rhs)
  {
    return (lhs.second > rhs.second);
  });


  for (size_t i{}; i < result.size() - 1; i++)
  {
    for (size_t j{i + 1}; j < result.size(); j++)
    {
      if (result[i].second == result[j].second)
      {
        result[i].first += result[j].first;
        result.erase(begin(result) + j);
        j--;
        continue;
      }

      break;
    }
  }

  ostringstream oss{};

  bool is_first_number{true};

  for (const auto& p : result)
  {
    if (p.first)
    {
      if (-1 == p.first) oss << '-';

      else if ((1 == p.first) && !is_first_number) oss << '+';

      else if ((p.first > 0) && !is_first_number) oss << '+' << p.first;

      else if (1 != p.first) oss << p.first;

      if (!p.second && (1 == p.first || -1 == p.first)) oss << 1;

      else if (1 == p.second) oss << var_letter;

      else if (p.second) oss << var_letter << '^' << p.second;

      is_first_number = false;
    }
  }

  return oss.str();
}

int main()
{
  // cout << PolynomialExpansion(move(string{gets(stdin)}));

  // PolynomialExpansion(move(string{"(2x^2+4)(6x^3+3)"})) -> move(string{"..."}) is unnecessary in this case and should not be used 
  // as it prevents C++ compiler's copy elision optimization feature
  // PolynomialExpansion(string{"(2x^2+4)(6x^3+3)"}) is a more optimally, correct way of calling PolynomialExpansion without using move(...) explicitly

  cout << PolynomialExpansion(string{"(2x^2+4)(6x^3+3)"}) << '\n'; // expected output: "12x^5+24x^3+6x^2+12" 
  cout << PolynomialExpansion(string{"(-1x^3)(3x^3+2)"}) << '\n';  // expected output: "-3x^6-2x^3"  
  cout << PolynomialExpansion(string{"(1x)(2x^-2+1)"}) << '\n';    // expected output: "x+2x^-1"

  return 0;
}
