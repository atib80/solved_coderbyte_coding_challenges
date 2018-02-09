/*
 Coderbyte coding challenge: Time Convert

 Using the C++ language, have the function TimeConvert(num) take the num
 parameter being passed and return the number of hours and minutes the parameter
 converts to (ie. if num = 63 then the output should be 1:3). Separate the
 number of hours and minutes with a colon.

 Sample test cases:

 Input:  126
 Output: "2:6"

 Input:  45
 Output: "0:45"
 */

#include <iostream>
#include <string>

using namespace std;

string TimeConvert(const size_t minutes) {

  if (minutes < 60) 
    return string{"0:"} + to_string(minutes);
  
  return to_string(minutes / 60) + string{":"} + to_string(minutes % 60);
}

int main() {
  // cout << TimeConvert(gets(stdin));
  cout << TimeConvert(120) << '\n';  // expected output: "2:0"
  cout << TimeConvert(35) << '\n';   // expected output: "0:35"
  cout << TimeConvert(256) << '\n';  // expected output: "4:16"

  return 0;
}
