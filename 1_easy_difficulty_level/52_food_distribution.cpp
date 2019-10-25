/*
Coderbyte coding challenge: Food Distribution

Using the C++ language, have the function FoodDistribution(arr) read the array
of numbers stored in arr which will represent the hunger level of different
people ranging from 0 to 5 (0 meaning not hungry at all, 5 meaning very hungry).
You will also have N sandwiches to give out which will range from 1 to 20. The
format of the array will be [N, h1, h2, h3, ...] where N represents the number
of sandwiches you have and the rest of the array will represent the hunger
levels of different people. Your goal is to minimize the hunger difference
between each pair of people in the array using the sandwiches you have
available.

For example: if arr is [5, 3, 1, 2, 1], this means you have 5 sandwiches to give
out. You can distribute them in the following order to the people: 2, 0, 1, 0.
Giving these sandwiches to the people their hunger levels now become: [1, 1, 1,
1]. The difference between each pair of people is now 0, the total is also 0, so
your program should return 0. Note: You may not have to give out all, or even
any, of your sandwiches to produce a minimized difference.

Another example: if arr is [4, 5, 2, 3, 1, 0] then you can distribute the
sandwiches in the following order: [3, 0, 1, 0, 0] which makes all the hunger
levels the following: [2, 2, 2, 1, 0]. The differences between each pair of
people is now: 0, 0, 1, 1 and so your program should return the final minimized
difference of 2.

Sample test cases:

Input:  5, 2, 3, 4, 5
Output: 1

Input:  3, 2, 1, 0, 4, 1, 0
Output: 4
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

size_t
get_final_minimized_hunger_diff_level_by_balancing_hunger_diff_levels_between_each_pair_of_neighbors(
    const int* arr,
    const size_t arr_size) {
  int number_of_sandwiches{arr[0]};
  vector<int> hunger_levels(arr + 1, arr + arr_size);

  bool is_first_pair{true};

  for (size_t i{}; i < hunger_levels.size() - 1 && 0 != number_of_sandwiches;
       ++i) {
    int diff_level_between_neighbors{
        abs(hunger_levels[i + 1] - hunger_levels[i])};

    if (diff_level_between_neighbors > 0) {
      if (diff_level_between_neighbors > number_of_sandwiches)
        diff_level_between_neighbors = number_of_sandwiches;

      if (is_first_pair && hunger_levels[i] > hunger_levels[i + 1]) {
        is_first_pair = false;
        hunger_levels[i] -= diff_level_between_neighbors;
        number_of_sandwiches -= diff_level_between_neighbors;

      } else if (hunger_levels[i + 1] > hunger_levels[i]) {
        hunger_levels[i + 1] -= diff_level_between_neighbors;
        number_of_sandwiches -= diff_level_between_neighbors;
      }
    }
  }

  size_t hunger_level_diff{};

  for (size_t i{1}; i < hunger_levels.size() - 1; ++i) {
    hunger_level_diff += abs(hunger_levels[i + 1] - hunger_levels[i]);
  }

  return hunger_level_diff;
}

size_t
get_final_minimized_diff_level_by_balancing_diff_levels_using_average_hunger_level(
    const int* arr,
    const size_t arr_size) {
  int number_of_sandwiches{arr[0]};
  vector<int> hunger_levels(arr + 1, arr + arr_size);

  const int average_hungry_level =
      accumulate(cbegin(hunger_levels), cend(hunger_levels), 0) /
      static_cast<int>(hunger_levels.size());

  int prev_level{};

  for (size_t i{}; i < hunger_levels.size() && 0 != number_of_sandwiches; ++i) {
    if (hunger_levels[i] > average_hungry_level) {
      const int diff_level_between_neighbors{hunger_levels[i] -
                                             average_hungry_level};

      if (diff_level_between_neighbors > number_of_sandwiches) {
        hunger_levels[i] -= number_of_sandwiches;
        break;
      }

      hunger_levels[i] -= diff_level_between_neighbors;
      number_of_sandwiches -= diff_level_between_neighbors;

    } else if (hunger_levels[i] > prev_level) {
      const int diff_level_between_neighbors{hunger_levels[i] - prev_level};

      if (diff_level_between_neighbors > number_of_sandwiches) {
        hunger_levels[i] -= number_of_sandwiches;
        break;
      }

      hunger_levels[i] -= diff_level_between_neighbors;
      number_of_sandwiches -= diff_level_between_neighbors;
    }

    prev_level = hunger_levels[i];
  }

  size_t hunger_level_diff{};

  for (size_t i{}; i < hunger_levels.size() - 1; ++i) {
    hunger_level_diff += abs(hunger_levels[i + 1] - hunger_levels[i]);
  }

  return hunger_level_diff;
}

size_t
get_final_minimized_difference_level_by_balancing_sorted_hunger_diff_levels(
    const int* arr,
    const size_t arr_size) {
  int number_of_sandwiches{arr[0]};

  vector<pair<size_t, int>> hunger_levels{};
  vector<int> hunger_levels_arr(arr + 1, arr + arr_size);

  for (size_t i{1}; i < arr_size; ++i)
    hunger_levels.emplace_back(i - 1, arr[i]);

  sort(begin(hunger_levels), end(hunger_levels),
       [](const pair<size_t, int>& l, const pair<size_t, int>& r) {
         return l.second > r.second;
       });

  const int average_hungry_level =
      accumulate(begin(hunger_levels_arr), end(hunger_levels_arr), 0) /
      static_cast<int>(hunger_levels_arr.size());

  for (size_t i{}; i < hunger_levels.size() && 0 != number_of_sandwiches; ++i) {
    if (hunger_levels[i].second > average_hungry_level) {
      const int diff_level_between_neighbors{hunger_levels[i].second -
                                             average_hungry_level};

      if (diff_level_between_neighbors > number_of_sandwiches) {
        hunger_levels_arr[hunger_levels[i].first] -= number_of_sandwiches;
        break;
      }

      hunger_levels_arr[hunger_levels[i].first] -= diff_level_between_neighbors;

      number_of_sandwiches -= diff_level_between_neighbors;
    }
  }

  size_t hungry_level_diff{};

  for (size_t i{}; i < hunger_levels_arr.size() - 1; i++) {
    hungry_level_diff += abs(hunger_levels_arr[i + 1] - hunger_levels_arr[i]);
  }

  return hungry_level_diff;
}

size_t find_final_minimized_hunger_difference_level(const int* arr,
                                                    const size_t arr_size) {
  const int number_of_sandwiches{arr[0]};

  const int needed_number_of_sandwitches{[&]() {
    int n{};
    vector<int> hunger_levels{arr + 1, arr + arr_size};
    sort(begin(hunger_levels), end(hunger_levels));

    const int min_hungry_level{hunger_levels.front()};
    const auto start{upper_bound(cbegin(hunger_levels), cend(hunger_levels),
                                 min_hungry_level)};
    for_each(start, cend(hunger_levels),
             [&](const int value) { n += value - min_hungry_level; });
    return n;
  }()};

  if (number_of_sandwiches >= needed_number_of_sandwitches)
    return 0U;

  vector<size_t> final_hunger_diff_levels{
      get_final_minimized_hunger_diff_level_by_balancing_hunger_diff_levels_between_each_pair_of_neighbors(
          arr, arr_size),
      get_final_minimized_diff_level_by_balancing_diff_levels_using_average_hunger_level(
          arr, arr_size),
      get_final_minimized_difference_level_by_balancing_sorted_hunger_diff_levels(
          arr, arr_size)};

  sort(begin(final_hunger_diff_levels), end(final_hunger_diff_levels));

  return *cbegin(final_hunger_diff_levels);
}

size_t FoodDistribution_v1(const int* arr, const size_t arr_size) {
  return find_final_minimized_hunger_difference_level(arr, arr_size);
}

void find_minimum_level_of_hunger_difference(
    vector<int>& hunger_levels,
    const size_t pos,
    const vector<int>& remaining_hunger_diff_level_right,
    int& min_hunger_diff_level,
    const int number_of_sandwiches,
    const int accumulated_diff_level = 0) {
  if (pos == hunger_levels.size() - 1 && 0 == number_of_sandwiches) {
    int hunger_diff_level{};
    for (size_t i{}; i < hunger_levels.size() - 1; ++i)
      hunger_diff_level += abs(hunger_levels[i] - hunger_levels[i + 1]);

    min_hunger_diff_level = min(hunger_diff_level, min_hunger_diff_level);
  }

  for (size_t i{pos}; i < hunger_levels.size() - 1; ++i) {
    const size_t ti{hunger_levels[i] > hunger_levels[i + 1] ? i : i + 1};
    const int orig_diff{abs(hunger_levels[i] - hunger_levels[i + 1])};
    for (int diff{min(orig_diff, number_of_sandwiches)}; diff >= 0; --diff) {
      hunger_levels[ti] -= diff;

      if (accumulated_diff_level + remaining_hunger_diff_level_right[i] -
              abs(orig_diff - abs(hunger_levels[i] - hunger_levels[i + 1])) -
              (number_of_sandwiches - diff) >=
          min_hunger_diff_level) {
        hunger_levels[ti] += diff;
        break;
      }

      find_minimum_level_of_hunger_difference(
          hunger_levels, i + 1, remaining_hunger_diff_level_right,
          min_hunger_diff_level, number_of_sandwiches - diff,
          accumulated_diff_level +
              abs(hunger_levels[i] - hunger_levels[i + 1]));

      hunger_levels[ti] += diff;
    }
  }
}

size_t FoodDistribution_v2(const int* arr, const size_t arr_size) {
  const int number_of_sandwiches{arr[0]};

  const int needed_number_of_sandwitches{[&]() {
    int n{};
    vector<int> hunger_levels{arr + 1, arr + arr_size};
    sort(begin(hunger_levels), end(hunger_levels));

    const int min_hungry_level{hunger_levels.front()};
    const auto start{upper_bound(cbegin(hunger_levels), cend(hunger_levels),
                                 min_hungry_level)};
    for_each(start, cend(hunger_levels),
             [&](const int value) { n += value - min_hungry_level; });
    return n;
  }()};

  if (number_of_sandwiches >= needed_number_of_sandwitches)
    return 0U;

  int min_hunger_diff_level{needed_number_of_sandwitches};

  vector<int> hunger_levels(arr + 1, arr + arr_size);
  vector<int> remaining_hunger_diff_level_right(arr_size - 1);
  int hunger_diff_level_right{};

  for (size_t i{hunger_levels.size() - 1}; i > 0; --i) {
    hunger_diff_level_right += abs(hunger_levels[i - 1] - hunger_levels[i]);
    remaining_hunger_diff_level_right[i - 1] = hunger_diff_level_right;
  }

  find_minimum_level_of_hunger_difference(hunger_levels, 0U,
                                          remaining_hunger_diff_level_right,
                                          min_hunger_diff_level, arr[0]);

  return min_hunger_diff_level;
}

struct hunger_level_data {
  const size_t index;
  int prev_level;
  const int number_of_sandwiches;
  const int accumulated_diff_level;
  vector<int> min_distance_offsets;

  hunger_level_data(const size_t index,
                    const int prev_level,
                    const int number_of_sandwiches,
                    const int accumulated_diff_level,
                    vector<int> distance_offsets)
      : index{index},
        prev_level{prev_level},
        number_of_sandwiches{number_of_sandwiches},
        accumulated_diff_level{accumulated_diff_level},
        min_distance_offsets{move(distance_offsets)} {}
};

size_t FoodDistribution_v3(const int* arr, const size_t arr_size) {
  const int needed_number_of_sandwitches{[&]() {
    int n{};
    vector<int> hunger_levels{arr + 1, arr + arr_size};
    sort(begin(hunger_levels), end(hunger_levels));

    const int min_hungry_level{hunger_levels.front()};
    const auto start{upper_bound(cbegin(hunger_levels), cend(hunger_levels),
                                 min_hungry_level)};
    for_each(start, cend(hunger_levels),
             [&](const int value) { n += value - min_hungry_level; });
    return n;
  }()};

  if (arr[0] >= needed_number_of_sandwitches)
    return 0U;

  int min_hunger_diff_level{needed_number_of_sandwitches};
  const int* hunger_levels{arr + 1};
  const size_t hunger_levels_size{arr_size - 1};

  vector<int> min_distance_offsets(hunger_levels_size, min_hunger_diff_level);
  min_distance_offsets.front() = -arr[0];

  queue<hunger_level_data> q{
      {{1U, hunger_levels[0], arr[0], 0, min_distance_offsets}}};

  while (!q.empty()) {
    hunger_level_data node{move(q.front())};
    q.pop();

    if (node.accumulated_diff_level >= min_hunger_diff_level)
      continue;

    if (node.index == hunger_levels_size) {
      min_hunger_diff_level = node.accumulated_diff_level;
      min_distance_offsets = move(node.min_distance_offsets);
      continue;
    }

    int next_level{hunger_levels[node.index]};
    const int orig_diff{abs(node.prev_level - next_level)};
    for (int diff{min(orig_diff, node.number_of_sandwiches)}; diff >= 0;
         --diff) {
      if (node.prev_level > next_level) {
        node.prev_level -= diff;

        if (node.accumulated_diff_level + abs(node.prev_level - next_level) +
                (node.index > 1U ? diff : 0) -
                (node.number_of_sandwiches - diff) <
            min_distance_offsets[node.index]) {
          node.min_distance_offsets[node.index] =
              node.accumulated_diff_level + abs(node.prev_level - next_level) -
              (node.number_of_sandwiches - diff);
          q.emplace(
              node.index + 1, next_level, node.number_of_sandwiches - diff,
              node.accumulated_diff_level + abs(node.prev_level - next_level) +
                  (node.index > 1U ? diff : 0),
              node.min_distance_offsets);
        } else
          break;

        node.prev_level += diff;

      } else {
        next_level -= diff;

        if (node.accumulated_diff_level + abs(next_level - node.prev_level) -
                (node.number_of_sandwiches - diff) <
            min_distance_offsets[node.index]) {
          node.min_distance_offsets[node.index] =
              node.accumulated_diff_level + abs(next_level - node.prev_level) -
              (node.number_of_sandwiches - diff);
          q.emplace(
              node.index + 1, next_level, node.number_of_sandwiches - diff,
              node.accumulated_diff_level + abs(next_level - node.prev_level),
              node.min_distance_offsets);
        } else
          break;

        next_level += diff;
      }
    }
  }

  return min_hunger_diff_level;
}

int main() {
  // int A[] = gets(stdin);
  // cout << FoodDistribution_v2(A, sizeof(A)/sizeof(*A));
  const int B[]{5, 3, 1, 2, 1};
  cout << FoodDistribution_v3(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 0
  const int C[]{4, 5, 2, 3, 1, 0};
  cout << FoodDistribution_v3(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 2
  const int D[]{5, 2, 3, 4, 5};
  cout << FoodDistribution_v3(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 1
  const int E[]{3, 2, 1, 0, 4, 1, 0};
  cout << FoodDistribution_v3(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: 4
  const int F[]{20, 5, 4, 1};
  cout << FoodDistribution_v3(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: 0
  const int G[]{4, 2, 3, 2, 1};
  cout << FoodDistribution_v3(G, sizeof(G) / sizeof(*G))
       << '\n';  // expected output: 0
  const int H[]{4, 5, 4, 5, 2, 3, 1, 2};
  cout << FoodDistribution_v3(H, sizeof(H) / sizeof(*H))
       << '\n';  // expected output: 3
  const int I[]{7, 5, 4, 3, 4, 5, 2, 3, 1, 4, 5};
  cout << FoodDistribution_v3(I, sizeof(I) / sizeof(*I))
       << '\n';  // expected output: 6

  return 0;
}
