/*
Coderbyte coding challenge: Dash Insert

Using the C++ language, have the function DashInsert(str) insert dashes ('-') between each two odd numbers in str. 
For example: if str is 454793 the output should be 4547-9-3. Don't count zero as an odd number.

Sample test cases:

Input:  99946
Output: 9-9-946

Input:  56730
Output: 567-30
*/

#include <iostream>
#include <cctype>
#include <string>

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

string DashInsert(string str) {

  str = trim(str); 

  const size_t str_len { str.length() };

  if (str_len < 2u) return str;

  string result(1, str.front());
  result.reserve(2 * str_len); // 2 * str_len - 1

  int digit { static_cast<int>(str.front() - '0') };

  bool is_prev_odd { digit % 2 == 1 ? true : false };

  for (size_t i{1u}; i != str_len; i++) {

    if (is_prev_odd && (str[i] % 2 == 1)) {

      result.push_back('-');
      result.push_back(str[i]);
      continue;     
    }

    result.push_back(str[i]);

    is_prev_odd = str[i] % 2 == 1 ? true : false;

  }

  return result; 
            
}

int main() { 
  
  cout << DashInsert(move(string{gets(stdin)}));
  // cout << DashInsert(move(string{"454793"})) << '\n'; // expected output: 4547-9-3
  // cout << DashInsert(move(string{"99946"}))  << '\n'; // expected output: 9-9-946
  // cout << DashInsert(move(string{"56730"}))  << '\n'; // expected output: 567-30
  return 0;

}
