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
#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string get_needed_weights_string(int first_weight, int second_weight) {
  char buffer[32];
  if (first_weight > second_weight)
    swap(first_weight, second_weight);
  sprintf(buffer, "%d,%d", first_weight, second_weight);

  return buffer;
}

template <typename FwIterType, typename T = int>
T get_decimal_value(FwIterType start, const FwIterType last) {
  T result{};

  while (start != last) {
    result *= 10;
    result += static_cast<T>(*start - '0');
    ++start;
  }

  return result;
}

pair<int, int> get_left_and_right_scale_weights(const string& str) {
  size_t start{str.find_first_of("1234567890")};
  if (string::npos == start)
    return {0, 0};
  size_t last{str.find_first_not_of("0123456789", start + 1)};
  if (string::npos == last)
    last = str.length();

  pair<int, int> left_right_scale_weights{
      get_decimal_value(cbegin(str) + start, cbegin(str) + last), 0};

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

vector<int> get_available_weights_in_descending_order(const string& str) {
  vector<int> available_weights_in_desc_order;
  available_weights_in_desc_order.reserve(10);

  size_t start{};

  while (start < str.length()) {
    start = str.find_first_of("1234567890", start);
    if (string::npos == start)
      break;
    size_t last{str.find_first_not_of("0123456789", start + 1)};
    if (string::npos == last)
      last = str.length();
    available_weights_in_desc_order.emplace_back(
        get_decimal_value(cbegin(str) + start, cbegin(str) + last));
    start = last + 1;
  }

  sort(begin(available_weights_in_desc_order),
       end(available_weights_in_desc_order),
       [](const int ln, const int rn) { return ln > rn; });

  return available_weights_in_desc_order;
}

string ScaleBalancing(const string* str_arr, const size_t array_size) {
  if (array_size < 2U)
    return "not possible";

  const pair<int, int> left_and_right_scale_weigths{
      get_left_and_right_scale_weights(str_arr[0])};

  const int& left_scale{left_and_right_scale_weigths.first};
  const int& right_scale{left_and_right_scale_weigths.second};
  if (left_scale == right_scale)
    return "Scale is already balanced.";

  vector<int> available_weights_in_desc_order{
      get_available_weights_in_descending_order(str_arr[1])};

  const int needed_extra_weight{left_scale > right_scale
                                    ? left_scale - right_scale
                                    : right_scale - left_scale};

  if (binary_search(cbegin(available_weights_in_desc_order),
                    cend(available_weights_in_desc_order), needed_extra_weight,
                    greater<int>{}))
    return to_string(needed_extra_weight);

  auto last_weight_iter{cend(available_weights_in_desc_order)};
  --last_weight_iter;

  for (auto start{cbegin(available_weights_in_desc_order)};
       start != last_weight_iter; ++start) {
    int first_weight{};

    for (auto next = start; next != cend(available_weights_in_desc_order);
         ++next) {
      if (*next < needed_extra_weight) {
        const int current_weight{*next};

        if (0 == first_weight)
          first_weight = current_weight;
        else if (first_weight + current_weight == needed_extra_weight)
          return get_needed_weights_string(first_weight, current_weight);
      }
    }
  }

  reverse(begin(available_weights_in_desc_order),
          end(available_weights_in_desc_order));

  for (auto start1{cbegin(available_weights_in_desc_order)};
       start1 != cend(available_weights_in_desc_order); ++start1) {
    for (auto start2{cbegin(available_weights_in_desc_order)};
         start2 != cend(available_weights_in_desc_order); ++start2) {
      if (left_scale + *start1 == right_scale + *start2)
        return get_needed_weights_string(*start1, *start2);

      if (left_scale + *start2 == right_scale + *start1)
        return get_needed_weights_string(*start2, *start1);
    }
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
