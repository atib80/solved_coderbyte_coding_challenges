#include <conio.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <unordered_map>
#include <vector>

template <class ForwardIt, class T>
size_t bsearch(ForwardIt first, ForwardIt last, const T& value) {
  using difference_type =
      typename std::iterator_traits<ForwardIt>::difference_type;
  const ForwardIt start{first};
  first = std::lower_bound(first, last, value);
  return (!(first == last) && (value == *first)) ? std::distance(start, first)
                                                 : string::npos;
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

  if (string::npos != bsearch(begin(numbers), end(numbers), target))
    cout << "Found target number: " << target << '\n';
  else
    cout << "Target number (" << target << ") could not be found!\n";

  target = 15;

  if (string::npos != bsearch(begin(numbers), end(numbers), target))
    cout << "Found target number: " << target << '\n';
  else
    cout << "Target number (" << target << ") could not be found!\n";

  target = 17;

  if (string::npos != bsearch(begin(numbers), end(numbers), target))
    cout << "Found target number: " << target << '\n';
  else
    cout << "Target number (" << target << ") could not be found!\n";

  target = 23;

  if (string::npos != bsearch(begin(numbers), end(numbers), target))
    cout << "Found target number: " << target << '\n';
  else
    cout << "Target number (" << target << ") could not be found!\n";

  target = 26;

  if (string::npos != bsearch(begin(numbers), end(numbers), target))
    cout << "Found target number: " << target << '\n';
  else
    cout << "Target number (" << target << ") could not be found!\n";

  target = 52;

  if (string::npos != bsearch(begin(numbers), end(numbers), target))
    cout << "Found target number: " << target << '\n';
  else
    cout << "Target number (" << target << ") could not be found!\n";

  target = 53;

  if (string::npos != bsearch(begin(numbers), end(numbers), target))
    cout << "Found target number: " << target << '\n';
  else
    cout << "Target number (" << target << ") could not be found!\n";

  return 0;
}
