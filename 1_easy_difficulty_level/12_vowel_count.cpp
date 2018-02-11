/*
Coderbyte coding challenge: Vowel Count

Using the C++ language, have the function VowelCount(str) take the str string parameter being passed and return the number of vowels the string contains 
(ie. "All cows eat grass and moo" would return 8). Do not count y as a vowel for this challenge.

Sample test cases:

Input:  "hello"
Output: 2

Input:  "coderbyte"
Output: 3
*/

#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (0u == str.length())
    return string{};

  size_t begin_str{};
  size_t end_str{str_len - 1};

  for (; begin_str <= end_str; ++begin_str) {
    if (!isspace(str[begin_str]))
      break;
  }

  if (begin_str > end_str)
    return string{};

  for (; end_str > begin_str; --end_str) {
    if (!isspace(str[end_str]))
      break;
  }

  return str.substr(begin_str, end_str - begin_str + 1);
}

string vowel_count(string str) { 
    
    const unordered_set<char> vowels{'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'};    
    
    size_t v_count{};

    str = trim(str);
    
    for (const auto ch : str) {
        if (vowels.find(ch) != end(vowels)) v_count++;
    }
   
  return to_string(v_count); 
            
}

int main() { 

  // cout << vowel_count(gets(stdin));  
  cout << vowel_count(move(string{"All cows eat grass and moo"})) << '\n'; // expected output: 8
  cout << vowel_count(move(string{"hello"})) << '\n';                      // expected output: 2
  cout << vowel_count(move(string{"coderbyte"})) << '\n';                  // expected output: 3
  
  return 0;    
} 
