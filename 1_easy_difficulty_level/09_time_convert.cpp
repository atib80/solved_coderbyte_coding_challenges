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
#include <type_traits>
#include <utility>

template <typename, typename...>
struct is_anyone_of : std::false_type {};

template <typename T, typename First, typename... Rest>
struct is_anyone_of<T, First, Rest...>
    : std::integral_constant<bool,
                             std::is_same_v<T, First> ||
                                 is_anyone_of<T, Rest...>::value> {};

template <typename T, typename First, typename... Rest>
constexpr bool is_anyone_of_v = is_anyone_of<T, First, Rest...>::value;

template <typename T>
struct get_char_type {
  using type = std::remove_cv_t<std::remove_pointer_t<std::decay_t<T>>>;
  static_assert(is_anyone_of_v<type, char, wchar_t, char16_t, char32_t>);
};

template <typename T>
using get_char_type_t = typename get_char_type<T>::type;

template <typename T>
struct is_valid_char_type {
  static constexpr const bool value =
      is_anyone_of_v<std::remove_cv_t<T>, char, wchar_t, char16_t, char32_t>;
};

template <typename T>
constexpr const bool is_valid_char_type_v = is_valid_char_type<T>::value;

template <typename CharType,
          size_t BUFFER_LENGTH,
          typename =
              std::enable_if_t<is_valid_char_type_v<get_char_type_t<CharType>>>>
class Solution {
  mutable std::array<CharType, BUFFER_LENGTH> buffer;

 public:
  constexpr Solution() : buffer{} {}

  template <typename T>
  constexpr const CharType* TimeConvert(const T time_in_minutes) const {
    if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T>) {
      uint64_t minutes{static_cast<uint64_t>(time_in_minutes)};
      uint64_t hours{minutes / 60};
      minutes %= 60;
      size_t index{};

      if (0 == minutes)

        buffer.at(index++) = static_cast<CharType>('0');

      else {
        while (minutes > 0) {
          buffer.at(index++) = static_cast<CharType>('0') + minutes % 10;
          minutes /= 10;
        }
      }

      buffer.at(index++) = static_cast<CharType>(':');

      if (0 == hours)

        buffer.at(index++) = static_cast<CharType>('0');

      else {
        while (hours > 0) {
          buffer.at(index++) = static_cast<CharType>('0') + hours % 10;
          hours /= 10;
        }
      }

      buffer.at(index) = static_cast<CharType>('\0');

      for (size_t i{}, j{index - 1}; i < j; ++i, --j)
        std::swap(buffer.at(i), buffer.at(j));

    } else {
      buffer.at(0) = static_cast<CharType>('N');
      buffer.at(1) = static_cast<CharType>('a');
      buffer.at(2) = static_cast<CharType>('N');
      buffer.at(2) = static_cast<CharType>('\0');
    }

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
