/*
Coderbyte coding challenge: Linear Congruence

Using the C++ language, have the function LinearCongruence(str) read the str
parameter being passed which will be a linear congruence equation in the form:
"ax = b (mod m)" Your goal is to solve for x and return the number of solutions
to x. For example: if str is "32x = 8 (mod 4)" then your program should return 4
because the answers to this equation can be either 0, 1, 2, or 3.

Sample test cases:

Input:  "12x = 5 (mod 2)"
Output: 0

Input:  "12x = 4 (mod 2)"
Output: 2
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

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

string LinearCongruence(string str) {
  str = trim(str);

  int x{stoi(str.substr(0, str.find('x')))};

  size_t sep_pos{str.find('=')};

  if (string::npos == sep_pos)
    return "not possible";

  size_t second_number_start_pos{str.find_first_of("1234567890", sep_pos + 1)};

  if (string::npos == second_number_start_pos)
    return "not possible";

  sep_pos = str.find_first_not_of("1234567890", second_number_start_pos + 1);

  if (string::npos == sep_pos)
    return "not possible";

  const int y{stoi(
      str.substr(second_number_start_pos, sep_pos - second_number_start_pos))};

  size_t m_start{str.rfind("mod")};

  m_start = str.find_first_of("1234567890", m_start + 3);

  const size_t m_end{str.find_first_not_of("1234567890", m_start)};

  int m{stoi(str.substr(m_start, m_end - m_start))};

  while (m) {
    const int temp{m};
    m = x % m;
    x = temp;
  }

  if (y % x == 0)
    return to_string(x);

  return "0";
}

int main() {
  // cout << LinearCongruence(gets(stdin));
  cout << LinearCongruence(move(string{"32x = 8 (mod 4)"}))
       << '\n';  // expected output: 4
  cout << LinearCongruence(move(string{"12x = 5 (mod 2)"}))
       << '\n';  // expected output: 0
  cout << LinearCongruence(move(string{"12x = 4 (mod 2)"}))
       << '\n';  // expected output: 2

  return 0;
}
