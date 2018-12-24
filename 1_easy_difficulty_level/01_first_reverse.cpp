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
#include <string>
#include <type_traits>

template <typename, typename...>
struct is_anyone_of : std::false_type {};

template <typename T, typename First>
struct is_anyone_of<T, First> : std::is_same<T, First> {};

template <typename T, typename First, typename... Rest>
struct is_anyone_of<T, First, Rest...>
    : std::integral_constant<bool,
                             std::is_same_v<T, First> ||
                                 is_anyone_of<T, Rest...>::value> {};

template <typename T, typename First, typename... Rest>
inline constexpr bool is_anyone_of_v = is_anyone_of<T, First, Rest...>::value;

template <typename T>
struct is_character_type {
  static constexpr bool value =
      is_anyone_of_v<std::remove_cv_t<T>, char, wchar_t, char16_t, char32_t>;
};

template <typename T>
inline constexpr bool is_character_type_v = is_character_type<T>::value;

template <typename CharType>
bool is_ws_char(const CharType ch) {
  static_assert(is_character_type_v<CharType>,
                "Specified character type is not supported!");

#if defined(__GNUC__)
  printf("__PRETTY_FUNCTION__ -> %s\n", __PRETTY_FUNCTION__);
#elif defined(_MSC_VER)
  printf("__FUNCSIG__ -> %s\n", __FUNCSIG__);
#endif

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

template <typename StringType>
StringType trim(const StringType& str) {
  static_assert(is_anyone_of_v<StringType, std::string, std::wstring,
                               std::u16string, std::u32string>,
                "Specified string type is not supported!");

#if defined(__GNUC__)
  printf("__PRETTY_FUNCTION__ -> %s\n", __PRETTY_FUNCTION__);
#elif defined(_MSC_VER)
  printf("__FUNCSIG__ -> %s\n", __FUNCSIG__);
#endif

  const size_t str_len{str.length()};

  if (!str_len)
    return StringType{};

  size_t begin_str{};
  size_t end_str{str_len - 1};

  for (; begin_str <= end_str && is_ws_char(str[begin_str]); ++begin_str)
    continue;

  if (begin_str > end_str)
    return StringType{};

  for (; end_str > begin_str && is_ws_char(str[end_str]); --end_str)
    continue;

  return str.substr(begin_str, end_str - begin_str + 1);
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
