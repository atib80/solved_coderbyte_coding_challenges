#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <typename ForwardIter, typename T>
ForwardIter optimal_bsearch(ForwardIter first,
                            ForwardIter last,
                            const T& value) {
  const ForwardIter orig_last{last};
  ForwardIter next{first};

  while (++next != last) {
    ForwardIter current{first};

    std::advance(current, std::distance(first, last) / 2);

    if (value < *current)
      last = current;
    else
      first = current;

    next = first;
  }

  return value == *first ? first : orig_last;
}

int main() {
  std::vector<int> numbers{1, 4, 2, 6, 12, 8, 5, 25, 26, 17, 35, 53, 3};

  std::sort(std::begin(numbers), std::end(numbers));

  for (decltype(numbers[0]) i{numbers[0]}; i <= numbers.back(); ++i) {
    if (std::cend(numbers) !=
        optimal_bsearch(std::cbegin(numbers), std::cend(numbers), i))
      std::cout << "Successfully located specified number: " << i << '\n';
    else
      std::cout << "Failed to locate specified number: " << i << '\n';
  }

  return 0;
}
