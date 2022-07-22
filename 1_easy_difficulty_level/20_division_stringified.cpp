/*
Coderbyte coding challenge: Division Stringified

Using the C++ language, have the function DivisionStringified(num1,num2) take
both parameters being passed, divide num1 by num2, and return the result as a
string with properly formatted commas. If an answer is only 3 digits long,
return the number with no commas (ie. 2 / 3 should output "1"). For example: if
num1 is 123456789 and num2 is 10000 the output should be "12,346".

Sample test cases:

Input:  5 & num2 = 2
Output: "3"

Input:  6874 & num2 = 67
Output: "103"
*/

#include <cmath>
#include <cstdint>
// #include <iostream>
#include <cstring>
#include <stdexcept>
#include <string>

#include <stl_helper_functions.hpp>

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

using namespace std;

string division_stringified_v1(const int64_t numerator,
                               const int64_t denumerator) {
  constexpr static size_t buffer_size{32U};
  char buffer[buffer_size];

  if (0 == denumerator)
    return "Not possible!";
  int64_t whole_part{static_cast<int64_t>(
      round(static_cast<double>(numerator) / denumerator))};

  const bool is_negative{whole_part < 0};
  if (is_negative)
    whole_part = abs(whole_part);

  size_t j{buffer_size - 1}, digit_count{1};
  buffer[j] = 0;

  while (true) {
    buffer[--j] = static_cast<char>('0' + whole_part % 10);
    whole_part /= 10;

    if (0 == whole_part)
      break;

    if (0U == digit_count % 3)
      buffer[--j] = ',';

    ++digit_count;
  }

  if (is_negative)
    buffer[--j] = '-';

  return buffer + j;
}

class division_stringified_v2 {
  static constexpr const size_t buffer_size{32U};
  char buffer[buffer_size];
  size_t offset;

 public:
  constexpr division_stringified_v2(const int64_t numerator,
                                    const int64_t denumerator)
      : buffer{}, offset{buffer_size - 1} {
    if (0 == denumerator)
      throw runtime_error{"Cannot divide a number by 0!"};

    const double result{static_cast<double>(numerator) / denumerator};
    int64_t whole_part{static_cast<int64_t>(result)};

    if (whole_part > 0) {
      if (result - whole_part >= 0.5)
        ++whole_part;
    } else if (whole_part < 0) {
      if (result - whole_part <= -0.5)
        --whole_part;
    } else {
      buffer[--offset] = '0';
      return;
    }

    const bool is_negative{result < 0};
    if (is_negative)
      whole_part = -whole_part;

    size_t digit_count{1};

    while (true) {
      buffer[--offset] = static_cast<char>('0' + whole_part % 10);
      whole_part /= 10;

      if (0 == whole_part)
        break;

      if (0U == digit_count % 3)
        buffer[--offset] = ',';

      ++digit_count;
    }

    if (is_negative)
      buffer[--offset] = '-';
  }

  constexpr const char* get_result() const { return buffer + offset; }
};

TEST_CASE("Division Stringified: division_stringified_v1") {
  CHECK(division_stringified_v1(1, 10) == "0");
  CHECK(division_stringified_v1(5, 54) == "0");
  CHECK(division_stringified_v1(175, 24) == "7");
  CHECK(division_stringified_v1(101077282, 21123) == "4,785");
  CHECK(division_stringified_v1(-101077282, 21123) == "-4,785");
  CHECK(division_stringified_v1(101077282, -21123) == "-4,785");
  CHECK(division_stringified_v1(-101077282, -21123) == "4,785");
  CHECK(division_stringified_v1(100000, 1) == "100,000");
  CHECK(division_stringified_v1(10000000, 10) == "1,000,000");
}

TEST_CASE("Division Stringified: division_stringified_v2") {
  constexpr division_stringified_v2 div1{1, 10};
  CHECK(strcmp(div1.get_result(), "0") == 0);
  constexpr division_stringified_v2 div2{5, 54};
  CHECK(strcmp(div2.get_result(), "0") == 0);
  constexpr division_stringified_v2 div3{175, 24};
  CHECK(strcmp(div3.get_result(), "7") == 0);
  constexpr division_stringified_v2 div4{101077282, 21123};
  CHECK(strcmp(div4.get_result(), "4,785") == 0);
  constexpr division_stringified_v2 div5{-101077282, 21123};
  CHECK(strcmp(div5.get_result(), "-4,785") == 0);
  constexpr division_stringified_v2 div6{101077282, -21123};
  CHECK(strcmp(div6.get_result(), "-4,785") == 0);
  constexpr division_stringified_v2 div7{-101077282, -21123};
  CHECK(strcmp(div7.get_result(), "4,785") == 0);
  constexpr division_stringified_v2 div8{100000, 1};
  CHECK(strcmp(div8.get_result(), "100,000") == 0);
  constexpr division_stringified_v2 div9{10000000, 10};
  CHECK(strcmp(div9.get_result(), "1,000,000") == 0);
}

// int main() {
//   // const vector<int64_t> numbers { gets(stdin) };
//   // cout << DivisionStringified(numbers[0], numbers[1]);
//   constexpr division_stringified_v2 div1{1, 10};
//   cout << div1.get_result() << '\n';  // expected output: "0"
//   constexpr division_stringified_v2 div2{5, 54};
//   cout << div2.get_result() << '\n';  // expected output: "0"
//   constexpr division_stringified_v2 div3{175, 24};
//   cout << div3.get_result() << '\n';  // expected output: "7"
//   constexpr division_stringified_v2 div4{101077282, 21123};
//   cout << div4.get_result() << '\n';  // expected output: "4,785"
//   constexpr division_stringified_v2 div5{-101077282, 21123};
//   cout << div5.get_result() << '\n';  // expected output: "-4,785"
//   constexpr division_stringified_v2 div6{101077282, -21123};
//   cout << div6.get_result() << '\n';  // expected output: "-4,785"
//   constexpr division_stringified_v2 div7{-101077282, -21123};
//   cout << div7.get_result() << '\n';  // expected output: "4,785"
//   constexpr division_stringified_v2 div8{100000, 1};
//   cout << div8.get_result() << '\n';  // expected output: "100,000"
//   constexpr division_stringified_v2 div9{10000000, 10};
//   cout << div9.get_result() << '\n';  // expected output: "1,000,000"

//   return 0;
// }
