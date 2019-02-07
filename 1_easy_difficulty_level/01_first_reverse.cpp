/*
Coderbyte coding challenge: First Reverse

Using the C++ language, have the function FirstReverse(str) take the str
parameter being passed and return the string in reversed order. For example: if
the input string is "Hello World and Coders" then your program should return the
string sredoC dna dlroW olleH.

Sample test cases:

Input:  "coderbyte"
Output: "etybredoc"

Input:  "I Love Code"
Output: "edoC evoL I"
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>
#include <unordered_set>

template <typename, typename...>
struct is_anyone_of : std::false_type {};

template <typename T, typename First, typename... Rest>
struct is_anyone_of<T, First, Rest...>
    : std::integral_constant<bool,
                             std::is_same_v<T, First> ||
                                 is_anyone_of<T, Rest...>::value> {};

template <typename T, typename First, typename... Rest>
static inline constexpr bool is_anyone_of_v =
    is_anyone_of<T, First, Rest...>::value;

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
static constexpr const CharType* default_whitespace_chars_v =
    default_whitespace_chars<CharType>::value;

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
      is_anyone_of_v<std::remove_cv_t<T, char, wchar_t, char16_t, char32_t>>;
};

template <typename T>
static constexpr const bool is_valid_char_type_v = is_valid_char_type<T>::value;

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
static constexpr const bool is_non_const_char_pointer_type_v =
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
static constexpr const bool is_const_char_pointer_type_v =
    is_const_char_pointer_type<T>::value;

template <typename T>
struct is_non_const_char_array_type {
  static constexpr bool value =
      std::is_array_v<T> && 1u == std::rank_v<T> && !std::is_const_v<T>;
};

template <typename T>
static constexpr const bool is_non_const_char_array_type_v =
    is_non_const_char_array_type<T>::value;

template <typename T>
struct is_const_char_array_type {
  static constexpr bool value =
      std::is_array_v<T> && 1u == std::rank_v<T> && std::is_const_v<T>;
};

template <typename T>
static constexpr const bool is_const_char_array_type_v =
    is_const_char_array_type<T>::value;

template <typename T>
struct is_valid_string_type {
  static constexpr const bool value = is_anyone_of_v<
      std::remove_cv_t<std::remove_pointer_t<std::remove_reference_t<T>>>,
      std::string,
      std::wstring,
      std::u16string,
      std::u32string>;
};

template <typename T>
static constexpr const bool is_valid_string_type_v =
    is_valid_string_type<T>::value;

template <typename T>
struct add_const_pointer_to_char_type {
  using type = std::add_pointer_t<std::add_const_t<get_char_type_t<T>>>;
  static_assert(is_anyone_of_v<type,
                               const char*,
                               const wchar_t*,
                               const char16_t*,
                               const char32_t*>);
};

template <typename T>
using add_const_pointer_to_char_type_t =
    typename add_const_pointer_to_char_type<T>::type;

template <typename T>
struct is_character_type {
  static constexpr bool value =
      is_anyone_of_v<std::remove_cv_t<T>, char, wchar_t, char16_t, char32_t>;
};

template <typename T>
static inline constexpr bool is_character_type_v = is_character_type<T>::value;

template <typename CharType>
bool is_ws_char(const CharType ch) {
  static_assert(is_valid_char_type_v<CharType>,
                "Specified character type is not supported!");

// #if defined(__GNUC__)
//   printf("__PRETTY_FUNCTION__ -> %s\n", __PRETTY_FUNCTION__);
// #elif defined(_MSC_VER)
//   printf("__FUNCSIG__ -> %s\n", __FUNCSIG__);
// #endif

  switch (ch) {
    case static_cast<CharType>(' '):
    case static_cast<CharType>('\t'):
    case static_cast<CharType>('\n'):
    case static_cast<CharType>('\f'):
    case static_cast<CharType>('\v'):
      return true;

    default:
      return false;
  }
}

static constexpr size_t max_string_length{std::numeric_limits<size_t>::max()};

template <
    typename T,
    typename ConditionType = std::enable_if_t<
        is_const_char_array_type_v<T> || is_non_const_char_array_type_v<T> ||
            is_const_char_pointer_type_v<T> ||
            is_non_const_char_pointer_type_v<T> || is_valid_string_type_v<T>,
        void*>>
size_t len(T src, const size_t max_allowed_string_length = max_string_length) {

// #if defined(__GNUC__)
//   printf("__PRETTY_FUNCTION__ -> %s\n", __PRETTY_FUNCTION__);
// #elif defined(_MSC_VER)
//   printf("__FUNCSIG__ -> %s\n", __FUNCSIG__);
// #endif

  if constexpr (is_valid_string_type_v<T>) {
    return src.length() > max_allowed_string_length ? max_allowed_string_length
                                                    : src.length();
  } else {
    if (!src)
      return 0u;

    size_t length{};

    while (*src++) {
      ++length;

      if (max_allowed_string_length == length)
        return max_allowed_string_length;
    }

    return length;
  }
}

template <typename StringType,
          typename ConditionType =
              std::enable_if_t<is_valid_string_type_v<StringType>, void*>>

auto trim(const StringType& src,
          add_const_pointer_to_char_type_t<typename StringType::value_type>
              chars_to_trim =
                  default_whitespace_chars_v<typename StringType::value_type>) {

// #if defined(__GNUC__)
//   printf("__PRETTY_FUNCTION__ -> %s\n", __PRETTY_FUNCTION__);
// #elif defined(_MSC_VER)
//   printf("__FUNCSIG__ -> %s\n", __FUNCSIG__);
// #endif

  using char_type = typename StringType::value_type;

  if (0 == src.length())
    return StringType{};

  const std::unordered_set<char_type> trimmed_chars(
      chars_to_trim, chars_to_trim + len(chars_to_trim));

  const auto first{std::find_if(
      std::cbegin(src), std::cend(src), [&trimmed_chars](const auto ch) {
        return trimmed_chars.find(ch) == std::cend(trimmed_chars);
      })};

  if (first == std::cend(src))
    return StringType{};

  const auto last{std::find_if(std::crbegin(src), std::crend(src),
                               [&trimmed_chars](const auto ch) {
                                 return trimmed_chars.find(ch) ==
                                        std::cend(trimmed_chars);
                               })
                      .base()};

  return StringType(first, last);
}

using namespace std;

string FirstReverse(string str) {
  str = trim(str);
  const size_t str_len{str.length()};

  if (str_len < 2u)
    return str;

  for (size_t i{}; i < str_len / 2; i++)
    swap(str[i], str[str_len - 1 - i]);

  return str;
}

string FirstReverse_v2(string str) {
  reverse(begin(str), end(str));

  return str;
}

int main() {
  // cout << FirstReverse(gets(stdin));
  cout << FirstReverse(string{"Hello World and Coders"})
       << '\n';  // expected output: "sredoC dna dlroW olleH"
  cout << FirstReverse(string{"coderbyte"})
       << '\n';  // expected output: "etybredoc"
  cout << FirstReverse(string{"I Love Code"})
       << '\n';  // expected output: "edoC evoL I"

  return 0;
}
