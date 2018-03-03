#include <conio.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <unordered_map>
#include <vector>

// experimental version of a custom binary search algorithm implemented using
// 1 unordered_map container for quick lookup of lower and upper bound iterator
// values and 1 if comparison

template <typename RandomIter, typename T>
bool bsearch(RandomIter first, RandomIter last, const T& value) {
  std::unordered_map<int, RandomIter> next_iterators{{-1, first}, {1, last}};

  while (next_iterators[-1] <= next_iterators[1]) {
    RandomIter current{next_iterators[-1]};

    const auto curr_dist = std::distance(next_iterators[-1], next_iterators[1]);

    std::advance(current, curr_dist / 2);

    if (value == *current)
      return true;

    const int index = (*current - value) / std::abs(*current - value);

    next_iterators[index] = current - index;
  }

  return false;
}

template <class BidirIt>
bool next_permutation(BidirIt first, BidirIt last) {
  if (first == last)
    return false;
  BidirIt i = last;
  if (first == --i)
    return false;

  while (true) {
    BidirIt i1, i2;

    i1 = i;
    if (*--i < *i1) {
      i2 = last;
      while (!(*i < *--i2))
        ;
      std::iter_swap(i, i2);
      std::reverse(i1, last);
      return true;
    }
    if (i == first) {
      std::reverse(first, last);
      return false;
    }
  }
}

template <class BidirIt>
bool prev_permutation(BidirIt first, BidirIt last) {
  if (first == last)
    return false;
  BidirIt i = last;
  if (first == --i)
    return false;

  while (1) {
    BidirIt i1, i2;

    i1 = i;
    if (*i1 < *--i) {
      i2 = last;
      while (!(*--i2 < *i))
        ;
      std::iter_swap(i, i2);
      std::reverse(i1, last);
      return true;
    }
    if (i == first) {
      std::reverse(first, last);
      return false;
    }
  }
}

using namespace std;

int main() {
  vector<int> numbers{1, 4, 2, 6, 12, 8, 5, 25, 26, 17, 35, 53, 3};

  sort(begin(numbers), end(numbers));

  if (bsearch(begin(numbers), end(numbers), 53))
    cout << "Found target!";
  else
    cout << "No dice!";

  return 0;
}
