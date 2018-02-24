/*
Coderbyte coding challenge: Closest Enemy

Using the C++ language, have the function ClosestEnemy(arr) take the array of
numbers stored in arr and from the position in the array where a 1 is, return
the number of spaces either left or right you must move to reach an enemy which
is represented by a 2. For example: if arr is [0, 0, 1, 0, 0, 2, 0, 2] then your
program should return 3 because the closest enemy (2) is 3 spaces away from
the 1. The array will contain any number of 0's and 2's, but only a single 1. It
may not contain any 2's at all as well, where in that case your program should
return a 0.

Sample test cases:

Input:  1, 0, 0, 0, 2, 2, 2
Output: 4

Input:  2, 0, 0, 0, 2, 2, 1, 0
Output: 1
*/

#include <algorithm>
#include <climits>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

size_t ClosestEnemy_v1(const int* arr, const size_t arr_size) {
  const auto hero_count = count(arr, arr + arr_size, 1);

  if (!hero_count)
    throw runtime_error{
        "Input array 'arr' does not contain a single hero element!"};

  if (hero_count > 1)
    throw runtime_error{"Input array 'arr' contains more than 1 hero element!"};

  const auto enemy_count = count(arr, arr + arr_size, 2);

  if (!enemy_count)
    return 0;

  size_t hero_pos{string::npos}, left_enemy_pos{string::npos},
      right_enemy_pos{string::npos};

  for (size_t i{}; i < arr_size; i++) {
    if (1 == arr[i]) {
      hero_pos = i;
      continue;
    }

    if (2 == arr[i]) {
      if (string::npos == hero_pos) {
        left_enemy_pos = i;
        continue;
      }

      if ((string::npos == right_enemy_pos) && (string::npos != hero_pos)) {
        right_enemy_pos = i;
        break;
      }
    }
  }

  size_t min_distance{left_enemy_pos != string::npos ? hero_pos - left_enemy_pos
                                                     : string::npos};

  if ((string::npos != right_enemy_pos) &&
      (right_enemy_pos - hero_pos < min_distance))
    min_distance = right_enemy_pos - hero_pos;

  return min_distance;
}

int ClosestEnemy_v2(const int* arr, const size_t arr_size) {
  const auto hero_count = count(arr, arr + arr_size, 1);

  if (!hero_count)
    throw runtime_error{
        "Input array 'arr' does not contain a single hero element!"};

  if (hero_count > 1)
    throw runtime_error{"Input array 'arr' contains more than 1 hero element!"};

  const auto enemy_count = count(arr, arr + arr_size, 2);

  if (!enemy_count)
    return 0;

  const int hero_pos{static_cast<int>(find(arr, arr + arr_size, 1) - arr)};

  int min_distance{INT_MAX};

  auto enemy_pos_iter = find(arr, arr + arr_size, 2);

  while (arr + arr_size != enemy_pos_iter) {
    const int enemy_pos{static_cast<int>(enemy_pos_iter - arr)};

    if (abs(hero_pos - enemy_pos) < min_distance) {
      min_distance = abs(hero_pos - enemy_pos);
      enemy_pos_iter = find(enemy_pos_iter + 1, arr + arr_size, 2);
      continue;
    }

    break;
  }

  return min_distance;
}

int main() {
  // const int A[] = gets(stdin);
  // cout << ClosestEnemy_v1(A, sizeof(A)/sizeof(*A));
  const int B[] = {0, 0, 1, 0, 0, 2, 0, 2};
  cout << ClosestEnemy_v1(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 3
  const int C[] = {1, 0, 0, 0, 2, 2, 2};
  cout << ClosestEnemy_v1(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 4
  const int D[] = {2, 0, 0, 0, 2, 2, 1, 0};
  cout << ClosestEnemy_v1(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 1
  return 0;
}
