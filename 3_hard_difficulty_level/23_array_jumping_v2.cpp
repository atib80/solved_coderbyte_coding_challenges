/*
Coderbyte coding challenge: Array Jumping v2

(iterative solution implemented by using queue<T>)

Using the C++ language, have the function ArrayJumping(arr) take the array of
numbers stored in arr and first determine the largest element in the array, and
then determine whether or not you can reach that same element within the array
by moving left or right continuously according to whatever integer is in the
current spot. If you can reach the same spot within the array, then your program
should output the least amount of jumps it took. For example: if the input is
[2, 3, 5, 6, 1] you'll start at the spot where 6 is and if you jump 6 spaces to
the right while looping around the array you end up at the last element where
the 1 is. Then from here you jump 1 space to the left and you're back where you
started, so your program should output 2. If it's impossible to end up back at
the largest element in the array your program should output -1. The largest
element in the array will never equal the number of elements in the array. The
largest element will be unique.

Sample test cases:

Input:  1,2,3,4,2
Output: 3

Input:  1,7,1,1,1,1
Output: 2
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <tuple>
#include <unordered_set>

using namespace std;

int find_minimum_number_of_jumps(const int* numbers,
                                 const int numbers_size,
                                 const int target_pos) {
  int min_number_of_jumps{numeric_limits<int>::max()};
  queue<tuple<int, int, unordered_set<int>>> q{
      {make_tuple(target_pos, 0, unordered_set<int>{})}};

  while (!q.empty()) {
    const int current_pos{get<0>(q.front())};
    const int number_of_jumps{get<1>(q.front())};
    unordered_set<int> already_visited_left{move(get<2>(q.front()))};
    unordered_set<int> already_visited_right{already_visited_left};
    q.pop();

    if (number_of_jumps > 0 && current_pos == target_pos) {
      if (number_of_jumps < min_number_of_jumps)
        min_number_of_jumps = number_of_jumps;
      continue;
    }

    if (number_of_jumps + 1 >= min_number_of_jumps)
      continue;

    const int max_steps{numbers[current_pos] % numbers_size};

    const int next_pos_left{current_pos - max_steps < 0
                                ? numbers_size - (max_steps - current_pos)
                                : current_pos - max_steps};

    if (already_visited_left.find(next_pos_left) == end(already_visited_left)) {
      already_visited_left.insert(next_pos_left);
      q.emplace(next_pos_left, number_of_jumps + 1, move(already_visited_left));
    }

    const int next_pos_right{current_pos + max_steps > numbers_size - 1
                                 ? max_steps - (numbers_size - current_pos)
                                 : current_pos + max_steps};

    if (already_visited_right.find(next_pos_right) ==
        end(already_visited_right)) {
      already_visited_right.insert(next_pos_right);
      q.emplace(next_pos_right, number_of_jumps + 1,
                move(already_visited_right));
    }
  }

  if (numeric_limits<int>::max() == min_number_of_jumps)
    return -1;

  return min_number_of_jumps;
}

int ArrayJumping(const int* arr, const int arr_size) {
  const int target_pos =
      static_cast<ptrdiff_t>(max_element(arr, arr + arr_size) - arr);
  ;

  return find_minimum_number_of_jumps(arr, arr_size, target_pos);
}

int main() {
  // const int A[] = gets(stdin);
  // cout << ArrayJumping(A, sizeof(A) / sizeof(*A));
  const int B[] = {2, 3, 5, 6, 1};
  cout << ArrayJumping(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 2
  const int C[] = {1, 2, 3, 4, 2};
  cout << ArrayJumping(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 3
  const int D[] = {1, 7, 1, 1, 1, 1};
  cout << ArrayJumping(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 2

  return 0;
}
