/*
Coderbyte coding challenge: Shortest path

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
#include <queue>
#include <string>
#include <unordered_map>
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

struct vertex {
  vertex(const size_t vertex_index, const string& vertex_name)
      : index{vertex_index}, name{vertex_name} {}

  const size_t index;
  const string name;
  string parent;
  vector<size_t> neighbour_vertices;
};

string shortest_path_v1(string* str_arr, const size_t str_arr_size) {
  const size_t n{stoul(str_arr[0])};
  vector<vertex> graph{};
  unordered_map<string, size_t> graph_map{};

  for (size_t i{1}; i <= n; i++) {
    graph.emplace_back(i - 1, str_arr[i]);
    graph_map[str_arr[i]] = i - 1;
  }

  for (size_t i{n + 1}; i < str_arr_size; i++) {
    const vector<string> edges{split(str_arr[i], "-")};
    const size_t lvi{graph_map[edges[0]]};
    const size_t rvi{graph_map[edges[1]]};
    graph[lvi].neighbour_vertices.emplace_back(rvi);
    graph[rvi].neighbour_vertices.emplace_back(lvi);
  }

  vector<bool> is_vertex_visited(n);
  queue<size_t> q{{0}};

  while (!q.empty()) {
    is_vertex_visited[q.front()] = true;
    vertex& current_vertex{graph[q.front()]};
    q.pop();

    for (size_t i{}; i < current_vertex.neighbour_vertices.size(); i++) {
      const size_t nvi{
          graph_map[graph[current_vertex.neighbour_vertices[i]].name]};
      if (!is_vertex_visited[nvi]) {
        q.emplace(nvi);
        graph[current_vertex.neighbour_vertices[i]].parent =
            current_vertex.name;
        is_vertex_visited[nvi] = true;
      }
    }
  }

  string path{graph[n - 1].name};
  size_t index{n - 1};

  while (index) {
    if (graph[index].parent.empty())
      return "-1";

    path = graph[index].parent + "-" + path;
    index = graph_map[graph[index].parent];
  }

  return path;
}

int main() {
  // string A[] = gets(stdin);
  // cout << shortest_path_v1(A, sizeof(A)/sizeof(*A));
  string B[] = {"4", "A", "B", "C", "D", "A-B", "B-D", "B-C", "C-D"};
  cout << shortest_path_v1(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "A-B-D"
  string C[] = {"5",   "A",   "B",   "C",   "D",  "F",
                "A-B", "A-C", "B-C", "C-D", "D-F"};
  cout << shortest_path_v1(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "A-C-D-F"
  string D[] = {"4", "X", "Y", "Z", "W", "X-Y", "Y-Z", "X-W"};
  cout << shortest_path_v1(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "X-W"

  return 0;
}
