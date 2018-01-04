/*
Coderbyte coding challenge: Time Convert

Using the C++ language, have the function TimeConvert(num) take the num parameter being passed and return the number of hours and minutes the parameter converts to 
(ie. if num = 63 then the output should be 1:3). Separate the number of hours and minutes with a colon.

Sample test cases:

Input:  126
Output: "2:6"

Input:  45
Output: "0:45"
*/

#include <iostream>
#include <string>

using namespace std;

string TimeConvert(const int num) { 

  string final{};
  
  if (num < 60) {
      
      final = "0:";
      final += std::to_string(num);
      return final;
  }
  
  int hours = num / 60;
  int minutes = num - (hours * 60);
  
  final += to_string(hours);
  final += ":";
  final += to_string(minutes);

  return final;
            
}

int main() { 

  // cout << TimeConvert(gets(stdin));
  cout << TimeConvert(120) << '\n'; // expected output: "2:0"
  cout << TimeConvert(35) << '\n';  // expected output: "0:35"
  cout << TimeConvert(256) << '\n'; // expected output: "4:16"
  return 0;
    
}
