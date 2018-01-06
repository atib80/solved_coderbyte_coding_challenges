/*
Coderbyte coding challenge: Distinct Characters

Using the C++ language, have the function DistinctCharacters(str) take the str parameter being passed and determine if it contains at least 10 distinct characters, 
if so, then your program should return the string true, otherwise it should return the string false. For example: if str is "abc123kkmmmm?" 
then your program should return the string false because this string contains only 9 distinct characters: a, b, c, 1, 2, 3, k, m, ? adds up to 9.

Sample test cases:

Input:  "12334bbmma:=6"
Output: "true"

Input:  "eeeemmmmmmmmm1000"
Output: "false"
*/

#include <iostream>
#include <cctype>
#include <string>
#include <unordered_set>

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

string DistinctCharacters(string str) {

  str = trim(str);

  unordered_set<char> distinct_characters{};

  for (const char ch : str) {

  	distinct_characters.insert(ch);

    if (distinct_characters.size() >= 10u) return string{"true"};

  }  

  return string{"false"};            

}

int main() {

  // cout << DistinctCharacters(move(string{gets(stdin)}));
  cout << DistinctCharacters(move(string{"abc123kkmmmm?"})) << '\n';     // expected output: "false"
  cout << DistinctCharacters(move(string{"12334bbmma:=6"})) << '\n';     // expected output: "true"
  cout << DistinctCharacters(move(string{"eeeemmmmmmmmm1000"})) << '\n'; // expected output: "false"  
  return 0;    
}
