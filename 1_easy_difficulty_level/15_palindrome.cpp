/*
Coderbyte coding challenge: Palindrome

Using the C++ language, have the function Palindrome(str) take the str parameter being passed and return the string true if the parameter is a palindrome, 
(the string is the same forward as it is backward) otherwise return the string false. For example: "racecar" is also "racecar" backwards. 
Punctuation and numbers will not be part of the string.

Sample test cases:

Input:  "never odd or even"
Output: "true"

Input:  "eye"
Output: "true"
*/

#include <iostream>
#include <cctype>
#include <string>
#include <queue>
#include <stack>

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

string palindrome(string str) { 

   str = trim(str);
    
   stack<char> s{};
   queue<char> q{};
    
  for (const char ch : str) {
      
      if (isspace(ch)) continue;
      
      s.emplace(ch);
      q.emplace(ch);
  }
  
  while (!s.empty() && !q.empty()) {
          
          if (s.top() != q.front()) return string{"false"};
          s.pop();
          q.pop();
      }

     
  return string{"true"}; 
            
}

string palindrome2(string str) { 

  str = trim(str);

  const size_t str_len{str.length()};

  if (str_len < 2u) return string{"false"};

  for (size_t i{}, j{str_len - 1}; i < j; i++, j--) {

      if (str[i] != str[j]) return string{"false"};
  }

  return string{"true"};

}


int main() { 
  
  // cout << palindrome(move(string{gets(stdin)}));
  cout << palindrome(move(string{"racecar"})) << '\n';           // expected output: "true"
  cout << palindrome(move(string{"never odd or even"})) << '\n'; // expected output: "true"
  cout << palindrome(move(string{"eye"})) << '\n';               // expected output: "true"

  return 0;

} 
