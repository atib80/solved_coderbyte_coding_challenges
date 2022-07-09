/*
Coderbyte coding challenge: Check Nums

Using the C++ language, have the function CheckNums(num1,num2) take both
parameters being passed and return the string true if num2 is greater than num1,
otherwise return the string false. If the parameter values are equal to each
other then return the string -1.

Sample test cases:

Input:  3 & num2 = 122
Output: "true"

Input:  67 & num2 = 67
Output: "-1"

Input:  83 & num2 = 67
Output: "false"
*/

#include <cmath>
// #include <iostream>
#include <string>
#include <unordered_map>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

using namespace std;

string CheckNums_v1(const int num1, const int num2) {
  if (num1 == num2)
    return "-1";
  return num2 > num1 ? "true" : "false";
}

string CheckNums_v2(const int num1, const int num2) {
  static constexpr const char* dict[3]{"true", "-1", "false"};

  const int diff{num1 - num2};
  const int abs_diff{abs(diff)};
  const int key{1 + diff / (0 != abs_diff ? abs_diff : 1)};
  return dict[key];
}

TEST_CASE("Check Nums: CheckNums_v1") {
  REQUIRE(CheckNums_v1(3, 122) == "true");
  REQUIRE(CheckNums_v1(67, 67) == "-1");
  REQUIRE(CheckNums_v1(35, 17) == "false");
}

TEST_CASE("Check Nums: CheckNums_v2") {
  REQUIRE(CheckNums_v2(3, 122) == "true");
  REQUIRE(CheckNums_v2(67, 67) == "-1");
  REQUIRE(CheckNums_v2(35, 17) == "false");
}

// int main() {
//   // cout << CheckNums_v2(gets(stdin));
//   cout << CheckNums_v2(3, 122) << '\n';  // expected output: "true"
//   cout << CheckNums_v2(67, 67) << '\n';  // expected output: "-1"
//   cout << CheckNums_v2(35, 17) << '\n';  // expected output: "false"

//   return 0;
// }
