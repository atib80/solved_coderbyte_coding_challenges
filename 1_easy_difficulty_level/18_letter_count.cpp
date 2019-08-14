/*
Coderbyte coding challenge: Letter Count I

Using the C++ language, have the function LetterCountI(str) take the str
parameter being passed and return the first word with the greatest number of
repeated letters. For example: "Today, is the greatest day ever!" should return
greatest because it has 2 e's (and 2 t's) and it comes before ever which also
has 2 e's. If there are no words with repeating letters return -1. Words will be
separated by spaces.

Sample test cases:

Input:  "Hello apple pie"
Output: "Hello"

Input:  "No words"
Output: -1
*/

#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
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
constexpr bool is_anyone_of_v = is_anyone_of<T, First, Rest...>::value;

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

template <
    typename T,
    typename FormatStringType = const char*,
    typename = std::enable_if_t<
        is_valid_char_type_v<remove_all_decorations_t<FormatStringType>> &&
        is_anyone_of_v<remove_all_decorations_t<FormatStringType>,
                       char,
                       wchar_t>>>
basic_string<remove_all_decorations_t<FormatStringType>> num_to_str(
    T&& number,
    FormatStringType format_string = nullptr) {
  using char_type = remove_all_decorations_t<FormatStringType>;
  using data_type = remove_all_decorations_t<T>;

  static char_type buffer[32]{};

  if (nullptr != format_string) {
    if constexpr (std::is_same_v<char_type, char>)
      snprintf(buffer, 32, format_string, std::forward<T>(number));
    else
      snwprintf(buffer, 32, format_string, std::forward<T>(number));
  }

  if constexpr (is_integral_v<data_type>) {
    if constexpr (is_signed_v<data_type>) {
      const long long value = std::forward<T>(number);
      if constexpr (std::is_same_v<char_type, char>)
        snprintf(buffer, 32, "%lld", value);
      else
        snwprintf(buffer, 32, L"%lld", value);
    } else {
      const unsigned long long value = std::forward<T>(number);
      if constexpr (std::is_same_v<char_type, char>)
        snprintf(buffer, 32, "%llu", value);
      else
        snwprintf(buffer, 32, L"%llu", value);
    }
  } else if constexpr (is_floating_point_v<data_type>) {
    if constexpr (is_same_v<float, data_type>) {
      if constexpr (std::is_same_v<char_type, char>)
        snprintf(buffer, 32, "%f", std::forward<T>(number));
      else
        snwprintf(buffer, 32, L"%f", std::forward<T>(number));
    } else {
      if constexpr (std::is_same_v<char_type, char>)
        snprintf(buffer, 32, "%lf", std::forward<T>(number));
      else
        snwprintf(buffer, 32, L"%lf", std::forward<T>(number));
    }
  } else {
    static char buffer[128]{};
    snprintf(buffer, 128,
             "Provided data type [%s] is not a valid primitive integral or "
             "floating point number type!",
             typeid(data_type).name());
    throw std::invalid_argument{buffer};
  }

  return buffer;
}

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (0U == str_len)
    return {};

  size_t begin_str{};
  size_t end_str{str_len - 1};

  for (; begin_str <= end_str; ++begin_str) {
    if (!isspace(str[begin_str]))
      break;
  }

  if (begin_str > end_str)
    return {};

  for (; end_str > begin_str; --end_str) {
    if (!isspace(str[end_str]))
      break;
  }

  return str.substr(begin_str, end_str - begin_str + 1);
}

template <
    typename T,
    typename U,
    typename = enable_if_t<
        (is_valid_string_type_v<T> || is_valid_string_view_type_v<T> ||
         is_char_array_type_v<T> ||
         is_char_pointer_type_v<
             T>)&&(is_valid_string_type_v<U> ||
                   is_valid_string_view_type_v<U> || is_char_array_type_v<U> ||
                   is_char_pointer_type_v<U>)&&(is_same_v<get_char_type_t<T>,
                                                          get_char_type_t<U>>)>>
vector<basic_string<get_char_type_t<T>>> split(
    const T& source,
    const U& needle,
    const bool split_on_whole_needle = true,
    const bool ignore_empty_string = true,
    size_t const max_count = basic_string<get_char_type_t<T>>::npos) {
  using char_type = get_char_type_t<T>;
  if constexpr (is_char_pointer_type_v<T>) {
    if (nullptr == source)
      return {};
  }
  const basic_string_view<char_type> sv{source};
  const size_t source_len{sv.length()};
  if (0U == source_len)
    return {};

  const basic_string_view<char_type> nv{needle};
  const size_t needle_len{split_on_whole_needle ? nv.length() : 1U};

  if (0U == needle_len) {
    const size_t upper_limit{max_count < source_len ? max_count : source_len};
    vector<basic_string<char_type>> parts(upper_limit);
    for (size_t i{}; i < upper_limit; i++)
      parts[i].assign({1, sv[i]});
    return parts;
  }

  vector<basic_string<char_type>> parts{};
  size_t number_of_parts{}, prev{};

  while (true) {
    const size_t current = split_on_whole_needle
                               ? sv.find(nv.data(), prev)
                               : sv.find_first_of(nv.data(), prev);

    if (basic_string<char_type>::npos == current)
      break;

    if (basic_string<char_type>::npos != max_count && parts.size() == max_count)
      break;

    if (current - prev > 0 || !ignore_empty_string) {
      if (!ignore_empty_string)
        parts.emplace_back();
      else
        parts.emplace_back(cbegin(sv) + prev, cbegin(sv) + current);
      number_of_parts++;
    }

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (prev < source_len &&
      (basic_string<char_type>::npos == max_count || parts.size() < max_count))
    parts.emplace_back(cbegin(sv) + prev, cend(sv));

  return parts;
}

string LetterCountI_v1(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  size_t start{};
  size_t count_of_max_repeated_letters{1};
  string_view word{};

  while (start < str_len) {
    start = str.find_first_not_of(' ', start);

    if (string::npos == start)
      break;

    size_t last{str.find_first_of(' ', start + 1)};

    if (string::npos == last)
      last = str_len;

    if (last - start > count_of_max_repeated_letters) {
      unordered_map<char, size_t> char_count{};

      for (size_t i{start}; i < last; i++)
        char_count[str[i]]++;

      size_t rep_char_count{};

      for (const auto& p : char_count) {
        if (p.second > 1)
          rep_char_count += p.second;
      }

      if (rep_char_count > count_of_max_repeated_letters) {
        count_of_max_repeated_letters = rep_char_count;
        word = string_view{str.c_str() + start, last - start};
      }
    }

    start = last + 1;
  }

  if (count_of_max_repeated_letters > 1)
    return string{word.data(), word.length()};

  return "-1";
}

string LetterCountI_v2(string str) {
  str = trim(str);

  vector<string> words{split(str, " \t\f\v\n\r", false)};

  bool found_word_with_repeated_characters{};

  stable_sort(begin(words), end(words),
              [&found_word_with_repeated_characters](const string& lhs,
                                                     const string& rhs) {
                unordered_map<char, size_t> char_count_lhs{};
                unordered_map<char, size_t> char_count_rhs{};
                const size_t lhs_len{lhs.length()};
                const size_t rhs_len{rhs.length()};
                const size_t min_len{!(lhs_len > rhs_len) ? lhs_len : rhs_len};
                const size_t max_len{!(lhs_len < rhs_len) ? lhs_len : rhs_len};
                const string& max_word{!(lhs_len < rhs_len) ? lhs : rhs};
                unordered_map<char, size_t>& char_count_max{
                    !(lhs_len < rhs_len) ? char_count_lhs : char_count_rhs};

                unordered_set<char> characters{};

                for (size_t i{}; i < min_len; ++i) {
                  char_count_lhs[lhs[i]]++;
                  char_count_rhs[rhs[i]]++;
                  if (0U == characters.count(lhs[i]))
                    characters.insert(lhs[i]);
                  if (0U == characters.count(rhs[i]))
                    characters.insert(rhs[i]);
                }

                for (size_t i{min_len}; i < max_len; ++i) {
                  char_count_max[max_word[i]]++;
                  if (0U == characters.count(max_word[i]))
                    characters.insert(max_word[i]);
                }

                size_t rep_char_count_lhs{}, rep_char_count_rhs{};

                for (const char ch : characters) {
                  if (char_count_lhs[ch] > 1U) {
                    rep_char_count_lhs += char_count_lhs[ch];
                    found_word_with_repeated_characters = true;
                  }
                  if (char_count_rhs[ch] > 1U) {
                    rep_char_count_rhs += char_count_rhs[ch];
                    found_word_with_repeated_characters = true;
                  }
                }

                return rep_char_count_lhs > rep_char_count_rhs;
              });

  if (found_word_with_repeated_characters)
    return move(words[0]);

  return "-1";
}

int main() {
  // cout << LetterCountI_v1(gets(stdin));
  cout << LetterCountI_v1("Today, is the greatest day ever!")
       << '\n';  // expected output: "greatest"
  cout << LetterCountI_v1("Hello apple pie")
       << '\n';                                 // expected output: "Hello"
  cout << LetterCountI_v1("No words") << '\n';  // expected output: "-1"

  return 0;
}
