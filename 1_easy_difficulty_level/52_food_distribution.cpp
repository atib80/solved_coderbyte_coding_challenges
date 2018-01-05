/*
Coderbyte coding challenge: Food Distribution

Using the C++ language, have the function FoodDistribution(arr) read the array of numbers stored in arr which will represent the hunger level of different people 
ranging from 0 to 5 (0 meaning not hungry at all, 5 meaning very hungry). You will also have N sandwiches to give out which will range from 1 to 20. 
The format of the array will be [N, h1, h2, h3, ...] where N represents the number of sandwiches you have and the rest of the array will represent the hunger levels 
of different people. Your goal is to minimize the hunger difference between each pair of people in the array using the sandwiches you have available.

For example: if arr is [5, 3, 1, 2, 1], this means you have 5 sandwiches to give out. You can distribute them in the following order to the people: 2, 0, 1, 0. 
Giving these sandwiches to the people their hunger levels now become: [1, 1, 1, 1]. The difference between each pair of people is now 0, the total is also 0, 
so your program should return 0. Note: You may not have to give out all, or even any, of your sandwiches to produce a minimized difference.

Another example: if arr is [4, 5, 2, 3, 1, 0] then you can distribute the sandwiches in the following order: [3, 0, 1, 0, 0] 
which makes all the hunger levels the following: [2, 2, 2, 1, 0]. The differences between each pair of people is now: 0, 0, 1, 1 and so your program should 
return the final minimized difference of 2.

Sample test cases:

Input:  5, 2, 3, 4, 5
Output: 1

Input:  3, 2, 1, 0, 4, 1, 0
Output: 4
*/

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>

using namespace std;

size_t FoodDistribution(int* arr, const size_t arr_size)
{
  int number_of_sandwiches{arr[0]};
  vector<int> hungry_levels_arr(arr + 1, arr + arr_size);

  vector<pair<size_t, int>> hungry_levels{};
  vector<int> hungry_levels_sorted(arr + 1, arr + arr_size);

  for (size_t i{1u}; i < arr_size; i++) hungry_levels.emplace_back(make_pair(i - 1, arr[i]));


  sort(begin(hungry_levels), end(hungry_levels), [](const pair<size_t, int>& l, const pair<size_t, int>& r)
  {
    return (l.second > r.second);
  });

  const int min_hungry_level{hungry_levels.back().second};

  int needed_number_of_sandwitches{};

  for (const auto& h : hungry_levels)
  {
    if (min_hungry_level == h.second) break;
    needed_number_of_sandwitches += (h.second - min_hungry_level);
  }

  if (number_of_sandwiches >= needed_number_of_sandwitches) return 0;

  bool is_first_pair{true};

  for (size_t i{1u}; i != (arr_size - 1); i++)
  {
    int s{abs(arr[i + 1] - arr[i])};

    if ((s > 0) && (number_of_sandwiches > 0))
    {
      if (s > number_of_sandwiches) s = number_of_sandwiches;

      if (is_first_pair && (arr[i] > arr[i + 1]))
      {
        is_first_pair = false;

        arr[i] -= s;

        number_of_sandwiches -= s;
      }
      else if (arr[i + 1] > arr[i])
      {
        arr[i + 1] -= s;

        number_of_sandwiches -= s;
      }
    }
  }

  size_t hungry_level_diff1{};

  for (size_t i{1u}; i != (arr_size - 1); i++)
  {
    hungry_level_diff1 += abs(arr[i + 1] - arr[i]);
  }

  number_of_sandwiches = arr[0];

  int average_hungry_level{};

  for (const auto& h : hungry_levels_arr) average_hungry_level += h;

  average_hungry_level /= hungry_levels_arr.size();

  int prev_level{};

  int s;

  for (size_t i{}; i < hungry_levels_arr.size(); i++)
  {
    if (number_of_sandwiches < 1) break;

    if (hungry_levels_arr[i] > average_hungry_level)
    {
      s = hungry_levels_arr[i] - average_hungry_level;

      if (s > number_of_sandwiches)
      {
        hungry_levels_arr[i] -= number_of_sandwiches;
        break;
      }

      hungry_levels_arr[i] -= s;

      number_of_sandwiches -= s;
    }
    else if (hungry_levels_arr[i] > prev_level)
    {
      s = hungry_levels_arr[i] - prev_level;

      if (s > number_of_sandwiches)
      {
        hungry_levels_arr[i] -= number_of_sandwiches;
        break;
      }

      hungry_levels_arr[i] -= s;

      number_of_sandwiches -= s;
    }

    prev_level = hungry_levels_arr[i];
  }

  size_t hungry_level_diff2{};

  for (size_t i{}; i != (hungry_levels_arr.size() - 1); i++)
  {
    hungry_level_diff2 += abs(hungry_levels_arr[i + 1] - hungry_levels_arr[i]);
  }

  number_of_sandwiches = arr[0];

  for (size_t i{}; i < hungry_levels.size(); i++)
  {
    if (number_of_sandwiches < 1) break;

    if (hungry_levels[i].second > average_hungry_level)
    {
      s = hungry_levels[i].second - average_hungry_level;

      if (s > number_of_sandwiches)
      {
        hungry_levels_sorted[hungry_levels[i].first] -= number_of_sandwiches;
        break;
      }

      hungry_levels_sorted[hungry_levels[i].first] -= s;

      number_of_sandwiches -= s;
    }
  }

  size_t hungry_level_diff3{};

  for (size_t i{}; i != (hungry_levels_sorted.size() - 1); i++)
  {
    hungry_level_diff3 += abs(hungry_levels_sorted[i + 1] - hungry_levels_sorted[i]);
  }

  size_t hl[3] = {hungry_level_diff1, hungry_level_diff2, hungry_level_diff3};

  sort(hl, hl + 3);

  return *hl;
}

int main()
{
  // int A[] = gets(stdin);
  // cout << FoodDistribution(A, sizeof(A)/sizeof(*A));
  int B[] = {5, 3, 1, 2, 1};
  cout << FoodDistribution(B, sizeof(B) / sizeof(*B)) << '\n'; // expected output: 0
  int C[] = {4, 5, 2, 3, 1, 0};
  cout << FoodDistribution(C, sizeof(C)/sizeof(*C)) << '\n';   // expected output: 2
  int D[] = {5, 2, 3, 4, 5};
  cout << FoodDistribution(D, sizeof(D)/sizeof(*D)) << '\n';   // expected output: 1
  int E[] = {3, 2, 1, 0, 4, 1, 0};
  cout << FoodDistribution(E, sizeof(E)/sizeof(*E)) << '\n';   // expected output: 4
  int F[] = {20, 5, 4, 1};
  cout << FoodDistribution(F, sizeof(F)/sizeof(*F)) << '\n';   // expected output: 0
  int G[] = {4, 2, 3, 2, 1};
  cout << FoodDistribution(G, sizeof(G)/sizeof(*G)) << '\n';   // expected output: 0
  int H[] = {4, 5, 4, 5, 2, 3, 1, 2};
  cout << FoodDistribution(H, sizeof(H)/sizeof(*H)) << '\n';   // expected output: 3
  int I[] = {7, 5, 4, 3, 4, 5, 2, 3, 1, 4, 5};
  cout << FoodDistribution(I, sizeof(I)/sizeof(*I)) << '\n';   // expected output: 6
  return 0;
}
