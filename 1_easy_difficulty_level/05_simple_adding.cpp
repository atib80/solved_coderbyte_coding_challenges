/*
Coderbyte coding challenge: Simple Adding

Using the C++ language, have the function SimpleAdding(num) add up all the
numbers from 1 to num. For example: if the input is 4 then your program should
return 10 because 1 + 2 + 3 + 4 = 10. For the test cases, the parameter num will
be any number from 1 to 1000.

Sample test cases:

Input:  12
Output: 78

Input:  140
Output: 9870
*/

#include <array>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <vector>

using namespace std;

constexpr uint64_t SimpleAdding_v1(const uint64_t num) {
  uint64_t result{1ULL};

  for (uint64_t i{2ULL}; i <= num; ++i)
    result += i;

  return result;
}

template <typename T, T start, T last>
class crange {
  const array<T, last - start> crange_;

 public:
  constexpr explicit crange() {
    if (start > last)
      throw invalid_argument{
          "The start value of a range object cannot be greater than its last!"};
    for (T i{}, j{start}; j < last; ++i, ++j)
      crange_[i] = j;
  }

  template <typename ContainerType>
  operator ContainerType() const {
    ContainerType rangeContainer{};
    for (T i{start}; i < last; ++i)
      rangeContainer.insert(end(rangeContainer), i);
    return rangeContainer;
  }

  constexpr auto begin() const { return std::begin(crange_); }

  constexpr auto end() const { return std::end(crange_); }

  constexpr auto cbegin() const { return std::cbegin(crange_); }

  constexpr auto cend() const { return std::cend(crange_); }
};

template <typename T, T first, T last>
constexpr auto begin(const crange<T, first, last>& cr) {
  return cr.begin();
}

template <typename T, T first, T last>
auto end(const crange<T, first, last>& cr) {
  return cr.end();
}

template <typename T, T first, T last>
auto cbegin(const crange<T, first, last>& cr) {
  return cr.cbegin();
}

template <typename T, T first, T last>
auto cend(const crange<T, first, last>& cr) {
  return cr.cend();
}

template <typename T>
class range {
  T start_;
  T last_;

  vector<T> range_;

 public:
  explicit range(const T start = 0, const T last = 0)
      : start_{start}, last_{last}, range_(last_ - start_) {
    if (start_ > last_)
      throw invalid_argument{
          "The start value of a range object cannot be greater than its last!"};
    iota(range_.begin(), range_.end(), start_);
  }

  template <typename ContainerType>
  operator ContainerType() const {
    ContainerType rangeContainer{};
    for (T i{start_}; i < last_; ++i)
      rangeContainer.insert(end(rangeContainer), i);
    return rangeContainer;
  }

  auto begin() const { return std::begin(range_); }

  auto end() const { return std::end(range_); }

  auto cbegin() const { return std::cbegin(range_); }

  auto cend() const { return std::cend(range_); }
};

template <typename T>
auto begin(const range<T>& r) {
  return r.begin();
}

template <typename T>
auto end(const range<T>& r) {
  return r.end();
}

template <typename T>
auto cbegin(const range<T>& r) {
  return r.cbegin();
}

template <typename T>
auto cend(const range<T>& r) {
  return r.cend();
}

uint64_t SimpleAdding_v2(const uint64_t num) {
  range<size_t> r{1, num + 1};

  return accumulate(cbegin(r), cend(r), 0UL);
}

constexpr int64_t SimpleAdding_v3(int64_t num) {
  const bool is_negative{num < 0};
  if (is_negative)
    num = -num;

  const int64_t result{(num * (num + 1)) / 2};

  return !is_negative ? result : -result;
}

int main() {
  // cout << SimpleAdding_v3(gets(stdin));
  cout << SimpleAdding_v3(4) << '\n';    // expected output: 10
  cout << SimpleAdding_v3(12) << '\n';   // expected output: 78
  cout << SimpleAdding_v3(140) << '\n';  // expected output: 9870

  return 0;
}
