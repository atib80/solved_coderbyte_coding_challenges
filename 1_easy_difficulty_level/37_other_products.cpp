/*
Coderbyte coding challenge: Other Products

Using the C++ language, have the function OtherProducts(arr) take the array of
numbers stored in arr and return a new list of the products of all the other
numbers in the array for each element. For example: if arr is [1, 2, 3, 4, 5]
then the new array, where each location in the new array is the product of all
other elements, is [120, 60, 40, 30, 24]. The following calculations were
performed to get this answer: [(2*3*4*5), (1*3*4*5), (1*2*4*5), (1*2*3*5),
(1*2*3*4)]. You should generate this new array and then return the numbers as a
string joined by a hyphen: 120-60-40-30-24. The array will contain at most 10
elements and at least 1 element of only positive integers.

Sample test cases:

Input:  1,4,3
Output: "12-3-4"

Input:  3,1,2,6
Output: "12-36-18-6"
*/

#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

using namespace std;

// alias template 'has_cbegin_member_function_t' type function checks if
// typename 'T' has a cbegin() member function
template <typename T>
using has_cbegin_member_function_t = decltype(std::declval<T&>().cbegin());

template <typename T, typename = void>
struct has_cbegin_member_function : std::false_type {};

template <typename T>
struct has_cbegin_member_function<T,
                                  std::void_t<has_cbegin_member_function_t<T>>>
    : std::true_type {};

template <typename T>
constexpr const bool has_cbegin_member_function_v =
    has_cbegin_member_function<T>::value;

// alias template 'has_cend_member_function_t' type function checks if typename
// 'T' has a cend() member function
template <typename T>
using has_cend_member_function_t = decltype(std::declval<T&>().cend());

template <typename T, typename = void>
struct has_cend_member_function : std::false_type {};

template <typename T>
struct has_cend_member_function<T, std::void_t<has_cend_member_function_t<T>>>
    : std::true_type {};

template <typename T>
constexpr const bool has_cend_member_function_v =
    has_cend_member_function<T>::value;

// alias template 'has_output_stream_operator_type_t' type function checks if
// typename 'T' has a valid operator<<(StreamType&, const T&) member function,
// overloaded output operator defined for specified output stream type
// 'StreamType'
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

template <typename ContainerType,
          typename NeedleType,
          typename = enable_if_t<
              has_cbegin_member_function_v<ContainerType> &&
              has_cend_member_function_v<ContainerType> &&
              has_output_stream_operator_v<ostringstream, NeedleType>>>
string join(const ContainerType& items, const NeedleType& needle) {
  ostringstream oss{};
  auto start = cbegin(items);
  const auto last = cend(items);

  if (start == last)
    return {};

  while (true) {
    oss << *start;
    ++start;
    if (start == last)
      break;
    oss << needle;
  }

  return oss.str();
}

string OtherProducts(const int64_t* numbers, const size_t numbers_size) {
  if (0U == numbers_size)
    return "not possible";

  if (1U == numbers_size)
    return to_string(numbers[0]);

  vector<int64_t> products(numbers_size);

  for (size_t i{}; i < numbers_size; ++i) {
    int64_t product{1};

    for (size_t j{}; j < numbers_size; ++j) {
      if (i == j)
        continue;

      product *= numbers[j];
    }

    products[i] = product;
  }

  return join(products, '-');
}

int main() {
  // const int64_t A[] = gets(stdin);
  // cout << OtherProducts(A, sizeof(A)/sizeof(*A));
  const int64_t B[]{1, 2, 3, 4, 5};
  cout << OtherProducts(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "120-60-40-30-24"
  const int64_t C[]{1, 4, 3};
  cout << OtherProducts(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "12-3-4"
  const int64_t D[]{3, 1, 2, 6};
  cout << OtherProducts(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "12-36-18-6"

  return 0;
}
