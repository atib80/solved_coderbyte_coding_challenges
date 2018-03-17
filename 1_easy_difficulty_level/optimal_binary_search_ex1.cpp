#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <typename ForwardIter, typename T>
ForwardIter optimal_bsearch(ForwardIter first,
                            ForwardIter last,
                            const T& value) {
  using difference_type =
      typename std::iterator_traits<ForwardIter>::difference_type;

  const ForwardIter orig_last{last};
  ForwardIter next{first};

  while (++next < last) {
    ForwardIter current{first};

    const difference_type d{std::distance(first, last)};

    std::advance(current, d / 2);

    if (value < *current)
      last = current;
    else
      first = current;

    next = first;
  }

  if (value == *first)
    return first;

  return orig_last;
}

int main() {
  std::vector<int> numbers{1, 4, 2, 6, 12, 8, 5, 25, 26, 17, 35, 53, 3};

  std::sort(std::begin(numbers), std::end(numbers));

  for (decltype(numbers[0]) i{numbers[0]}; i <= numbers.back(); i++) {
    if (std::end(numbers) !=
        optimal_bsearch(std::begin(numbers), std::end(numbers), i))
      std::cout << "Successfully located specified number: " << i << '\n';
    else
      std::cout << "Failed to locate specified number: " << i << '\n';
  }

  return 0;
}
