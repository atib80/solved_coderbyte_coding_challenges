/*
Coderbyte coding challenge: Shortest path v2

(alternative iterative solution implemented by using queue, list and
unordered_map<string, unordered_set<string>> [simplified edge list
representation of graph's connected vertices])

Using the C++ language, have the function ShortestPath(strArr) take strArr which
will be an array of strings which models a non-looping Graph. The structure of
the array will be as follows: The first element in the array will be the number
of nodes N (points) in the array as a string. The next N elements will be the
nodes which can be anything (A, B, C .. Brick Street, Main Street .. etc.). Then
after the Nth element, the rest of the elements in the array will be the
connections between all of the nodes. They will look like this: (A-B, B-C ..
Brick Street-Main Street .. etc.). Although, there may exist no connections at
all.

An example of strArr may be: ["4","A","B","C","D","A-B","B-D","B-C","C-D"]. Your
program should return the shortest path from the first Node to the last Node in
the array separated by dashes. So in the example above the output should be
A-B-D. Here is another example with strArr being
["7","A","B","C","D","E","F","G","A-B","A-E","B-C","C-D","D-F","E-D","F-G"]. The
output for this array should be A-E-D-F-G. There will only ever be one shortest
path for the array. If no path between the first and last node exists, return
-1. The array will at minimum have two nodes. Also, the connection A-B for
example, means that A can get to B and B can get to A.

Hard challenges are worth 15 points and you are not timed for them.

Sample test cases:

Input:   "5","A","B","C","D","F","A-B","A-C","B-C","C-D","D-F"
Output:  "A-C-D-F"

Input:  "4","X","Y","Z","W","X-Y","Y-Z","X-W"
Output: "X-W"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <unordered_map>
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

vector<string> split(const string& source,
                     const char* needle,
                     size_t const max_count = string::npos) {
  vector<string> parts{};

  string needle_st{needle};

  const size_t source_len{source.length()};

  const size_t needle_len{needle_st.length()};

  if (!source_len)
    return parts;

  if (!needle_len) {
    const size_t upper_limit{max_count < source_len ? max_count : source_len};
    for (size_t i{}; i < upper_limit; i++)
      parts.emplace_back(1, source[i]);
    return parts;
  }

  size_t number_of_parts{}, prev{};

  while (true) {
    const size_t current{source.find(needle_st, prev)};

    if (string::npos == current)
      break;

    number_of_parts++;

    if (string::npos != max_count && parts.size() == max_count)
      break;

    if (current - prev > 0)
      parts.emplace_back(source.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (prev < source_len) {
    if (string::npos == max_count)
      parts.emplace_back(source.substr(prev));

    else if (parts.size() < max_count)
      parts.emplace_back(source.substr(prev));
  }

  return parts;
}

struct path_segment {
  string current_vertex;
  string travelled_path;
  unordered_set<string> visited_vertices;
  size_t travelled_distance;

  path_segment(const string& cv,
               const string& path,
               const unordered_set<string>& prev_visited_vertices = {},
               const size_t distance = 0)
      : current_vertex{cv},
        travelled_path{path},
        visited_vertices{prev_visited_vertices},
        travelled_distance{distance} {}
};

void create_graph_adjacency_list(
    string* str_arr,
    const size_t str_arr_size,
    vector<string>& vertices,
    unordered_map<string, unordered_set<string>>& adj_list) {
  const size_t n{stoul(str_arr[0])};

  for (size_t i{1}; i <= n; i++) {
    vertices.emplace_back(str_arr[i]);
    adj_list.insert(make_pair(str_arr[i], unordered_set<string>{}));
  }

  for (size_t i{n + 1}; i < str_arr_size; i++) {
    const vector<string> edges{split(str_arr[i], "-", 2)};
    if (adj_list.find(edges[0]) == end(adj_list))
      adj_list.insert(make_pair(edges[0], unordered_set<string>{}));
    adj_list[edges[0]].insert(edges[1]);
    if (adj_list.find(edges[1]) == end(adj_list))
      adj_list.insert(make_pair(edges[1], unordered_set<string>{}));
    adj_list[edges[1]].insert(edges[0]);
  }
}

string shortest_path_v2(string* str_arr, const size_t str_arr_size) {
  vector<string> vertices{};
  unordered_map<string, unordered_set<string>> adj_list{};

  create_graph_adjacency_list(str_arr, str_arr_size, vertices, adj_list);

  size_t shortest_path_distance{string::npos};
  string shortest_path{"-1"};

  list<path_segment> visited_node_data{};
  list<path_segment>::iterator list_iter{visited_node_data.insert(
      end(visited_node_data),
      move(path_segment(vertices.front(), vertices.front(), {vertices.front()},
                        0)))};
  queue<list<path_segment>::iterator> q{{list_iter}};

  while (!q.empty()) {
    list_iter = q.front();
    q.pop();

    for (const string& neighbor_vertex : adj_list[list_iter->current_vertex]) {
      if (list_iter->visited_vertices.find(neighbor_vertex) !=
          end(list_iter->visited_vertices))
        continue;
      list_iter->visited_vertices.insert(neighbor_vertex);

      if (list_iter->travelled_distance + 1 >= shortest_path_distance)
        break;
      if (neighbor_vertex == vertices.back()) {
        shortest_path_distance = list_iter->travelled_distance + 1;
        shortest_path = list_iter->travelled_path + "-" + vertices.back();
        break;
      }
      list<path_segment>::iterator iter{visited_node_data.insert(
          end(visited_node_data),
          move(path_segment(
              neighbor_vertex,
              move(list_iter->travelled_path + "-" + neighbor_vertex),
              list_iter->visited_vertices,
              list_iter->travelled_distance + 1)))};
      q.emplace(iter);
      list_iter->visited_vertices.erase(neighbor_vertex);
    }
  }

  return shortest_path;
}

int main() {
  // string A[] = gets(stdin);
  // cout << shortest_path_v2(A, sizeof(A)/sizeof(*A));
  string B[] = {"4", "A", "B", "C", "D", "A-B", "B-D", "B-C", "C-D"};
  cout << shortest_path_v2(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "A-B-D"
  string C[] = {"5",   "A",   "B",   "C",   "D",  "F",
                "A-B", "A-C", "B-C", "C-D", "D-F"};
  cout << shortest_path_v2(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "A-C-D-F"
  string D[] = {"4", "X", "Y", "Z", "W", "X-Y", "Y-Z", "X-W"};
  cout << shortest_path_v2(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "X-W"

  return 0;
}
