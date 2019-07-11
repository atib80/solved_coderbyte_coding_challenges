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

std::string TimeConvert(size_t minutes) {
  if (minutes < 60) {
    static char buffer[5]{"0:"};
    if (minutes < 10) {
      buffer[2] = '0' + minutes;
      buffer[3] = 0;
      return buffer;
    }

    buffer[2] = '0' + minutes / 10;
    minutes %= 10;
    buffer[3] = '0' + minutes;
    buffer[4] = 0;
    return buffer;
  }

  return std::to_string(minutes / 60) + ":" + std::to_string(minutes % 60);
}

int main() {
  // cout << TimeConvert(gets(stdin));
  std::cout << TimeConvert(120) << '\n';  // expected output: "2:0"
  std::cout << TimeConvert(35) << '\n';   // expected output: "0:35"
  std::cout << TimeConvert(256) << '\n';  // expected output: "4:16"

  return 0;
}
