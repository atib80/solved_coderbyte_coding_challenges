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

#include <algorithm>
#include <array>
// #include <iostream>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <utility>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

using namespace std;

string TimeConvert(uint64_t minutes) {
  uint64_t hours{minutes / 60};
  minutes %= 60;
  string result;

  if (0 == minutes) {
    result.push_back('0');
  } else {
    while (minutes > 0) {
      result.push_back('0' + minutes % 10);
      minutes /= 10;
    }
  }

  result.push_back(':');

  if (0 == hours) {
    result.push_back('0');
  } else {
    while (hours > 0) {
      result.push_back('0' + hours % 10);
      hours /= 10;
    }
  }

  reverse(begin(result), end(result));

  return result;
}

TEST_CASE("Time Convert") {
  REQUIRE(TimeConvert(120) == "2:0");
  REQUIRE(TimeConvert(35) == "0:35");
  REQUIRE(TimeConvert(256) == "4:16");
  REQUIRE(TimeConvert(308) == "5:8");
  REQUIRE(TimeConvert(935) == "15:35");
}

// int main() {
//   constexpr static Solution<char, 16> s{};

//   // cout << s.TimeConvert(gets(stdin));
//   std::cout << s.TimeConvert(120) << '\n';  // expected output: "2:0"
//   std::cout << s.TimeConvert(35) << '\n';   // expected output: "0:35"
//   std::cout << s.TimeConvert(256) << '\n';  // expected output: "4:16"
//   std::cout << s.TimeConvert(308) << '\n';  // expected output: "5:8"
//   std::cout << s.TimeConvert(935) << '\n';  // expected output: "15:35"

//   return 0;
// }
