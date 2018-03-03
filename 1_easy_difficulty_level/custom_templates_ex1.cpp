#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <vector>

template <typename RandomIter, typename T>
bool bsearch(RandomIter first, RandomIter last, const T& value) {
  std::unordered_map<int, RandomIter> next_iterators{{-1, first}, {1, last}};

  while (next_iterators[-1] < next_iterators[1]) {
    const auto d = std::distance(next_iterators[-1], next_iterators[1]);

    RandomIter current{next_iterators[-1]};

    std::advance(current, max(1, d / 2));

    const T result{*current - value};

    if (0 == result)
      return true;

    next_iterators[result / std::abs(result)] = current;
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

using namespace std;

int main() {
  vector<int> numbers{1, 4, 2, 6, 12, 8, 5, 25, 26, 17, 35, 53, 3};

  sort(begin(numbers), end(numbers));

  if (bsearch(begin(numbers), end(numbers), 10))
    cout << "Found value 10!";
  else
    cout << "No dice!";

  return 0;
}