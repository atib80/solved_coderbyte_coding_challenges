#include <conio.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <unordered_map>
#include <vector>

template <typename RandomIter, typename T>
bool bsearch(RandomIter first, RandomIter last, const T& value) {
  std::unordered_map<bool, RandomIter> next_iterators{{true, first},
                                                      {false, last}};

  // T delta_diff{};
  // if (std::is_floating_point<T>::value) delta_diff = static_cast<T>(0.00001);

  while (next_iterators[true] <= next_iterators[false]) {
    RandomIter current{next_iterators[true]};

    const auto curr_dist =
        std::distance(next_iterators[true], next_iterators[false]);

    std::advance(current, curr_dist / 2);

    const T diff{*current - value};

    // if (abs(diff) <= delta_diff)
    // return true;

    if (0 == diff)
      return true;

    const bool index{signbit(static_cast<double>(diff))};

    next_iterators[index] = current - (index ? -1 : 1);
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

  int target{1};

  if (bsearch(begin(numbers), end(numbers), target))
    cout << "Found target number: " << target << '\n';
  else
    cout << "Target number (" << target << ") could not be found!\n";

  target = 15;

  if (bsearch(begin(numbers), end(numbers), target))
    cout << "Found target number: " << target << '\n';
  else
    cout << "Target number (" << target << ") could not be found!\n";

  target = 17;

  if (bsearch(begin(numbers), end(numbers), target))
    cout << "Found target number: " << target << '\n';
  else
    cout << "Target number (" << target << ") could not be found!\n";

  target = 23;

  if (bsearch(begin(numbers), end(numbers), target))
    cout << "Found target number: " << target << '\n';
  else
    cout << "Target number (" << target << ") could not be found!\n";

  target = 26;

  if (bsearch(begin(numbers), end(numbers), target))
    cout << "Found target number: " << target << '\n';
  else
    cout << "Target number (" << target << ") could not be found!\n";

  target = 52;

  if (bsearch(begin(numbers), end(numbers), target))
    cout << "Found target number: " << target << '\n';
  else
    cout << "Target number (" << target << ") could not be found!\n";

  target = 53;

  if (bsearch(begin(numbers), end(numbers), target))
    cout << "Found target number: " << target << '\n';
  else
    cout << "Target number (" << target << ") could not be found!\n";

  return 0;
}
