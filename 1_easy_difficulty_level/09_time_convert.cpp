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

#include <array>
#include <iostream>
#include <utility>

template <typename CharType, size_t BUFFER_LENGTH>
class Solution {
  mutable std::array<CharType, BUFFER_LENGTH> buffer;

 public:
  constexpr Solution() : buffer{} {}

  constexpr const CharType* TimeConvert(size_t minutes) const {
    size_t hours{minutes / 60}, index{};
    minutes %= 60;

    if (0u == minutes)

      buffer[index++] = static_cast<CharType>('0');

    else {
      while (minutes > 0) {
        buffer[index++] = static_cast<CharType>('0') + minutes % 10;
        minutes /= 10;
      }
    }

    buffer[index++] = static_cast<CharType>(':');

    if (0u == hours)

      buffer[index++] = static_cast<CharType>('0');

    else {
      while (hours > 0) {
        buffer[index++] = static_cast<CharType>('0') + hours % 10;
        hours /= 10;
      }
    }

    buffer[index] = static_cast<CharType>('\0');

    for (size_t i{}, j{index - 1}; i < j; ++i, --j)
      std::swap(buffer[i], buffer[j]);

    return buffer.data();
  }
};

int main() {
  constexpr static Solution<char, 16> s{};

  // cout << s.TimeConvert(gets(stdin));
  std::cout << s.TimeConvert(120) << '\n';  // expected output: "2:0"
  std::cout << s.TimeConvert(35) << '\n';   // expected output: "0:35"
  std::cout << s.TimeConvert(256) << '\n';  // expected output: "4:16"
  std::cout << s.TimeConvert(308) << '\n';  // expected output: "5:08"
  std::cout << s.TimeConvert(935) << '\n';  // expected output: "15:35"

  return 0;
}
