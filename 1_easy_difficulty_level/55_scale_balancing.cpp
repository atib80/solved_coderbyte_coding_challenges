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

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

string get_needed_weights_string(size_t first_weight, size_t second_weight) {
  if (first_weight > second_weight)
    swap(first_weight, second_weight);

  return to_string(first_weight) + ',' + to_string(second_weight);
}

template <typename FwIterType>
size_t get_decimal_value(FwIterType start, const FwIterType last) {
  size_t result{};

  while (start != last) {
    result =
        (result << 3U) + (result << 1U) + static_cast<size_t>(*start - '0');
    ++start;
  }

  return result;
}

pair<size_t, size_t> get_left_and_right_scale_weights(const string& str) {
  size_t start{str.find_first_of("1234567890")};
  if (string::npos == start)
    return {0, 0};
  size_t last{str.find_first_not_of("0123456789", start + 1)};
  if (string::npos == last)
    last = str.length();

  pair<size_t, size_t> left_right_scale_weights{
      get_decimal_value(cbegin(str) + start, cbegin(str) + last), 0U};

  start = str.find_first_of("1234567890", last + 1);
  if (string::npos == start)
    return left_right_scale_weights;
  last = str.find_first_not_of("0123456789", start + 1);
  if (string::npos == last)
    last = str.length();

  left_right_scale_weights.second =
      get_decimal_value(cbegin(str) + start, cbegin(str) + last);

  return left_right_scale_weights;
}

pair<vector<size_t>, unordered_map<size_t, size_t>> get_available_weights(
    const string& str) {
  vector<size_t> available_weights{};
  available_weights.reserve(10);
  unordered_map<size_t, size_t> weight_count{};

  size_t start{};

  while (start < str.length()) {
    start = str.find_first_of("1234567890", start);
    if (string::npos == start)
      break;
    size_t last{str.find_first_not_of("0123456789", start + 1)};
    if (string::npos == last)
      last = str.length();
    const size_t weight_value{
        get_decimal_value(cbegin(str) + start, cbegin(str) + last)};
    if (0U == weight_count.count(weight_value))
      available_weights.emplace_back(weight_value);
    weight_count[weight_value]++;
    start = last + 1;
  }

  sort(begin(available_weights), end(available_weights));
  return {available_weights, weight_count};
}

string ScaleBalancing(const string* str_arr, const size_t array_size) {
  if (array_size < 2U)
    return "not possible";

  const auto [left_scale,
              right_scale]{get_left_and_right_scale_weights(str_arr[0])};

  if (left_scale == right_scale)
    return "Scale is already balanced.";

  auto [available_weights, weight_count]{get_available_weights(str_arr[1])};

  const size_t needed_extra_weight{left_scale > right_scale
                                       ? left_scale - right_scale
                                       : right_scale - left_scale};

  if (weight_count.find(needed_extra_weight) != end(weight_count))
    return to_string(needed_extra_weight);

  for (size_t i{};
       i < static_cast<size_t>(upper_bound(cbegin(available_weights),
                                           cend(available_weights),
                                           needed_extra_weight) -
                               cbegin(available_weights));
       ++i) {
    --weight_count.at(available_weights[i]);
    const size_t needed_second_weight{needed_extra_weight -
                                      available_weights[i]};
    if (weight_count.find(needed_second_weight) != end(weight_count) &&
        0U != weight_count.at(needed_second_weight))
      return get_needed_weights_string(available_weights[i],
                                       needed_second_weight);
    ++weight_count.at(available_weights[i]);
  }

  for (size_t i{}; i < available_weights.size(); ++i) {
    --weight_count.at(available_weights[i]);
    const size_t missing_second_weight1{left_scale + available_weights[i] -
                                        right_scale};
    if (weight_count.find(missing_second_weight1) != end(weight_count) &&
        0U != weight_count.at(missing_second_weight1))
      return get_needed_weights_string(available_weights[i],
                                       missing_second_weight1);
    const size_t missing_second_weight2{right_scale + available_weights[i] -
                                        left_scale};

    if (weight_count.find(missing_second_weight2) != end(weight_count) &&
        0U != weight_count.at(missing_second_weight2))
      return get_needed_weights_string(available_weights[i],
                                       missing_second_weight2);
    ++weight_count.at(available_weights[i]);
  }

  return "not possible";
}

int main() {
  // const string a[] = gets(stdin);
  const string a[]{"[3, 4]", "[1, 2, 7, 7]"};
  cout << ScaleBalancing(a, sizeof(a) / sizeof(*a))
       << '\n';  // expected output: "1"
  const string b[]{"[13, 4]", "[1, 2, 3, 6, 14]"};
  cout << ScaleBalancing(b, sizeof(b) / sizeof(*b))
       << '\n';  // expected output: "3,6"
  const string c[]{"[5, 9]", "[1, 2, 6, 7]"};
  cout << ScaleBalancing(c, sizeof(c) / sizeof(*c))
       << '\n';  // expected output: "2,6"
  const string d[]{"[6, 2]", "[1, 10, 6, 5]"};
  cout << ScaleBalancing(d, sizeof(d) / sizeof(*d))
       << '\n';  // expected output: "1,5"

  return 0;
}
