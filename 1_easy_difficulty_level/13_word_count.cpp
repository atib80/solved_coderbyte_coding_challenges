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

template <typename T>
string number_to_string(const T& number) {
  static char buffer[32]{};
  if constexpr (is_integral_v<T>) {
    if constexpr (is_signed_v<T>) {
      const long long value = number;
      snprintf(buffer, 32, "%lld", value);
    }
    else {
      const unsigned long long value = number;
      snprintf(buffer, 32, "%llu", value);
    }
  } else if constexpr (is_floating_point_v<T>) {
    if constexpr (is_same_v<float, T>)
      snprintf(buffer, 32, "%f", number);
    else
      snprintf(buffer, 32, "%lf", number);
  } else {
    static char buffer[128]{};
    snprintf(buffer, 128,
             "Provided data type T [%s] is not a valid primitive integral or "
             "floating point number type!",
             typeid(T).name());
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

vector<string> split(const string& source,
                     const char* needle,
                     size_t const max_count = string::npos) {
  vector<string> parts{};

  const size_t source_len{source.length()};

  const size_t needle_len{strlen(needle)};

  if (!source_len)
    return parts;

  if (!needle_len) {
    const size_t upper_limit{max_count < source_len ? max_count : source_len};
    for (size_t i{}; i < upper_limit; i++)
      parts.emplace_back(1, source[i]);
    return parts;
  }

  size_t number_of_parts{}, prev{};

  while (true) {
    const size_t current{source.find(needle, prev)};

    if (string::npos == current)
      break;

    number_of_parts++;

    if (string::npos != max_count && parts.size() == max_count)
      break;

    if (current - prev > 0)
      parts.emplace_back(source.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (prev < source_len) {
    if (string::npos == max_count)
      parts.emplace_back(source.substr(prev));

    else if (parts.size() < max_count)
      parts.emplace_back(source.substr(prev));
  }

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

  return number_to_string(word_count);
}

string word_count_v2(string str) {
  str = trim(str);

  const vector<string> words{split(str, " ")};

  return number_to_string(words.size());
}

int main() {
  // cout << word_count_v2(gets(stdin));
  cout << word_count_v1("Never eat shredded wheat or cake")
       << '\n';                                   // expected output: 6
  cout << word_count_v1("Hello World") << '\n';   // expected output: 2
  cout << word_count_v1("one 22 three") << '\n';  // expected output: 3
  cout << word_count_v1("Coderbyte") << '\n';     // expected output: 1
  cout << word_count_v1("h333llLo") << '\n';      // expected output: 1
  cout << word_count_v1("Yo0") << '\n';           // expected output: 1
  cout << word_count_v1("commacomma!") << '\n';   // expected output: 1
  cout << word_count_v1("aq") << '\n';            // expected output: 1

  return 0;
}
