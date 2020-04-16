/*
Coderbyte coding challenge: First Factorial

Using the C++ language, have the function FirstFactorial(num) take the num
parameter being passed and return the factorial of it (e.g. if num = 4, return
(4 * 3 * 2 * 1)). For the test cases, the range will be between 1 and 18 and the
input will always be an integer.

Sample test cases:

Input:  4
Output: 24

Input:  8
Output: 40320
*/

#include <cctype>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "../include/stl_helper_functions.hpp"

using namespace std;

class big_integer {
  using byte = unsigned char;
  using number_base = stl::helper::number_base;

  const number_base base_;
  vector<byte> digits_;
  string number_str_;
  string_view number_str_view_;
  bool is_negative_number_;
  size_t first_;
  size_t last_;

 public:
  explicit big_integer(const char* number,
                       const number_base base = number_base::decimal)
      : base_{base} {
    store_number(number);
  }

  explicit big_integer(const string& number,
                       const number_base base = number_base::decimal)
      : big_integer(number.c_str(), base) {}

  big_integer(const big_integer& rhs) : base_{rhs.base_} {
    store_number(rhs.get_big_integer().c_str());
  }

  number_base get_big_integer_number_base() const { return base_; }

  string get_big_integer() const {
    return string(cbegin(number_str_) + first_, cbegin(number_str_) + last_);
  }

  explicit operator string() const { return get_big_integer(); }

  explicit operator const char*() const { return &number_str_[first_]; }

 private:
  void store_number(const char* number) {
    if (number != nullptr && stl::helper::len(number) > 0) {
      number_str_ = stl::helper::trim(number);
    } else {
      throw invalid_argument{
          "Input number string does not contain a valid number!"};
    }

    digits_.resize(128U);

    first_ = 0U;

    if (number_str_[0] == '-' || number_str_[0] == '+') {
      is_negative_number_ = number_str_[0] == '-';
      first_++;
    }

    if (base_ == number_base::binary) {
      if ('b' == number_str_[0] || 'B' == number_str_[0]) {
        first_++;

      } else if ('0' == number_str_[0] &&
                 ('b' == number_str_[1] || 'B' == number_str_[1])) {
        first_ += 2;
      }

    } else if (base_ == number_base::octal) {
      if ('0' == number_str_[0] || 'o' == number_str_[0] ||
          'O' == number_str_[0]) {
        first_++;
      }

    } else if (base_ == number_base::decimal) {
      while (isspace(number_str_[first_])) {
        first_++;
      }

      if (number_str_[first_] < '0' || number_str_[first_] > '9') {
        throw invalid_argument{
            "Input number string does not contain a valid number!"};
      }

      last_ = number_str_.find_first_not_of("0123456789", first_ + 1);

    } else if (base_ == number_base::hexadecimal) {
      if ('0' == number_str_[0] &&
          ('x' == number_str_[1] || 'X' == number_str_[1])) {
        first_ += 2;
      }
    }

    number_str_view_ = {&number_str_[first_], last_ - first_};
  }
};

template <size_t N = 20>
struct precalculated_factorials {
  uint64_t factorials[N + 1];

  constexpr precalculated_factorials() : factorials{} {
    factorials[0] = factorials[1] = 1;

    for (size_t i{2}; i <= N; ++i)
      factorials[i] = calculate_factorial(i);
  }

  constexpr uint64_t calculate_factorial(uint64_t n) const {
    uint64_t result{n};

    while (--n > 1)
      result *= n;

    return result;
  }

  constexpr uint64_t get_factorial_of_specified_number(const uint64_t n) const {
    if (n <= N)
      return factorials[n];
    return calculate_factorial(n);
  }
};

static constexpr precalculated_factorials<> factorials;

uint64_t FirstFactorial_v1(uint64_t num) {
  if (!num)
    return 1;

  if (num < 3)
    return num;

  uint64_t result{num};

  while (num > 2)
    result *= --num;

  return result;
}

uint64_t FirstFactorial_v2(const uint64_t num) {
  if (num < 2LL)
    return 1LL;

  return num * FirstFactorial_v2(num - 1);
}

uint64_t FirstFactorial_v3(const uint64_t num) {
  if (num <= 20)
    return factorials.get_factorial_of_specified_number(num);
  return FirstFactorial_v1(num);
}

int main() {
  // cout << FirstFactorial_v1(gets(stdin));
  cout << FirstFactorial_v1(0) << '\n';   // expected output: 1
  cout << FirstFactorial_v1(1) << '\n';   // expected output: 1
  cout << FirstFactorial_v1(2) << '\n';   // expected output: 2
  cout << FirstFactorial_v1(3) << '\n';   // expected output: 6
  cout << FirstFactorial_v1(4) << '\n';   // expected output: 24
  cout << FirstFactorial_v1(5) << '\n';   // expected output: 120
  cout << FirstFactorial_v1(6) << '\n';   // expected output: 720
  cout << FirstFactorial_v1(7) << '\n';   // expected output: 5040
  cout << FirstFactorial_v1(8) << '\n';   // expected output: 40320
  cout << FirstFactorial_v1(9) << '\n';   // expected output: 362880
  cout << FirstFactorial_v1(10) << '\n';  // expected output: 3628800
  cout << FirstFactorial_v1(11) << '\n';  // expected output: 39916800
  cout << FirstFactorial_v1(12) << '\n';  // expected output: 479001600
  cout << FirstFactorial_v1(13) << '\n';  // expected output: 6227020800
  cout << FirstFactorial_v1(14) << '\n';  // expected output: 87178291200
  cout << FirstFactorial_v1(15) << '\n';  // expected output: 1307674368000
  cout << FirstFactorial_v1(16) << '\n';  // expected output: 20922789888000
  cout << FirstFactorial_v1(17) << '\n';  // expected output: 355687428096000
  cout << FirstFactorial_v1(18) << '\n';  // expected output: 6402373705728000
  cout << FirstFactorial_v1(19) << '\n';  // expected output: 121645100408832000
  cout << FirstFactorial_v1(20)
       << '\n';  // expected output: 2432902008176640000

  return 0;
}
