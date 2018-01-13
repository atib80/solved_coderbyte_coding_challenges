/*
Coderbyte coding challenge: Pattern Chaser

Using the C++ language, have the function PatternChaser(str) take str which will be a string and return the longest pattern within the string. 
A pattern for this challenge will be defined as: if at least 2 or more adjacent characters within the string repeat at least twice. 
So for example "aabecaa" contains the pattern aa, on the other hand "abbbaac" doesn't contain any pattern. 
Your program should return yes/no pattern/null. 
So if str were "aabejiabkfabed" the output should be "yes abe". 
If str were "123224" the output should return "no null". 
The string may either contain all characters (a through z only), integers, or both. 
But the parameter will always be a string type. 
The maximum length for the string being passed in will be 20 characters. 
If a string for example is "aa2bbbaacbbb" the pattern is "bbb" and not "aa". 
You must always return the longest pattern possible.

Hard challenges are worth 15 points and you are not timed for them.

Sample test cases:

Input:  "da2kr32a2"
Output: "yes a2"

Input:  "sskfssbbb9bbb"
Output: "yes bbb"
*/

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string trim(const string& str)
{
  const size_t str_len{ str.length() };

  if (!str_len) return string{};

  size_t first{}, last{ str_len - 1 };

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

bool check_current_string_pattern(const string& src_str, const string& current_pattern, const size_t current_pattern_start_index) {

   const size_t str_len { src_str.length() };
   const size_t current_pattern_size { current_pattern.length() };

   size_t current_pattern_count { 1u };

   size_t i { current_pattern_start_index };

   while ((i + current_pattern_size) < str_len) {

      i += current_pattern_size;

      const size_t pos { src_str.find(current_pattern, i) };

      if (pos == string::npos) {
        
        if (current_pattern_count > 1u) return true;        

        break;
      }

      i = pos;

      current_pattern_count++;

    }

    if (current_pattern_count > 1u) return true; 

    return false;
}

string pattern_chaser(string str) { 

   str = trim(str);

   const size_t str_len { str.length() };

   if (str_len < 3u) return "no null";

   size_t current_pattern_size { str_len / 2u };

   size_t current_pattern_start_index { 0u };
   
   while (current_pattern_size != 1u) {

      if ((current_pattern_start_index + (2 * current_pattern_size)) > str_len) {       

        current_pattern_size--;

        if (current_pattern_size < 2u) return string{"no null"};

        current_pattern_start_index = 0u;

      }

     const string current_pattern { str.substr(current_pattern_start_index, current_pattern_size) };

     if (check_current_string_pattern(str, current_pattern, current_pattern_start_index)) {

         return string { "yes " + current_pattern };

     }
     
     current_pattern_start_index++;

    }
  
  return "no null";

}

int main() { 
  
  // cout << pattern_chaser(move(string{gets(stdin)}));
  cout << pattern_chaser(move(string{"aabecaa"})) << '\n';        // expected output: "yes aa"
  cout << pattern_chaser(move(string{"abbbaac"})) << '\n';        // expected output: "no null"
  cout << pattern_chaser(move(string{"aabejiabkfabed"})) << '\n'; // expected output: "yes abe"
  cout << pattern_chaser(move(string{"123224"})) << '\n';         // expected output: "no null"
  cout << pattern_chaser(move(string{"aa2bbbaacbbb"})) << '\n';   // expected output: "yes bbb"
  cout << pattern_chaser(move(string{"da2kr32a2"})) << '\n';      // expected output: "yes a2"
  cout << pattern_chaser(move(string{"sskfssbbb9bbb"})) << '\n';  // expected output: "yes bbb"

  return 0;
}
