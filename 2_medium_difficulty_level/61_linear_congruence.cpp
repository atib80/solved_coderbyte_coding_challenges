/*
Coderbyte coding challenge: Linear Congruence

Using the C++ language, have the function LinearCongruence(str) read the str parameter being passed which will be a linear congruence equation in the form: 
"ax = b (mod m)" Your goal is to solve for x and return the number of solutions to x. For example: if str is "32x = 8 (mod 4)" then your program should return 4 
because the answers to this equation can be either 0, 1, 2, or 3.

Sample test cases:

Input:  "12x = 5 (mod 2)"
Output: 0

Input:  "12x = 4 (mod 2)"
Output: 2
*/

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string trim(const string& str)
{
  size_t begin_str{};
  size_t end_str{str.size() - 1};

  if (0u == str.length()) return string{};

  for (; begin_str <= end_str; ++begin_str)
  {
    if (!isspace(str[begin_str])) break;
  }

  if (begin_str > end_str) return string{};

  for (; end_str > begin_str; --end_str)
  {
    if (!isspace(str[end_str])) break;
  }

  return str.substr(begin_str, end_str - begin_str + 1);
}

string LinearCongruence(string str) {  

  str = trim(str);

  int x { stoi(str.substr(0, str.find('x'))) };

  size_t sep_pos { str.find('=') };

  if (string::npos == sep_pos) return string{"Not possible!"};

  size_t second_number_start_pos { str.find_first_of("1234567890", sep_pos + 1) };

  if (string::npos == second_number_start_pos) return string{"Not possible!"};

  sep_pos = str.find_first_not_of("1234567890", second_number_start_pos + 1);

  if (string::npos == sep_pos) return string{"Not possible!"};

  const int y { stoi(str.substr(second_number_start_pos, sep_pos - second_number_start_pos)) };

  str.erase(--end(str));

  sep_pos = str.rfind(' ');

  sep_pos++;

  int m { stoi(str.substr(sep_pos)) };

  while (m) {

  	const int temp {m};
  	m = x % m;
  	x = temp;

  }

  if (y % x == 0) return to_string(x);

  return string{"0"};
}

int main() { 
  
  // cout << LinearCongruence(gets(stdin));
  cout << LinearCongruence(move(string{"32x = 8 (mod 4)"})) << '\n'; // expected output: 4
  cout << LinearCongruence(move(string{"12x = 5 (mod 2)"})) << '\n'; // expected output: 0
  cout << LinearCongruence(move(string{"12x = 4 (mod 2)"})) << '\n'; // expected output: 2

  return 0;      
} 
