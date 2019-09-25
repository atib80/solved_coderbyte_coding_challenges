/*
Coderbyte coding challenge: Powers Of Two

Using the C++ language, have the function PowersofTwo(num) take the num
parameter being passed which will be an integer and return the string true if
it's a power of two. If it's not return the string false. For example if the
input is 16 then your program should return the string true but if the input is
22 then the output should be the string false.

Sample test cases:

Input:  4
Output: "true"

Input:  124
Output: "false"
*/

#include <cmath>
#include <iostream>
#include <string>

using namespace std;

template <size_t N>
struct Log2N {
  static constexpr size_t value = (((N & 0xFFFFFFFF00000000ULL) != 0) << 5) |
                                  (((N & 0xFFFF0000FFFF0000ULL) != 0) << 4) |
                                  (((N & 0xFF00FF00FF00FF00ULL) != 0) << 3) |
                                  (((N & 0xF0F0F0F0F0F0F0F0ULL) != 0) << 2) |
                                  (((N & 0xCCCCCCCCCCCCCCCCULL) != 0) << 1) |
                                  ((N & 0xAAAAAAAAAAAAAAAAULL) != 0);
};

string PowersofTwo_v1(int64_t target_num) {
  if (target_num < 1)
    return "false";

  while (target_num > 1) {
    if (1 == target_num % 2)
      return "false";

    target_num /= 2;
  }

  return "true";
}

string PowersofTwo_v2(const int64_t target_num) {
  if (target_num < 1)
    return "false";

  int64_t num{1};

  while (num <= target_num) {
    if (target_num == num)
      return "true";

    num <<= 1;
  }

  return "false";
}

constexpr const char* PowersofTwo_v3(const uint64_t target_num) {
  if (0U == target_num)
    return "false";

  const size_t value = (((target_num & 0xFFFFFFFF00000000ULL) != 0) << 5) |
                       (((target_num & 0xFFFF0000FFFF0000ULL) != 0) << 4) |
                       (((target_num & 0xFF00FF00FF00FF00ULL) != 0) << 3) |
                       (((target_num & 0xF0F0F0F0F0F0F0F0ULL) != 0) << 2) |
                       (((target_num & 0xCCCCCCCCCCCCCCCCULL) != 0) << 1) |
                       ((target_num & 0xAAAAAAAAAAAAAAAAULL) != 0);

  const uint64_t correct_result{1ULL << value};
  return target_num == correct_result ? "true" : "false";
}

int main() {
  // cout << PowersofTwo_v2(gets(stdin));
  cout << PowersofTwo_v3(16) << '\n';     // expected output: "true"
  cout << PowersofTwo_v3(22) << '\n';     // expected output: "false"
  cout << PowersofTwo_v3(4) << '\n';      // expected output: "true"
  cout << PowersofTwo_v3(124) << '\n';    // expected output: "false"
  cout << PowersofTwo_v3(16) << '\n';     // expected output: "true"
  cout << PowersofTwo_v3(8) << '\n';      // expected output: "true"
  cout << PowersofTwo_v3(32) << '\n';     // expected output: "true"
  cout << PowersofTwo_v3(11128) << '\n';  // expected output: "false"

  return 0;
}
