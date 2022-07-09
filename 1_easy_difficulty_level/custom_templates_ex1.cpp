#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>

size_t find_missing_number(const size_t* first, const size_t* last) {
  if (last - first == 1)
    return *first + 1;

  const std::ptrdiff_t middle = (last - first)/2;
  if (*(first + middle) == *first + middle)
    return find_missing_number(first + middle, last);
  return find_missing_number(first, first + middle);
}

template <class ForwardIt, class T>
typename std::iterator_traits<ForwardIt>::difference_type
bsearch(ForwardIt first, ForwardIt last, const T& value) {
  const ForwardIt lb_pos = std::lower_bound(first, last, value);
  return !(lb_pos == last) && (*lb_pos == value) ? std::distance(first, lb_pos)
                                                 : -1;
}

template <class BidirIt>
bool next_permutation(const BidirIt first, const BidirIt last) {
  if (first == last)
    return false;
  BidirIt i{last};
  if (first == --i)
    return false;

  while (true) {
    BidirIt i1{i};

    if (*--i < *i1) {
      BidirIt i2{last};
      while (!(*i < *--i2))
        ;
      std::iter_swap(i, i2);
      std::reverse(i1, last);
      return true;
    }
    if (first == i) {
      std::reverse(first, last);
      return false;
    }
  }
}

template <class BidirIt>
bool prev_permutation(const BidirIt first, const BidirIt last) {
  if (first == last)
    return false;

  BidirIt i{last};

  if (first == --i)
    return false;

  while (true) {
    BidirIt i1{i};
    if (*i1 < *--i) {
      BidirIt i2{last};
      while (!(*--i2 < *i))
        ;
      std::iter_swap(i, i2);
      std::reverse(i1, last);
      return true;
    }
    if (first == i) {
      std::reverse(first, last);
      return false;
    }
  }
}

using namespace std;

int main() {
  vector<int> numbers{1, 4, 2, 6, 12, 8, 5, 25, 26, 17, 35, 53, 3};

  sort(begin(numbers), end(numbers));

  const array<int, 7> values{1, 15, 17, 23, 26, 52, 53};

  for (const auto target : values) {
    const std::iterator_traits<decltype(cbegin(numbers))>::difference_type
        position = bsearch(cbegin(numbers), cend(numbers), target);
    if (-1 != position)
      cout << "Found target number: " << target << " at position: " << position
           << '\n';
    else
      cout << "Target number (" << target << ") could not be found!\n";
  }

  return 0;
}
