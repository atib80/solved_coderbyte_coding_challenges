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

class Solution {
  static constexpr const size_t buf_len{16};
  mutable char buffer[buf_len];

 public:
  constexpr Solution() : buffer{} {}

  constexpr const char* TimeConvert(size_t minutes) const {
    if (minutes < 60) {
      buffer[0] = '0';
      buffer[1] = ':';

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

    size_t hours{minutes / 60}, index{buf_len - 1};
    minutes %= 60;

    while (hours > 0) {
      buffer[index--] = '0' + hours % 10;
      hours /= 10;
    }

    for (size_t i{}, j{index + 1}; j < buf_len; ++i, ++j) {
      buffer[i] = buffer[j];
      index = i;
    }

    buffer[++index] = ':';

    size_t offset = minutes > 9 ? 2 : 1;

    buffer[index + offset + 1] = 0;

    buffer[index + offset] = '0' + minutes % 10;
    minutes /= 10;
    --offset;
    if (minutes > 0)
      buffer[index + offset] = '0' + minutes;

    return buffer;
  }
};

int main() {
  constexpr static Solution s{};

  // cout << s.TimeConvert(gets(stdin));
  std::cout << s.TimeConvert(120) << '\n';  // expected output: "2:0"
  std::cout << s.TimeConvert(35) << '\n';   // expected output: "0:35"
  std::cout << s.TimeConvert(256) << '\n';  // expected output: "4:16"
  std::cout << s.TimeConvert(308) << '\n';  // expected output: "5:08"
  std::cout << s.TimeConvert(935) << '\n';  // expected output: "15:35"

  return 0;
}
