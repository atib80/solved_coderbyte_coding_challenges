/*
Coderbyte coding challenge: AB Check (v1, v2)

Using the C++ language, have the function ABCheck(str) take the str parameter
being passed and return the string true if the characters a and b are separated
by exactly 3 places anywhere in the string at least once (ie. "lane borrowed"
would result in true because there is exactly three characters between a and b).
Otherwise return the string false.

Sample test cases:

Input:  "after badly"
Output: "false"

Input:  "Laura sobs"
Output: "true"
*/

#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <locale>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

template <typename T, typename... Rest>
struct is_anyone_of : std::false_type {};

template <typename T, typename First>
struct is_anyone_of<T, First> : std::is_same<T, First> {};

template <typename T, typename First, typename... Rest>
struct is_anyone_of<T, First, Rest...>
    : std::integral_constant<bool,
                             std::is_same<T, First>::value ||
                                 is_anyone_of<T, Rest...>::value> {};

template <typename T, typename First, typename... Rest>
constexpr const bool is_anyone_of_v = is_anyone_of<T, First, Rest...>::value;

template <typename CharType>
struct default_whitespace_chars {};

template <>
struct default_whitespace_chars<char> {
  static constexpr const char* value = " \t\n\f\v\r";
};

template <>
struct default_whitespace_chars<wchar_t> {
  static constexpr const wchar_t* value = L" \t\n\f\v\r";
};

template <>
struct default_whitespace_chars<char16_t> {
  static constexpr const char16_t* value = u" \t\n\f\v\r";
};

template <>
struct default_whitespace_chars<char32_t> {
  static constexpr const char32_t* value = U" \t\n\f\v\r";
};

template <typename CharType>
constexpr const CharType* default_whitespace_chars_v =
    default_whitespace_chars<CharType>::value;

template <typename T>
struct is_valid_char_type {
  static constexpr const bool value =
      is_anyone_of_v<std::remove_cv_t<T>, char, wchar_t, char16_t, char32_t>;
};

template <typename T>
constexpr const bool is_valid_char_type_v = is_valid_char_type<T>::value;

template <typename T>
struct is_non_const_char_pointer_type {
  static constexpr const bool value = is_anyone_of_v<T,
                                                     char*,
                                                     wchar_t*,
                                                     char16_t*,
                                                     char32_t*,
                                                     char* const,
                                                     wchar_t* const,
                                                     char16_t* const,
                                                     char32_t* const>;
};

template <typename T>
constexpr const bool is_non_const_char_pointer_type_v =
    is_non_const_char_pointer_type<T>::value;

template <typename T>
struct is_const_char_pointer_type {
  static constexpr const bool value = is_anyone_of_v<T,
                                                     const char*,
                                                     const wchar_t*,
                                                     const char16_t*,
                                                     const char32_t*,
                                                     const char* const,
                                                     const wchar_t* const,
                                                     const char16_t* const,
                                                     const char32_t* const>;
};

template <typename T>
constexpr const bool is_const_char_pointer_type_v =
    is_const_char_pointer_type<T>::value;

template <typename T>
struct is_non_const_char_array_type {
  static constexpr bool value = 1u == std::rank_v<T> &&
                                is_valid_char_type_v<std::remove_extent_t<T>> &&
                                !std::is_const_v<std::remove_extent_t<T>>;
};

template <typename T>
constexpr const bool is_non_const_char_array_type_v =
    is_non_const_char_array_type<T>::value;

template <typename T>
struct is_const_char_array_type {
  static constexpr bool value = 1u == std::rank_v<T> &&
                                is_valid_char_type_v<std::remove_extent_t<T>> &&
                                std::is_const_v<std::remove_extent_t<T>>;
};

template <typename T>
constexpr const bool is_const_char_array_type_v =
    is_const_char_array_type<T>::value;

template <typename T>
struct is_char_pointer_type {
  static constexpr const bool value =
      is_non_const_char_pointer_type_v<T> || is_const_char_pointer_type_v<T>;
};

template <typename T>
constexpr const bool is_char_pointer_type_v = is_char_pointer_type<T>::value;

template <typename T>
struct is_char_array_type {
  static constexpr const bool value =
      is_non_const_char_array_type_v<T> || is_const_char_array_type_v<T>;
};

template <typename T>
constexpr const bool is_char_array_type_v = is_char_array_type<T>::value;

template <typename T>
struct remove_all_decorations {
  using dt = std::decay_t<T>;

  using mt1 = std::conditional_t<std::is_const_v<dt> || std::is_volatile_v<dt>,
                                 std::remove_cv_t<dt>,
                                 dt>;
  using mt2 = std::
      conditional_t<std::is_array_v<mt1>, std::remove_all_extents_t<mt1>, mt1>;
  using mt3 = std::
      conditional_t<std::is_pointer_v<mt2>, std::remove_pointer_t<mt2>, mt2>;
  using mt4 = std::conditional_t<std::is_reference_v<mt3>,
                                 std::remove_reference_t<mt3>,
                                 mt3>;
  using type =
      std::conditional_t<std::is_const_v<mt4> || std::is_volatile_v<mt4>,
                         std::remove_cv_t<mt4>,
                         mt4>;
};

template <typename T>
using remove_all_decorations_t = typename remove_all_decorations<T>::type;

template <typename T>
struct is_valid_string_type {
  static constexpr const bool value =
      is_anyone_of_v<remove_all_decorations_t<T>,
                     std::string,
                     std::wstring,
                     std::u16string,
                     std::u32string>;
};

template <typename T>
constexpr const bool is_valid_string_type_v = is_valid_string_type<T>::value;

template <typename T>
struct is_valid_string_view_type {
  static constexpr const bool value =
      is_anyone_of_v<remove_all_decorations_t<T>,
                     std::string_view,
                     std::wstring_view,
                     std::u16string_view,
                     std::u32string_view>;
};

template <typename T>
constexpr const bool is_valid_string_view_type_v =
    is_valid_string_view_type<T>::value;

template <typename T>
using has_value_type_t = decltype(std::declval<typename T::value_type>());

template <typename T, typename = void>
struct has_value_type : std::false_type {};

template <typename T>
struct has_value_type<T, std::void_t<has_value_type_t<T>>> : std::true_type {};

template <typename T>
constexpr const bool has_value_type_v = has_value_type<T>::value;

template <typename T, typename = void>
struct get_char_type {
  using type = remove_all_decorations_t<T>;
  static_assert(is_valid_char_type_v<type>,
                "Underlying type is not an intrinsic character type!");
};

template <typename T>
struct get_char_type<
    T,
    std::void_t<has_value_type_t<remove_all_decorations_t<T>>>> {
  using type = typename remove_all_decorations_t<T>::value_type;
  static_assert(is_valid_char_type_v<type>,
                "Underlying type is not an intrinsic character type!");
};

template <typename T>
using get_char_type_t = typename get_char_type<T>::type;

template <typename T>
struct add_const_pointer_to_char_type {
  using type = std::add_const_t<
      std::add_pointer_t<std::add_const_t<get_char_type_t<T>>>>;
};

template <typename T>
using add_const_pointer_to_char_type_t =
    typename add_const_pointer_to_char_type<T>::type;

class StringHelper {
 public:
  inline static constexpr size_t max_string_length{std::string::npos};

  template <typename T,
            typename = std::enable_if_t<
                is_char_array_type_v<T> || is_char_pointer_type_v<T> ||
                is_valid_string_type_v<T> || is_valid_string_view_type_v<T>>>
  static size_t len(T src,
                    size_t max_allowed_string_length = max_string_length) {
    if constexpr (is_valid_string_type_v<T> || is_valid_string_view_type_v<T>) {
      return src.length() > max_allowed_string_length
                 ? max_allowed_string_length
                 : src.length();
    } else {
      if constexpr (is_char_pointer_type_v<T>) {
        if (nullptr == src)
          return 0U;
      }

      size_t length{};

      while (src[length]) {
        ++length;
        if (max_allowed_string_length == length)
          return max_allowed_string_length;
      }

      return length;
    }
  }

  template <typename T,
            typename = std::enable_if_t<is_valid_string_type_v<T> ||
                                        is_valid_string_view_type_v<T>>>

  static auto trim(const T& src,
                   add_const_pointer_to_char_type_t<T> chars_to_trim =
                       default_whitespace_chars_v<typename T::value_type>) {
    using char_type = typename T::value_type;

    if (0 == src.length())
      return basic_string<char_type>{};

    const std::unordered_set<char_type> trimmed_chars(
        chars_to_trim, chars_to_trim + len(chars_to_trim));

    const auto first{std::find_if(
        std::cbegin(src), std::cend(src), [&trimmed_chars](const auto ch) {
          return trimmed_chars.find(ch) == std::cend(trimmed_chars);
        })};

    if (first == std::cend(src))
      return basic_string<char_type>{};

    const auto last{std::find_if(std::crbegin(src), std::crend(src),
                                 [&trimmed_chars](const auto ch) {
                                   return trimmed_chars.find(ch) ==
                                          std::cend(trimmed_chars);
                                 })
                        .base()};

    return basic_string<char_type>(first, last);
  }
};

string ABCheck_v1(string str) {
  str = StringHelper::trim(str);

  const int str_len{static_cast<int>(str.length())};

  for (int i{}, j{str_len - 1}; i < str_len - 4 && j > 3 && i < j;
       i++, j--) {
    if (('a' == str[i] && 'b' == str[i + 4]) ||
        ('b' == str[i] && 'a' == str[i + 4]) ||
        ('a' == str[j] && 'b' == str[j - 4]) ||
        ('b' == str[j] && 'a' == str[j - 4]))
      return "true";
  }

  return "false";
}

string ABCheck_v2(string str) {
  str = StringHelper::trim(str);

  size_t start{str.find_first_of("ab")};

  if (string::npos == start)
    return "false";

  while (true) {
    const char prev_char{str[start]};

    const size_t next_char_pos{str.find_first_of("ab", start + 1)};

    if (string::npos == next_char_pos)
      return "false";

    if (prev_char != str[next_char_pos] && next_char_pos - start == 4)
      return "true";

    start = next_char_pos;
  }
}

int main() {
  // cout << ABCheck_v1(gets(stdin));
  cout << ABCheck_v1("ab") << '\n';             // expected output: "false"
  cout << ABCheck_v1("a-b") << '\n';            // expected output: "false"
  cout << ABCheck_v1("a--b") << '\n';           // expected output: "false"
  cout << ABCheck_v1("a---b") << '\n';          // expected output: "true"
  cout << ABCheck_v1("lane borrowed") << '\n';  // expected output: "true"
  cout << ABCheck_v1("after badly") << '\n';    // expected output: "false"
  cout << ABCheck_v1("Laura sobs") << '\n';     // expected output: "true"

  return 0;
}
