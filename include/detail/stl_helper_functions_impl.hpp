#ifndef _STL_HELPER_FUNCTIONS_IMPL_HPP_
#define _STL_HELPER_FUNCTIONS_IMPL_HPP_

#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS

#include <algorithm>
#include <array>
#include <chrono>
#include <cinttypes>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cwchar>
#include <deque>
#include <forward_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace stl::helper::detail {

#if defined(_MSC_VER)
#if defined(_MSVC_LANG) && _MSVC_LANG < 201703L
#error \
    "You need a modern compiler that is fully compliant with the c++17 language standard or a newer one in order to use this header-only library!"
#endif
#elif defined(__cplusplus) && __cplusplus < 201703L
#error \
    "You need a modern compiler that is fully compliant with the c++17 language standard or a newer one in order to use this header-only library!"
#endif

#ifdef _MSC_VER
#include <Strsafe.h>
#include <windows.h>
#define SNPRINTF StringCchPrintfA
#define SNWPRINTF StringCchPrintfW
#else
#define SNPRINTF snprintf
#define SNWPRINTF swprintf
#endif

#define PRINT_VAR_NAME(arg) std::cout << #arg << ' '
#define PRINT_VAR_NAMEW(arg) std::wcout << #arg << L' '

#if defined(__LP64__) || defined(_M_AMD64) || defined(_M_X64)
#define SIZE_T_PFORMAT PRIu64
#else
#define SIZE_T_PFORMAT PRIu32
#endif

#if (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L) || \
    (defined(__cplusplus) && __cplusplus >= 202002L)
#define CPP20_USE_CONSTEXPR constexpr
#else
#define CPP20_USE_CONSTEXPR
#endif

template <typename T, typename... T0_TN>
struct is_all_of_impl;

template <typename T>
struct is_all_of_impl<T> : std::true_type {};

template <typename T, typename... T1_TN>
struct is_all_of_impl<T, T, T1_TN...> : is_all_of_impl<T, T1_TN...> {};

template <typename T, typename T0, typename... T1_TN>
struct is_all_of_impl<T, T0, T1_TN...> : std::false_type {};

template <typename T, typename... T0_TN>
struct is_anyone_of_impl;

template <typename T>
struct is_anyone_of_impl<T> : std::false_type {};

template <typename T, typename... T1_TN>
struct is_anyone_of_impl<T, T, T1_TN...> : std::true_type {};

template <typename T, typename T0, typename... T1_TN>
struct is_anyone_of_impl<T, T0, T1_TN...> : is_anyone_of_impl<T, T1_TN...> {};

template <typename T>
struct is_valid_char_type {
  static constexpr const bool value = is_anyone_of_impl<std::remove_cv_t<T>,
                                                        char,
                                                        wchar_t,
                                                        char16_t,
                                                        char32_t
#if defined(__cpp_char8_t) && __cpp_char8_t >= 201811L
                                                        ,
                                                        char8_t
#endif
                                                        >::value;
};

template <typename T, typename = std::enable_if_t<is_valid_char_type<T>::value>>
std::vector<size_t> str_find_all_of_impl(std::basic_string_view<T> src_sv,
                                         std::basic_string_view<T> needle_sv,
                                         const size_t start_pos = 0U) {
  std::vector<size_t> start_indices{};
  size_t search_pos{start_pos};
  const size_t not_found_index{std::basic_string_view<T>::npos};

  while (search_pos <= src_sv.length() - needle_sv.length()) {
    search_pos = src_sv.find(needle_sv, search_pos);
    if (not_found_index == search_pos)
      break;
    start_indices.emplace_back(search_pos);
    search_pos += needle_sv.length();
  }

  return start_indices;
}

struct array_like_container_tag {};

struct vector_like_container_tag {};

struct list_like_container_tag {};

struct associative_like_container_tag {};

template <typename C>
struct container_traits;

// partial specializations for those sequential STL container data types that
// are similar to std::vector<T, A>

template <typename T, size_t N>
struct container_traits<T[N]> {
  using category = array_like_container_tag;
};

template <typename T, size_t N>
struct container_traits<std::array<T, N>> {
  using category = array_like_container_tag;
};

template <typename T, typename A>
struct container_traits<std::vector<T, A>> {
  using category = vector_like_container_tag;
};

template <typename T, typename A>
struct container_traits<std::deque<T, A>> {
  using category = vector_like_container_tag;
};

// partial specializations for those sequential STL container data types that
// are similar to std::list<T, A>

template <typename T, typename A>
struct container_traits<std::list<T, A>> {
  using category = list_like_container_tag;
};

template <typename T, typename A>
struct container_traits<std::forward_list<T, A>> {
  using category = list_like_container_tag;
};

// partial specializations for those associative STL container types that are
// similar to std::set<T, C, A> and std::map<K, V, C, A>

template <typename T, typename C, typename A>
struct container_traits<std::set<T, C, A>> {
  using category = associative_like_container_tag;
};

template <typename T, typename C, typename A>
struct container_traits<std::multiset<T, C, A>> {
  using category = associative_like_container_tag;
};

template <typename T, typename C, typename A>
struct container_traits<std::unordered_set<T, C, A>> {
  using category = associative_like_container_tag;
};

template <typename T, typename C, typename A>
struct container_traits<std::unordered_multiset<T, C, A>> {
  using category = associative_like_container_tag;
};

template <typename K, typename V, typename C, typename A>
struct container_traits<std::map<K, V, C, A>> {
  using category = associative_like_container_tag;
};

template <typename K, typename V, typename C, typename A>
struct container_traits<std::multimap<K, V, C, A>> {
  using category = associative_like_container_tag;
};

template <typename K, typename V, typename C, typename A>
struct container_traits<std::unordered_map<K, V, C, A>> {
  using category = associative_like_container_tag;
};

template <typename K, typename V, typename C, typename A>
struct container_traits<std::unordered_multimap<K, V, C, A>> {
  using category = associative_like_container_tag;
};

template <typename T, size_t N, typename X>
CPP20_USE_CONSTEXPR bool erase_first_impl(T (&arr)[N],
                                          const X& x,
                                          array_like_container_tag) {
  auto iter = std::find(arr, arr + N, x);

  if (iter == arr + N) {
    return false;
  }

  for (auto prev = iter++; iter != arr + N; ++prev, ++iter) {
    *prev = *iter;
  }

  return true;
}

template <typename T, size_t N, typename X>
CPP20_USE_CONSTEXPR bool erase_last_impl(T (&arr)[N],
                                         const X& x,
                                         array_like_container_tag) {
  auto iter = arr + N;
  while (iter != arr) {
    auto current = --iter;
    if (x == *current) {
      for (auto prev = current++; current != arr + N; ++prev, ++current) {
        *prev = *current;
      }

      return true;
    }
  }

  return false;
}

template <typename T, size_t N, typename X>
CPP20_USE_CONSTEXPR bool erase_all_impl(T (&arr)[N],
                                        const X& x,
                                        array_like_container_tag) {
  return std::remove(arr, arr + N, x) != arr + N;
}

template <typename T, size_t N, typename Pred>
CPP20_USE_CONSTEXPR bool erase_first_if_impl(T (&arr)[N],
                                             Pred p,
                                             array_like_container_tag) {
  auto iter = std::find_if(arr, arr + N, p);

  if (iter == arr + N) {
    return false;
  }

  for (auto prev = iter++; iter != arr + N; ++prev, ++iter) {
    *prev = *iter;
  }

  return true;
}

template <typename T, size_t N, typename Pred>
CPP20_USE_CONSTEXPR bool erase_last_if_impl(T (&arr)[N],
                                            Pred p,
                                            array_like_container_tag) {
  auto iter = arr + N;
  while (iter != arr) {
    auto current = --iter;
    if (p(*current)) {
      for (auto prev = current++; current != arr + N; ++prev, ++current) {
        *prev = *current;
      }

      return true;
    }
  }

  return false;
}

template <typename T, size_t N, typename Pred>
CPP20_USE_CONSTEXPR bool erase_all_if_impl(T (&arr)[N],
                                           Pred p,
                                           array_like_container_tag) {
  return std::remove_if(arr, arr + N, p) != arr + N;
}

template <typename T, size_t N, typename X>
CPP20_USE_CONSTEXPR bool erase_first_impl(std::array<T, N>& c,
                                          const X& x,
                                          array_like_container_tag) {
  auto iter = std::find(c.begin(), c.end(), x);

  if (iter == c.end()) {
    return false;
  }

  for (auto prev = iter++; iter != c.end(); ++prev, ++iter) {
    *prev = *iter;
  }

  return true;
}

template <typename T, size_t N, typename X>
CPP20_USE_CONSTEXPR bool erase_last_impl(std::array<T, N>& c,
                                         const X& x,
                                         array_like_container_tag) {
  auto iter = std::find(c.rbegin(), c.rend(), x);

  if (iter == c.rend()) {
    return false;
  }

  for (auto prev = (iter + 1).base(), next = prev + 1; next != c.end();
       ++prev, ++next) {
    *prev = *next;
  }

  return true;
}

template <typename T, size_t N, typename X>
CPP20_USE_CONSTEXPR bool erase_all_impl(std::array<T, N>& c,
                                        const X& x,
                                        array_like_container_tag) {
  return std::remove(c.begin(), c.end(), x) != c.end();
}

template <typename T, size_t N, typename Pred>
CPP20_USE_CONSTEXPR bool erase_first_if_impl(std::array<T, N>& c,
                                             Pred p,
                                             array_like_container_tag) {
  auto iter = std::find_if(c.begin(), c.end(), p);

  if (iter == c.end()) {
    return false;
  }

  for (auto prev = iter++; iter != c.end(); ++prev, ++iter) {
    *prev = *iter;
  }

  return true;
}

template <typename T, size_t N, typename Pred>
CPP20_USE_CONSTEXPR bool erase_last_if_impl(std::array<T, N>& c,
                                            Pred p,
                                            array_like_container_tag) {
  auto iter = std::find_if(c.rbegin(), c.rend(), p);

  if (iter == c.rend()) {
    return false;
  }

  for (auto prev = (iter + 1).base(), next = prev + 1; next != c.end();
       ++prev, ++next) {
    *prev = *next;
  }

  return true;
}

template <typename T, size_t N, typename Pred>
CPP20_USE_CONSTEXPR bool erase_all_if_impl(std::array<T, N>& c,
                                           Pred p,
                                           array_like_container_tag) {
  return std::remove_if(c.begin(), c.end(), p) != c.end();
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR bool erase_first_impl(Container& c,
                                          const X& x,
                                          vector_like_container_tag) {
  const auto found_pos_iter = std::find(c.cbegin(), c.cend(), x);

  if (found_pos_iter == c.cend()) {
    return false;
  }

  c.erase(found_pos_iter);

  return true;
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR bool erase_last_impl(Container& c,
                                         const X& x,
                                         vector_like_container_tag) {
  const auto found_pos_iter = std::find(c.crbegin(), c.crend(), x);

  if (found_pos_iter == c.crend()) {
    return false;
  }

  c.erase((found_pos_iter + 1).base());

  return true;
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR bool erase_all_impl(Container& c,
                                        const X& x,
                                        vector_like_container_tag) {
  const size_t original_size = c.size();
  c.erase(std::remove(c.begin(), c.end(), x), c.end());
  return c.size() < original_size;
}

template <typename Container, typename Pred>
CPP20_USE_CONSTEXPR bool erase_first_if_impl(Container& c,
                                             Pred p,
                                             vector_like_container_tag) {
  const auto found_pos_iter = std::find_if(c.cbegin, c.cend(), p);

  if (found_pos_iter == c.cend()) {
    return false;
  }

  c.erase(found_pos_iter);

  return true;
}

template <typename Container, typename Pred>
CPP20_USE_CONSTEXPR bool erase_last_if_impl(Container& c,
                                            Pred p,
                                            vector_like_container_tag) {
  const auto found_pos_iter = std::find_if(c.crbegin(), c.crend(), p);

  if (found_pos_iter == c.crend()) {
    return false;
  }

  c.erase((found_pos_iter + 1).base());

  return true;
}

template <typename Container, typename Pred>
CPP20_USE_CONSTEXPR bool erase_all_if_impl(Container& c,
                                           Pred p,
                                           vector_like_container_tag) {
  const size_t original_size = c.size();
  c.erase(std::remove_if(c.begin(), c.end(), p), c.end());
  return c.size() < original_size;
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR bool erase_first_impl(Container& c,
                                          const X& x,
                                          list_like_container_tag) {
  for (auto iter = c.cbegin(); iter != c.cend(); ++iter) {
    if (x == *iter) {
      c.erase(iter);
      return true;
    }
  }

  return false;
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR bool erase_last_impl(Container& c,
                                         const X& x,
                                         list_like_container_tag) {
  if constexpr (std::is_same_v<
                    typename std::iterator_traits<
                        typename Container::const_iterator>::iterator_category,
                    std::forward_iterator_tag>) {
    auto iter = c.cend();

    for (auto curr = c.cbegin();
         (curr = std::find(curr, c.cend(), x)) != c.cend();) {
      iter = curr;
      ++curr;
    }

    if (iter != c.cend()) {
      c.erase(iter);
      return true;
    }

    return false;
  } else {
    auto found_pos_iter = std::find(c.crbegin(), c.crend(), x);

    if (found_pos_iter == c.crend()) {
      return false;
    }

    c.erase((++found_pos_iter).base());
    return true;
  }
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR bool erase_all_impl(Container& c,
                                        const X& x,
                                        list_like_container_tag) {
  const size_t original_size = c.size();
  c.remove(x);
  return c.size() < original_size;
}

template <typename Container, typename Pred>
CPP20_USE_CONSTEXPR bool erase_first_if_impl(Container& c,
                                             Pred p,
                                             list_like_container_tag) {
  for (auto iter = c.cbegin(); iter != c.cend(); ++iter) {
    if (p(*iter)) {
      c.erase(iter);
      return true;
    }
  }

  return false;
}

template <typename Container, typename Pred>
CPP20_USE_CONSTEXPR bool erase_last_if_impl(Container& c,
                                            Pred p,
                                            list_like_container_tag) {
  if constexpr (std::is_same_v<
                    typename std::iterator_traits<
                        typename Container::const_iterator>::iterator_category,
                    std::forward_iterator_tag>) {
    auto iter = c.cend();

    for (auto curr = c.cbegin();
         (curr = std::find_if(curr, c.cend(), p)) != c.cend();) {
      iter = curr;
      ++curr;
    }

    if (iter != c.cend()) {
      c.erase(iter);
      return true;
    }
    return false;
  } else {
    auto found_pos_iter = std::find_if(c.crbegin(), c.crend(), p);

    if (found_pos_iter == c.crend()) {
      return false;
    }

    c.erase((++found_pos_iter).base());
    return true;
  }
}

template <typename Container, typename Pred>
CPP20_USE_CONSTEXPR bool erase_all_if_impl(Container& c,
                                           Pred p,
                                           list_like_container_tag) {
  const size_t original_size = c.size();
  c.remove_if(p);
  return c.size() < original_size;
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR bool erase_first_impl(Container& c,
                                          const X& x,
                                          associative_like_container_tag) {
  const auto found_iter = c.find(x);
  if (found_iter != c.end()) {
    c.erase(found_iter);
    return true;
  }

  return false;
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR bool erase_last_impl(Container& c,
                                         const X& x,
                                         associative_like_container_tag) {
  auto iter_range = c.equal_range(x);
  if (iter_range.first != iter_range.second) {
    if constexpr (std::is_same_v<typename std::iterator_traits<
                                     typename Container::const_iterator>::
                                     iterator_category,
                                 std::forward_iterator_tag>) {
      auto prev = iter_range.first;
      while (++iter_range.first != iter_range.second) {
        prev = iter_range.first;
      }
      c.erase(prev);
      return true;

    } else {
      c.erase(--iter_range.second);
    }
  }

  return false;
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR bool erase_all_impl(Container& c,
                                        const X& x,
                                        associative_like_container_tag) {
  const size_t original_size = c.size();
  c.erase(x);
  return c.size() < original_size;
}

template <typename Container, typename Pred>
CPP20_USE_CONSTEXPR bool erase_first_if_impl(Container& c,
                                             Pred p,
                                             associative_like_container_tag) {
  for (auto iter = c.cbegin(); iter != c.cend(); ++iter) {
    if (p(*iter)) {
      c.erase(iter);
      return true;
    }
  }

  return false;
}

template <typename Container, typename Pred>
CPP20_USE_CONSTEXPR bool erase_last_if_impl(Container& c,
                                            Pred p,
                                            associative_like_container_tag) {
  if constexpr (std::is_same_v<
                    typename std::iterator_traits<
                        typename Container::const_iterator>::iterator_category,
                    std::forward_iterator_tag>) {
    auto last = c.cend();
    for (auto iter = c.cbegin(); iter != c.cend(); ++iter) {
      if (p(*iter)) {
        last = iter;
      }
    }

    if (last != c.cend()) {
      c.erase(last);
      return true;
    }

  } else {
    for (auto iter = c.crbegin(); iter != c.crend(); ++iter) {
      if (p(*iter)) {
        c.erase((++iter).base());
        return true;
      }
    }
  }

  return false;
}

template <typename Container, typename Pred>
CPP20_USE_CONSTEXPR bool erase_all_if_impl(Container& c,
                                           Pred p,
                                           associative_like_container_tag) {
  const size_t original_size = c.size();
  for (auto iter = c.cbegin(); iter != c.cend();) {
    if (p(*iter)) {
      c.erase(iter++);
    } else {
      ++iter;
    }
  }

  return c.size() < original_size;
}

template <typename T, size_t N, typename X>
constexpr const T* find_first_impl(const T (&arr)[N],
                                   const X& x,
                                   array_like_container_tag) {
  auto iter = &arr[0];

  for (; iter != arr + N && *iter != x; ++iter)
    ;

  return iter;
}

template <typename T, size_t N, typename Pred>
constexpr const T* find_first_if_impl(const T (&arr)[N],
                                      Pred p,
                                      array_like_container_tag) {
  auto iter = &arr[0];

  for (; iter != arr + N && !p(*iter); ++iter)
    ;

  return iter;
}

template <typename T, size_t N, typename X>
constexpr const T* find_last_impl(const T (&arr)[N],
                                  const X& x,
                                  array_like_container_tag) {
  for (auto iter = arr + N; iter != arr;) {
    if (x == *--iter) {
      return iter;
    }
  }

  return arr + N;
}

template <typename T, size_t N, typename Pred>
constexpr const T* find_last_if_impl(const T (&arr)[N],
                                     Pred p,
                                     array_like_container_tag) {
  for (auto iter = arr + N; iter != arr;) {
    if (p(*--iter)) {
      return iter;
    }
  }

  return arr + N;
}

template <typename T, size_t N, typename X>
CPP20_USE_CONSTEXPR std::vector<const T*>
find_all_impl(const T (&arr)[N], const X& x, array_like_container_tag) {
  std::vector<const T*> result;

  for (auto iter = &arr[0]; iter != arr + N; ++iter) {
    if (x == *iter) {
      result.emplace_back(iter);
    }
  }

  return result;
}

template <typename T, size_t N, typename Pred>
CPP20_USE_CONSTEXPR std::vector<const T*>
find_all_if_impl(const T (&arr)[N], Pred p, array_like_container_tag) {
  std::vector<const T*> result;

  for (auto iter = &arr[0]; iter != arr + N; ++iter) {
    if (p(*iter)) {
      result.emplace_back(iter);
    }
  }

  return result;
}

template <typename T, size_t N, typename X>
constexpr typename std::array<T, N>::const_iterator find_first_impl(
    const std::array<T, N>& c,
    const X& x,
    array_like_container_tag) {
  auto iter = c.cbegin();

  for (; iter != c.cend() && *iter != x; ++iter)
    ;

  return iter;
}

template <typename T, size_t N, typename Pred>
constexpr typename std::array<T, N>::const_iterator find_first_if_impl(
    const std::array<T, N>& c,
    Pred p,
    array_like_container_tag) {
  auto iter = c.cbegin();

  for (; iter != c.cend() && !p(*iter); ++iter)
    ;

  return iter;
}

template <typename T, size_t N, typename X>
constexpr typename std::array<T, N>::const_iterator find_last_impl(
    const std::array<T, N>& c,
    const X& x,
    array_like_container_tag) {
  for (auto iter = c.crbegin(); iter != c.crend(); ++iter) {
    if (x == *iter) {
      return (iter + 1).base();
    }
  }

  return c.cend();
}

template <typename T, size_t N, typename Pred>
constexpr typename std::array<T, N>::const_iterator
find_last_if_impl(const std::array<T, N>& c, Pred p, array_like_container_tag) {
  for (auto iter = c.crbegin(); iter != c.crend(); ++iter) {
    if (p(*iter)) {
      return (iter + 1).base();
    }
  }

  return c.cend();
}

template <typename T, size_t N, typename X>
CPP20_USE_CONSTEXPR std::vector<typename std::array<T, N>::const_iterator>
find_all_impl(const std::array<T, N>& c, const X& x, array_like_container_tag) {
  std::vector<typename std::array<T, N>::const_iterator> result;

  for (auto iter = c.cbegin(); iter != c.cend(); ++iter) {
    if (x == *iter) {
      result.emplace_back(iter);
    }
  }

  return result;
}

template <typename T, size_t N, typename Pred>
CPP20_USE_CONSTEXPR std::vector<typename std::array<T, N>::const_iterator>
find_all_if_impl(const std::array<T, N>& c, Pred p, array_like_container_tag) {
  std::vector<typename std::array<T, N>::const_iterator> result;

  for (auto iter = c.cbegin(); iter != c.cend(); ++iter) {
    if (p(*iter)) {
      result.emplace_back(iter);
    }
  }

  return result;
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR typename Container::const_iterator
find_first_impl(const Container& c, const X& x, vector_like_container_tag) {
  auto iter = c.cbegin();

  for (; iter != c.cend() && *iter != x; ++iter)
    ;

  return iter;
}

template <typename Container, typename Pred>
CPP20_USE_CONSTEXPR typename Container::const_iterator
find_first_if_impl(const Container& c, Pred p, vector_like_container_tag) {
  auto iter = c.cbegin();

  for (; iter != c.cend() && !p(*iter); ++iter)
    ;

  return iter;
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR typename Container::const_iterator
find_last_impl(const Container& c, const X& x, vector_like_container_tag) {
  for (auto iter = c.crbegin(); iter != c.crend(); ++iter) {
    if (x == *iter) {
      return (iter + 1).base();
    }
  }

  return c.cend();
}

template <typename Container, typename Pred>
CPP20_USE_CONSTEXPR typename Container::const_iterator
find_last_if_impl(const Container& c, Pred p, vector_like_container_tag) {
  for (auto iter = c.crbegin(); iter != c.crend(); ++iter) {
    if (p(*iter)) {
      return (iter + 1).base();
    }
  }

  return c.cend();
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR std::vector<typename Container::const_iterator>
find_all_impl(const Container& c, const X& x, vector_like_container_tag) {
  std::vector<typename Container::const_iterator> result;

  for (auto iter = c.cbegin(); iter != c.cend(); ++iter) {
    if (x == *iter) {
      result.emplace_back(iter);
    }
  }

  return result;
}

template <typename Container, typename Pred>
CPP20_USE_CONSTEXPR std::vector<typename Container::const_iterator>
find_all_if_impl(const Container& c, Pred p, vector_like_container_tag) {
  std::vector<typename Container::const_iterator> result;

  for (auto iter = c.cbegin(); iter != c.cend(); ++iter) {
    if (p(*iter)) {
      result.emplace_back(iter);
    }
  }

  return result;
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR typename Container::const_iterator
find_first_impl(const Container& c, const X& x, list_like_container_tag) {
  auto iter = c.cbegin();

  for (; iter != c.cend() && *iter != x; ++iter)
    ;

  return iter;
}

template <typename Container, typename Pred>
CPP20_USE_CONSTEXPR typename Container::const_iterator
find_first_if_impl(const Container& c, Pred p, list_like_container_tag) {
  auto iter = c.cbegin();

  for (; iter != c.cend() && !p(*iter); ++iter)
    ;

  return iter;
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR typename Container::const_iterator
find_last_impl(const Container& c, const X& x, list_like_container_tag) {
  if constexpr (std::is_same_v<
                    typename std::iterator_traits<
                        typename Container::const_iterator>::iterator_category,
                    std::forward_iterator_tag>) {
    auto last_found_iter = c.cend();

    for (auto curr = c.cbegin();
         (curr = std::find(curr, c.cend(), x)) != c.cend();) {
      last_found_iter = curr;
      ++curr;
    }

    return last_found_iter;

  } else {
    auto last_found_iter = std::find(c.crbegin(), c.crend(), x);

    if (last_found_iter == c.crend()) {
      return c.cend();
    }

    return (++last_found_iter).base();
  }
}

template <typename Container, typename Pred>
CPP20_USE_CONSTEXPR typename Container::const_iterator
find_last_if_impl(const Container& c, Pred p, list_like_container_tag) {
  if constexpr (std::is_same_v<
                    typename std::iterator_traits<
                        typename Container::const_iterator>::iterator_category,
                    std::forward_iterator_tag>) {
    auto last_found_iter = c.cend();

    for (auto curr = c.cbegin();
         (curr = std::find_if(curr, c.cend(), p)) != c.cend();) {
      last_found_iter = curr;
      ++curr;
    }

    return last_found_iter;

  } else {
    auto last_found_iter = std::find_if(c.crbegin(), c.crend(), p);

    if (last_found_iter == c.crend()) {
      return c.cend();
    }

    return (++last_found_iter).base();
  }
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR std::vector<typename Container::const_iterator>
find_all_impl(const Container& c, const X& x, list_like_container_tag) {
  std::vector<typename Container::const_iterator> result;

  for (auto iter = c.cbegin(); iter != c.cend(); ++iter) {
    if (x == *iter) {
      result.emplace_back(iter);
    }
  }

  return result;
}

template <typename Container, typename Pred>
CPP20_USE_CONSTEXPR std::vector<typename Container::const_iterator>
find_all_if_impl(const Container& c, Pred p, list_like_container_tag) {
  std::vector<typename Container::const_iterator> result;

  for (auto iter = c.cbegin(); iter != c.cend(); ++iter) {
    if (p(*iter)) {
      result.emplace_back(iter);
    }
  }

  return result;
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR typename Container::const_iterator find_first_impl(
    const Container& c,
    const X& x,
    associative_like_container_tag) {
  return c.find(x);
}

template <typename Container, typename Pred>
CPP20_USE_CONSTEXPR typename Container::const_iterator
find_first_if_impl(const Container& c, Pred p, associative_like_container_tag) {
  auto iter = c.cbegin();

  for (; iter != c.cend() && !p(*iter); ++iter)
    ;

  return iter;
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR typename Container::const_iterator
find_last_impl(const Container& c, const X& x, associative_like_container_tag) {
  auto iter_range = c.equal_range(x);
  if (iter_range.first != iter_range.second) {
    if constexpr (std::is_same_v<typename std::iterator_traits<
                                     typename Container::const_iterator>::
                                     iterator_category,
                                 std::forward_iterator_tag>) {
      auto prev = iter_range.first;
      while (++iter_range.first != iter_range.second) {
        prev = iter_range.first;
      }
      return prev;
    } else {
      if (iter_range.first != iter_range.second) {
        return --iter_range.second;
      }
    }
  }

  return c.cend();
}

template <typename Container, typename Pred>
CPP20_USE_CONSTEXPR typename Container::const_iterator
find_last_if_impl(const Container& c, Pred p, associative_like_container_tag) {
  if constexpr (std::is_same_v<
                    typename std::iterator_traits<
                        typename Container::const_iterator>::iterator_category,
                    std::forward_iterator_tag>) {
    auto last = c.cend();
    for (auto iter = c.cbegin(); iter != c.cend(); ++iter) {
      if (p(*iter)) {
        last = iter;
      }
    }

    return last;

  } else {
    for (auto iter = c.crbegin(); iter != c.crend(); ++iter) {
      if (p(*iter)) {
        return (++iter).base();
      }
    }
    return c.cend();
  }
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR std::vector<typename Container::const_iterator>
find_all_impl(const Container& c, const X& x, associative_like_container_tag) {
  std::vector<typename Container::const_iterator> result;

  const auto iter_range = c.equal_range(x);

  for (auto iter = iter_range.first; iter != iter_range.second; ++iter) {
    result.emplace_back(iter);
  }

  return result;
}

template <typename Container, typename Pred>
CPP20_USE_CONSTEXPR std::vector<typename Container::const_iterator>
find_all_if_impl(const Container& c, Pred p, associative_like_container_tag) {
  std::vector<typename Container::const_iterator> result;

  for (auto iter = c.cbegin(); iter != c.cend(); ++iter) {
    if (p(*iter)) {
      result.emplace_back(iter);
    }
  }

  return result;
}

// insert function templates for STL container types with
// vector_like_container_tag defined

template <typename Container, typename IterType, typename X>
CPP20_USE_CONSTEXPR auto insert_impl(Container& c,
                                     IterType iter,
                                     const X& x,
                                     vector_like_container_tag) {
  return c.insert(iter, x);
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR auto insert_at_beginning_impl(Container& c,
                                                  const X& x,
                                                  vector_like_container_tag) {
  return c.insert(c.begin(), x);
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR auto insert_at_end_impl(Container& c,
                                            const X& x,
                                            vector_like_container_tag) {
  return c.insert(c.end(), x);
}

// insert function templates for STL container types with
// list_like_container_tag defined

template <typename Container, typename IterType, typename X>
CPP20_USE_CONSTEXPR auto insert_impl(Container& c,
                                     IterType iter,
                                     const X& x,
                                     list_like_container_tag) {
  return c.insert_after(iter, x);
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR auto insert_at_beginning_impl(Container& c,
                                                  const X& x,
                                                  list_like_container_tag) {
  return c.insert_after(c.cbefore_begin(), x);
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR auto insert_at_end_impl(Container& c,
                                            const X& x,
                                            list_like_container_tag) {
  if constexpr (std::is_same_v<
                    typename std::iterator_traits<
                        typename Container::const_iterator>::iterator_category,
                    std::forward_iterator_tag>) {
    auto prev = c.cbegin();

    for (auto curr = prev; curr != c.cend(); ++curr) {
      prev = curr;
    }

    return c.insert_after(prev, x);

  } else {
    return c.insert_after(--c.cend(), x);
  }
}

// insert function templates for STL container types with
// associative_like_container_tag defined

template <typename Container, typename X>
CPP20_USE_CONSTEXPR auto insert_impl(Container& c,
                                     const X& x,
                                     associative_like_container_tag) {
  return c.insert(x);
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR auto insert_at_beginning_impl(
    Container& c,
    const X& x,
    associative_like_container_tag) {
  return c.insert(c.cbegin(), x);
}

template <typename Container, typename X>
CPP20_USE_CONSTEXPR auto insert_at_end_impl(Container& c,
                                            const X& x,
                                            associative_like_container_tag) {
  return c.insert(c.cend(), x);
}

}  // namespace stl::helper::detail

#endif /* _STL_HELPER_FUNCTIONS_IMPL_HPP_ */