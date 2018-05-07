/*
Coderbyte coding challenge: Farthest Nodes

Using the C++ language, have the function FarthestNodes(strArr) read strArr
which will be an array of hyphenated letters representing paths between those
two nodes. For example: ["a-b","b-c","b-d"] means that there is a path from node
a to b (and b to a), b to c, and b to d. Your program should determine the
longest path that exists in the graph and return the length of that path. So for
the example above, your program should return 2 because of the paths a-b-c and
d-b-c. The path a-b-c also means that there is a path c-b-a. No cycles will
exist in the graph and every node will be connected to some other node in the
graph.

Sample test cases:

Input:  a-b","b-c","b-d"
Output: 2

Input:  "b-e","b-c","c-d","a-b","e-f"
Output: 4

Input:  "b-a","c-e","b-c","d-c"
Output: 3
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <unordered_set>
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

vector<string> get_available_paths_from_input_string_array(
    string* str_arr,
    const size_t str_arr_size) {
  set<string> paths{};

  for (size_t i{}; i < str_arr_size; i++) {
    if (str_arr[i].length() < 3)
      continue;
    str_arr[i].erase(1, 1);
    str_arr[i][0] = static_cast<char>(tolower(str_arr[i][0]));
    str_arr[i][1] = static_cast<char>(tolower(str_arr[i][1]));
    if (str_arr[i][0] == str_arr[i][1])
      continue;
    paths.insert(str_arr[i]);
    swap(str_arr[i][0], str_arr[i][1]);
    paths.insert(str_arr[i]);
  }

  return vector<string>(begin(paths), end(paths));
}

void find_max_path_length(const vector<string>& paths,
                          const size_t current_path_index,
                          unordered_set<char>& visited_nodes,
                          size_t& max_path_length,
                          const size_t iter_count) {
  for (size_t i{}; i < paths.size(); i++) {
    if (i == current_path_index || visited_nodes.count(paths[i][0]))
      continue;

    if (paths[current_path_index][1] == paths[i][0] &&
        paths[current_path_index][0] != paths[i][1]) {
      visited_nodes.insert(paths[i][0]);
      find_max_path_length(paths, i, visited_nodes, max_path_length,
                           iter_count + 1);
      visited_nodes.erase(paths[i][0]);
    }
  }

  if (iter_count > max_path_length)
    max_path_length = iter_count;
}

string FarthestNodes(string* str_arr, const size_t str_arr_size) {
  const vector<string> paths{
      get_available_paths_from_input_string_array(str_arr, str_arr_size)};

  size_t max_path_length{};
  unordered_set<char> visited_start_nodes{};
  unordered_set<char> visited_nodes{};

  for (size_t i{}; i < paths.size(); i++) {
    if (visited_start_nodes.count(paths[i][0]))
      continue;
    visited_start_nodes.insert(paths[i][0]);
    visited_nodes.insert(paths[i][0]);
    find_max_path_length(paths, i, visited_nodes, max_path_length, 1);
    visited_nodes.erase(paths[i][0]);
  }

  return to_string(max_path_length);
}

size_t find_max_path_length_v2(vector<string> paths) {
  const size_t paths_size{paths.size()};
  size_t max_path_length{};
  unordered_set<char> visited_start_nodes{};

  for (size_t i{}; i < paths.size(); i++) {
    if (visited_start_nodes.count(paths[i][0]))
      continue;
    visited_start_nodes.insert(paths[i][0]);

    queue<tuple<size_t, size_t, unordered_set<char>>> q{
        {make_tuple(i, 1, unordered_set<char>{paths[i][0]})}};

    while (!q.empty()) {
      const size_t current_path_index{get<0>(q.front())};
      const size_t iter_count{get<1>(q.front())};
      unordered_set<char> visited_nodes{move(get<2>(q.front()))};
      q.pop();

      for (size_t j{}; j < paths_size; j++) {
        if (j == current_path_index || visited_nodes.count(paths[j][0]))
          continue;

        if (paths[current_path_index][1] == paths[j][0] &&
            paths[current_path_index][0] != paths[j][1]) {
          visited_nodes.insert(paths[j][0]);
          q.emplace(make_tuple(j, iter_count + 1, visited_nodes));
          visited_nodes.erase(paths[j][0]);
        }
      }

      if (iter_count > max_path_length)
        max_path_length = iter_count;
    }
  }

  return max_path_length;
}

string FarthestNodes_v2(string* str_arr, const size_t str_arr_size) {
  vector<string> paths{
      get_available_paths_from_input_string_array(str_arr, str_arr_size)};

  return to_string(find_max_path_length_v2(move(paths)));
}

int main() {
  // string A[] = gets(stdin);
  // cout << FarthestNodes(A, sizeof(A)/sizeof(*A));
  string B[] = {"a-b", "b-c", "b-d"};
  cout << FarthestNodes(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "2"
  string C[] = {"b-e", "b-c", "c-d", "a-b", "e-f"};
  cout << FarthestNodes(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "4"
  string D[] = {"b-a", "c-e", "b-c", "d-c"};
  cout << FarthestNodes(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "3"

  return 0;
}
