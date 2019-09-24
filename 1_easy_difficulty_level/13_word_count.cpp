/*
Coderbyte coding challenge: Word Count

Using the C++ language, have the function WordCount(str) take the str string
parameter being passed and return the number of words the string contains (e.g.
"Never eat shredded wheat or cake" would return 6). Words will be separated by
single spaces.

Sample test cases:

Input:  "Hello World"
Output: 2

Input:  "one 22 three"
Output: 3
*/

#include <cctype>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <typeinfo>
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

template <typename StreamType, typename T>
using has_output_stream_operator_type_t =
    decltype(std::declval<StreamType&>() << std::declval<T>());

template <typename StreamType, typename T, typename = void>
struct has_output_stream_operator : std::false_type {};

template <typename StreamType, typename T>
struct has_output_stream_operator<
    StreamType,
    T,
    std::void_t<has_output_stream_operator_type_t<StreamType, T>>>
    : std::true_type {};

template <typename StreamType, typename T>
constexpr const bool has_output_stream_operator_v =
    has_output_stream_operator<StreamType, T>::value;

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

template <typename T,
          typename FormatStringType = const char*,
          typename = std::enable_if_t<
              has_output_stream_operator_v<
                  std::basic_ostream<get_char_type_t<FormatStringType>>,
                  std::remove_reference_t<T>> &&
              is_valid_char_type_v<get_char_type_t<FormatStringType>> &&
              is_anyone_of_v<get_char_type_t<FormatStringType>, char, wchar_t>>>
std::basic_string<get_char_type_t<FormatStringType>> to_str(
    T&& data,
    FormatStringType format_string = nullptr) {
  using char_type = get_char_type_t<FormatStringType>;
  using data_type = remove_all_decorations_t<T>;

  static constexpr const size_t buf_size{32};

  static char_type buffer[buf_size]{};

  if (nullptr != format_string) {
    if constexpr (!std::is_integral_v<data_type> &&
                  !std::is_floating_point_v<data_type>) {
      std::basic_ostringstream<char_type> oss{};
      oss << std::forward<T>(data);
      return oss.str();
    } else if constexpr (std::is_same_v<char_type, char>)
      snprintf(buffer, buf_size, format_string, std::forward<T>(data));
    else
      snwprintf(buffer, buf_size, format_string, std::forward<T>(data));

      return buffer;
  }

  if constexpr (std::is_integral_v<data_type>) {
    if constexpr (std::is_signed_v<data_type>) {
      const long long value{std::forward<T>(data)};
      if constexpr (std::is_same_v<char_type, char>)
        snprintf(buffer, buf_size, "%lld", value);
      else
        snwprintf(buffer, buf_size, L"%lld", value);
    } else {
      const unsigned long long value{std::forward<T>(data)};
      if constexpr (std::is_same_v<char_type, char>)
        snprintf(buffer, buf_size, "%llu", value);
      else
        snwprintf(buffer, buf_size, L"%llu", value);
    }
  } else if constexpr (std::is_floating_point_v<data_type>) {
    if constexpr (std::is_same_v<float, data_type>) {
      if constexpr (std::is_same_v<char_type, char>)
        snprintf(buffer, buf_size, "%f", std::forward<T>(data));
      else
        snwprintf(buffer, buf_size, L"%f", std::forward<T>(data));
    } else if constexpr (std::is_same_v<double, data_type>) {
      if constexpr (std::is_same_v<char_type, char>)
        snprintf(buffer, buf_size, "%lf", std::forward<T>(data));
      else
        snwprintf(buffer, buf_size, L"%lf", std::forward<T>(data));
    } else {
      if constexpr (std::is_same_v<char_type, char>)
        snprintf(buffer, buf_size, "%Lf", std::forward<T>(data));
      else
        snwprintf(buffer, buf_size, L"%Lf", std::forward<T>(data));
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

string trim(const string& str, const locale& loc = locale{}) {
  const size_t str_len{str.length()};

  if (0U == str_len)
    return {};

  size_t begin_str{};
  size_t end_str{str_len - 1};

  for (; begin_str <= end_str; ++begin_str) {
    if (!isspace(str[begin_str], loc))
      break;
  }

  if (begin_str > end_str)
    return {};

  for (; end_str > begin_str; --end_str) {
    if (!isspace(str[end_str], loc))
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

string word_count_v1(string str) {
  str = trim(str);

  const size_t str_len{str.length()};

  size_t word_count{};
  size_t start{};

  while (start < str_len) {
    start = str.find_first_not_of(" \t\n\v\f", start);

    if (string::npos == start)
      break;

    const size_t last{str.find_first_of(" \t\n\v\f", start + 1)};

    if (string::npos == last) {
      word_count++;
      break;
    }

    word_count++;

    start = last + 1;
  }

  return to_str(word_count);
}

string word_count_v2(string str) {
  str = trim(str);

  const vector<string> words{split(str, " ")};

  return to_str(words.size());
}

int main() {
  // cout << word_count_v2(gets(stdin));
  cout << word_count_v2("Never eat shredded wheat or cake")
       << '\n';                                   // expected output: 6
  cout << word_count_v2("Hello World") << '\n';   // expected output: 2
  cout << word_count_v2("one 22 three") << '\n';  // expected output: 3
  cout << word_count_v2("Coderbyte") << '\n';     // expected output: 1
  cout << word_count_v2("h333llLo") << '\n';      // expected output: 1
  cout << word_count_v2("Yo0") << '\n';           // expected output: 1
  cout << word_count_v2("commacomma!") << '\n';   // expected output: 1
  cout << word_count_v2("aq") << '\n';            // expected output: 1

  return 0;
}
