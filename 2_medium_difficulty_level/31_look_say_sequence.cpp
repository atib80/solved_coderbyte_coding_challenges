/*
Coderbyte coding challenge: Look Say Sequence

Using the C++ language, have the function LookSaySequence(num) take the num parameter being passed and return the next number 
in the sequence according to the following rule: to generate the next number in a sequence read off the digits of the given number, 
counting the number of digits in groups of the same digit. For example, the sequence beginning with 1 would be: 1, 11, 21, 1211, ... 
The 11 comes from there being "one 1" before it and the 21 comes from there being "two 1's" before it. 
So your program should return the next number in the sequence given num.

Sample test cases:

Input:  1211
Output: 111221

Input:  2466
Output: 121426
*/

#include <iostream>
#include <string>

using namespace std;

string LookSaySequence(const int num) {

  string num_str { to_string(num) };

  string result_num{};
  char buffer[32];
  
  for(size_t i{}; i != num_str.length(); i++)
  {

    size_t count{1u};

    while ((i != num_str.length()) && (num_str[i] == num_str[i + 1]))
    {
      count++;
      i++;
    }

    sprintf(buffer, "%lu%c", count, num_str[i]);    
    result_num += buffer;
    
  }
  
  return result_num;            
}

int main() { 
  
  // cout << LookSaySequence(gets(stdin));
  cout << LookSaySequence(1211) << '\n'; // expected output: 111221
  cout << LookSaySequence(2466) << '\n'; // expected output: 121426

  return 0;    
}
