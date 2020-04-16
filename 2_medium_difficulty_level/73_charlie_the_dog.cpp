/*
Coderbyte coding challenge: Charlie The Dog

Using the C++ language, have the function CharlietheDog(strArr) read the array
of strings stored in strArr which will be a 4x4 matrix of the characters 'C',
'H', 'F', 'O', where C represents Charlie the dog, H represents its home, F
represents dog food, and O represents and empty space in the grid. Your goal is
to figure out the least amount of moves required to get Charlie to grab each
piece of food in the grid by moving up, down, left, or right, and then make it
home right after. Charlie cannot move onto the home before all pieces of food
have been collected. For example: if strArr is ["FOOF", "OCOO", "OOOH", "FOOO"],
then this looks like the following grid:

|F|O|O|F|
|O|C|O|O|
|O|O|O|H|
|F|O|O|O|

For the input above, the least amount of steps where the dog can reach each
piece of food, and then return home is 11 steps, so your program should return
the number 11. The grid will always contain between 1 and 8 pieces of food.

Sample test cases:

Input:  "OOOO", "OOFF", "OCHO", "OFOO"
|O|O|O|O|
|O|O|F|F|
|O|C|H|O|
|O|F|O|O|
Output: 7

Input:  "FOOO", "OCOH", "OFOF", "OFOO"
Output: 10
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

string trim(const string& input) {
  string output{input};
  output.erase(begin(output),
               find_if(begin(output), end(output),
                       [](const char ch) { return !isspace(ch); }));

  output.erase(find_if(output.rbegin(), output.rend(),
                       [](const char ch) { return !isspace(ch); })
                   .base(),
               end(output));

  return output;
}

size_t calculate_distance(const pair<size_t, size_t>& x,
                          const pair<size_t, size_t>& y) {
  return (x.first > y.first ? x.first - y.first : y.first - x.first) +
         (x.second > y.second ? x.second - y.second : y.second - x.second);
}

size_t CharlietheDog_v1(string* str_arr, const size_t arr_size) {
  if (!str_arr || !arr_size)
    return 0;

  pair<size_t, size_t> dog{string::npos, string::npos},
      home{string::npos, string::npos};
  vector<pair<size_t, size_t>> food_positions{};

  for (size_t i{}; i < arr_size; i++) {
    str_arr[i] = trim(str_arr[i]);

    for (size_t j{}; j < str_arr[i].length(); j++) {
      if ('c' == str_arr[i][j] || 'C' == str_arr[i][j])
        dog = make_pair(i, j);

      else if ('h' == str_arr[i][j] || 'H' == str_arr[i][j])
        home = make_pair(i, j);

      else if ('f' == str_arr[i][j] || 'F' == str_arr[i][j])
        food_positions.emplace_back(make_pair(i, j));
    }
  }

  size_t min_steps_count{string::npos};

  sort(begin(food_positions), end(food_positions),
       [](const pair<size_t, size_t>& x, const pair<size_t, size_t>& y) {
         return x.first < y.first && x.second < y.second;
       });

  size_t index{};
  string food_pos_indices =
      accumulate(begin(food_positions), end(food_positions), string{},
                 [&](const string& result, const pair<size_t, size_t>&) {
                   return result + to_string(index++);
                 });

  do {
    pair<size_t, size_t> dog_pos{dog};

    size_t steps_count{};

    for (const char food_pos_index : food_pos_indices) {
      steps_count +=
          calculate_distance(dog_pos, food_positions[food_pos_index - '0']);

      dog_pos = food_positions[food_pos_index - '0'];
    }

    steps_count += calculate_distance(dog_pos, home);

    if (steps_count < min_steps_count)
      min_steps_count = steps_count;

  } while (next_permutation(begin(food_pos_indices), end(food_pos_indices)));

  return min_steps_count;
}

size_t CharlietheDog_v2(string* str_arr, const size_t arr_size) {
  if (!str_arr || !arr_size)
    return 0;

  pair<size_t, size_t> dog{string::npos, string::npos},
      home{string::npos, string::npos};
  vector<pair<size_t, size_t>> food_positions{};

  for (size_t i{}; i < arr_size; i++) {
    str_arr[i] = trim(str_arr[i]);

    for (size_t j{}; j < str_arr[i].length(); j++) {
      if ('c' == str_arr[i][j] || 'C' == str_arr[i][j])
        dog = make_pair(i, j);

      else if ('h' == str_arr[i][j] || 'H' == str_arr[i][j])
        home = make_pair(i, j);

      else if ('f' == str_arr[i][j] || 'F' == str_arr[i][j])
        food_positions.emplace_back(make_pair(i, j));
    }
  }

  size_t min_steps_count{string::npos};

  sort(begin(food_positions), end(food_positions),
       [](const pair<size_t, size_t>& x, const pair<size_t, size_t>& y) {
         return x.first < y.first && x.second < y.second;
       });

  do {
    pair<size_t, size_t> dog_pos{dog};

    size_t steps_count{};

    for (const pair<size_t, size_t>& food_position : food_positions) {
      steps_count += calculate_distance(dog_pos, food_position);

      dog_pos = food_position;
    }

    steps_count += calculate_distance(dog_pos, home);

    if (steps_count < min_steps_count)
      min_steps_count = steps_count;

  } while (next_permutation(begin(food_positions), end(food_positions)));

  return min_steps_count;
}

pair<size_t, size_t> find_closest_food_position(
    const vector<pair<size_t, size_t>>& food_positions,
    const size_t current_pos,
    const unordered_map<string, size_t>& precalculated_distances,
    const unordered_set<size_t>& already_visited_food_positions) {
  pair<size_t, size_t> closest_food_position{};
  size_t min_distance{string::npos};

  for (size_t i{}; i < food_positions.size(); i++) {
    if (already_visited_food_positions.count(i) || current_pos == i)
      continue;
    const string index{to_string(current_pos) + to_string(i)};
    const auto dist_itr = precalculated_distances.find(index);
    const size_t current_distance{
        dist_itr != end(precalculated_distances)
            ? dist_itr->second
            : calculate_distance(food_positions[current_pos],
                                 food_positions[i])};
    if (current_distance < min_distance) {
      min_distance = current_distance;
      closest_food_position.first = i;
      closest_food_position.second = current_distance;
    }
  }

  return closest_food_position;
}

size_t CharlietheDog_v3(string* str_arr, const size_t arr_size) {
  if (!str_arr || !arr_size)
    return 0;

  pair<size_t, size_t> dog{string::npos, string::npos},
      home{string::npos, string::npos};
  vector<pair<size_t, size_t>> food_positions{};

  for (size_t i{}; i < arr_size; i++) {
    str_arr[i] = trim(str_arr[i]);

    for (size_t j{}; j < str_arr[i].length(); j++) {
      if ('c' == str_arr[i][j] || 'C' == str_arr[i][j])
        dog = make_pair(i, j);

      else if ('h' == str_arr[i][j] || 'H' == str_arr[i][j])
        home = make_pair(i, j);

      else if ('f' == str_arr[i][j] || 'F' == str_arr[i][j])
        food_positions.emplace_back(make_pair(i, j));
    }
  }

  sort(begin(food_positions), end(food_positions),
       [&dog](const pair<size_t, size_t>& x, const pair<size_t, size_t>& y) {
         return calculate_distance(x, dog) < calculate_distance(y, dog);
       });

  const unordered_map<string, size_t> precalculated_food_position_distances{
      [&food_positions]() {
        unordered_map<string, size_t> distances{};
        for (size_t i{}; i < food_positions.size() - 1; i++) {
          for (size_t j{i + 1}; j < food_positions.size(); j++) {
            string index{to_string(i) + to_string(j)};
            const size_t distance{
                calculate_distance(food_positions[i], food_positions[j])};
            distances[index] = distance;
            index = to_string(j) + to_string(i);
            distances[index] = distance;
          }
        }

        return distances;
      }()};

  size_t min_steps_count{string::npos};

  for (size_t i{}; i < food_positions.size(); i++) {
    size_t steps_count{calculate_distance(dog, food_positions[i])};

    unordered_set<size_t> already_visited_food_positions{{i}};

    size_t current_pos_index{i};

    for (size_t j{}; j < food_positions.size(); j++) {
      if (i == j)
        continue;

      const pair<size_t, size_t> next_closest_distance{
          find_closest_food_position(food_positions, current_pos_index,
                                     precalculated_food_position_distances,
                                     already_visited_food_positions)};
      steps_count += next_closest_distance.second;
      if (steps_count >= min_steps_count)
        break;
      already_visited_food_positions.insert(next_closest_distance.first);
      current_pos_index = next_closest_distance.first;
    }

    steps_count += calculate_distance(food_positions[current_pos_index], home);

    if (steps_count < min_steps_count)
      min_steps_count = steps_count;
  }

  return min_steps_count;
}

int main() {
  // string A[] = gets(stdin);
  // cout << CharlietheDog_v3(A, sizeof(A)/sizeof(*A));
  string B[] = {"FOOF", "OCOO", "OOOH", "FOOO"};
  cout << CharlietheDog_v3(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 11
  string C[] = {"OOOO", "OOFF", "OCHO", "OFOO"};
  cout << CharlietheDog_v3(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 7
  string D[] = {"FOOO", "OCOH", "OFOF", "OFOO"};
  cout << CharlietheDog_v3(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 10

  return 0;
}
