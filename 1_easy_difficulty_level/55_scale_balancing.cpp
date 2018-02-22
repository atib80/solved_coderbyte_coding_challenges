/*
Coderbyte coding challenge: Scale Balancing

Using the C++ language, have the function ScaleBalancing(strArr) read strArr
which will contain two elements, the first being the two positive integer
weights on a balance scale (left and right sides) and the second element being a
list of available weights as positive integers. Your goal is to determine if you
can balance the scale by using the least amount of weights from the list, but
using at most only 2 weights. For example: if strArr is ["[5, 9]", "[1, 2, 6,
7]"] then this means there is a balance scale with a weight of 5 on the left
side and 9 on the right side. It is in fact possible to balance this scale by
adding a 6 to the left side from the list of weights and adding a 2 to the right
side. Both scales will now equal 11 and they are perfectly balanced. Your
program should return a common separated string of the weights that were used
from the list in ascending order, so for this example your program should return
the string 2,6

There will only ever be one unique solution and the list of available weights
will not be empty. It is also possible to add two weights to only one side of
the scale to balance it. If it is not possible to balance the scale then your
program should return the string not possible.

Sample test cases:

Input:  "[3, 4]", "[1, 2, 7, 7]"
Output: "1"

Input:  "[13, 4]", "[1, 2, 3, 6, 14]"
Output: "3,6"
*/

#include <cctype>
#include <functional>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (!str_len)
    return string{};

  size_t begin_str{};
  size_t end_str{str_len - 1};

  for (; begin_str <= end_str; ++begin_str) {
    if (!isspace(str[begin_str]))
      break;
  }

  if (begin_str > end_str)
    return string{};

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

  string needle_st{needle};

  const size_t source_len{source.length()};

  const size_t needle_len{needle_st.size()};

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
    const size_t current{source.find(needle_st, prev)};

    if (string::npos == current)
      break;

    number_of_parts++;

    if ((string::npos != max_count) && (parts.size() == max_count))
      break;

    if ((current - prev) > 0)
      parts.emplace_back(source.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (prev < source_len) {
    if (string::npos == max_count)
      parts.emplace_back(source.substr(prev));

    else if ((string::npos != max_count) && (parts.size() < max_count))
      parts.emplace_back(source.substr(prev));
  }

  return parts;
}

string get_needed_weights_string(const size_t first_weight,
                                 const size_t second_weight) {
  ostringstream oss{};

  if (first_weight < second_weight) {
    oss << first_weight << ',' << second_weight;
  } else {
    oss << second_weight << ',' << first_weight;
  }

  return oss.str();
}

pair<int, int> get_left_and_right_scale_weights(string str) {
  str = trim(str);
  str.erase(begin(str));
  str.erase(--end(str));

  auto left_right_scale_str = split(str, ",");
  for (auto& str_part : left_right_scale_str)
    str_part = trim(str_part);
  if (2 != left_right_scale_str.size())
    return make_pair(0, 0);

  return make_pair(stoi(left_right_scale_str[0]),
                   stoi(left_right_scale_str[1]));
}

multiset<int, greater<int>> get_available_weights_in_descending_order(
    string str) {
  str = trim(str);
  str.erase(begin(str));
  str.erase(--end(str));

  auto weights_str = split(str, ",");
  for (auto& str_part : weights_str)
    str_part = trim(str_part);

  multiset<int, greater<int>> available_weights_in_desc_order{};

  for (const auto& weight_str : weights_str)
    available_weights_in_desc_order.insert(stoi(weight_str));

  return available_weights_in_desc_order;
}

string ScaleBalancing(string* str_arr, const size_t array_size) {
  if (array_size < 2)
    return "not possible";

  const pair<int, int> left_and_right_scale_weigths{
      get_left_and_right_scale_weights(move(str_arr[0]))};

  const int left_scale{left_and_right_scale_weigths.first};
  const int right_scale{left_and_right_scale_weigths.second};
  if (left_scale == right_scale)
    return "Scale is already balanced.";

  const multiset<int, greater<int>> available_weights_in_desc_order{
      get_available_weights_in_descending_order(move(str_arr[1]))};

  const int needed_extra_weight{left_scale > right_scale
                                    ? left_scale - right_scale
                                    : right_scale - left_scale};

  const auto found_needed_weight =
      available_weights_in_desc_order.find(needed_extra_weight);

  if (found_needed_weight != end(available_weights_in_desc_order)) {
    return to_string(*found_needed_weight);
  }

  auto last_weight_iter = end(available_weights_in_desc_order);
  --last_weight_iter;

  for (auto start = begin(available_weights_in_desc_order);
       start != last_weight_iter; ++start) {
    int first_weight{};

    for (auto next = start; next != end(available_weights_in_desc_order);
         ++next) {
      if (*next > needed_extra_weight)
        continue;

      const int current_weight{*next};

      if (!first_weight) {
        first_weight = current_weight;

        continue;
      }

      if (first_weight + current_weight == needed_extra_weight) {
        return get_needed_weights_string(first_weight, current_weight);
      }
    }
  }

  multiset<int> available_weights_in_asc_order(
      begin(available_weights_in_desc_order),
      end(available_weights_in_desc_order));

  for (auto start1 = begin(available_weights_in_asc_order);
       start1 != end(available_weights_in_asc_order); ++start1) {
    for (auto start2 = begin(available_weights_in_asc_order);
         start2 != end(available_weights_in_asc_order); ++start2) {
      if (left_scale + *start1 == right_scale + *start2) {
        return get_needed_weights_string(*start1, *start2);
      }

      if (left_scale + *start2 == right_scale + *start1) {
        return get_needed_weights_string(*start2, *start1);
      }
    }
  }

  return "not possible";
}

int main() {
  // string a[] = gets(stdin);
  string a[] = {"[3, 4]", "[1, 2, 7, 7]"};
  cout << ScaleBalancing(a, sizeof(a) / sizeof(*a))
       << '\n';  // expected output: "1"
  string b[] = {"[13, 4]", "[1, 2, 3, 6, 14]"};
  cout << ScaleBalancing(b, sizeof(b) / sizeof(*b))
       << '\n';  // expected output: "3,6"
  string c[] = {"[5, 9]", "[1, 2, 6, 7]"};
  cout << ScaleBalancing(c, sizeof(c) / sizeof(*c))
       << '\n';  // expected output: "2,6"
  string d[] = {"[6, 2]", "[1, 10, 6, 5]"};
  cout << ScaleBalancing(d, sizeof(d) / sizeof(*d))
       << '\n';  // expected output: "1,5"

  return 0;
}
