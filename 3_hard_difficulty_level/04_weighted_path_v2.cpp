/*
Coderbyte coding challenge: Weighted Path v2

(recursive solution)

Using the C++ language, have the function WeightedPath(strArr) take strArr which
will be an array of strings which models a non-looping weighted Graph. The
structure of the array will be as follows: The first element in the array will
be the number of nodes N (points) in the array as a string. The next N elements
will be the nodes which can be anything (A, B, C .. Brick Street, Main Street ..
etc.). Then after the Nth element, the rest of the elements in the array will be
the connections between all of the nodes along with their weights (integers)
separated by the pipe symbol (|). They will look like this: (A|B|3, B|C|12 ..
Brick Street|Main Street|14 .. etc.). Although, there may exist no connections
at all.

An example of strArr may be:
["4","A","B","C","D","A|B|1","B|D|9","B|C|3","C|D|4"]. Your program should
return the shortest path when the weights are added up from node to node from
the first Node to the last Node in the array separated by dashes. So in the
example above the output should be A-B-C-D. Here is another example with strArr
being
["7","A","B","C","D","E","F","G","A|B|1","A|E|9","B|C|2","C|D|1","D|F|2","E|D|6","F|G|2"].
The output for this array should be A-B-C-D-F-G.
There will only ever be one shortest path for the array.
If no path between the first and last node exists, return -1.
The array will at minimum have two nodes.
Also, the connection A-B for example, means that A can get to B and B can get to
A. A path may not go through any Node more than once.

Sample test cases:

Input:  "4","A","B","C","D", "A|B|2", "C|B|11", "C|D|3", "B|D|2"
Output: "A-B-D"

Input:  "4","x","y","z","w","x|y|2","y|z|14", "z|y|31"
Output: "-1"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
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
  size_t path_weight;

  path_segment(const string& cv,
               const string& path,
               const unordered_set<string>& prev_visited_vertices =
                   unordered_set<string>{},
               const size_t weight = 0)
      : current_vertex{cv},
        travelled_path{path},
        visited_vertices{prev_visited_vertices},
        path_weight{weight} {}
};

void create_graph_adjacency_list(
    string* str_arr,
    const size_t str_arr_size,
    vector<string>& vertices,
    unordered_map<string, unordered_map<string, size_t>>&
        adjacent_vertices_and_their_weights) {
  const size_t n{stoul(str_arr[0])};

  for (size_t i{1}; i <= n; i++) {
    vertices.emplace_back(str_arr[i]);
    adjacent_vertices_and_their_weights.insert(
        make_pair(str_arr[i], unordered_map<string, size_t>{}));
  }

  for (size_t i{n + 1}; i < str_arr_size; i++) {
    const vector<string> edge_weight{split(str_arr[i], "|")};
    if (adjacent_vertices_and_their_weights.find(edge_weight[0]) ==
        end(adjacent_vertices_and_their_weights))
      adjacent_vertices_and_their_weights.insert(
          make_pair(edge_weight[0], unordered_map<string, size_t>{}));
    if (adjacent_vertices_and_their_weights[edge_weight[0]].find(
            edge_weight[1]) ==
        end(adjacent_vertices_and_their_weights[edge_weight[0]]))
      adjacent_vertices_and_their_weights[edge_weight[0]].insert(
          make_pair(edge_weight[1], stoul(edge_weight[2])));
    else
      adjacent_vertices_and_their_weights[edge_weight[0]][edge_weight[1]] =
          stoul(edge_weight[2]);

    if (adjacent_vertices_and_their_weights.find(edge_weight[1]) ==
        end(adjacent_vertices_and_their_weights))
      adjacent_vertices_and_their_weights.insert(
          make_pair(edge_weight[1], unordered_map<string, size_t>{}));
    if (adjacent_vertices_and_their_weights[edge_weight[1]].find(
            edge_weight[0]) ==
        end(adjacent_vertices_and_their_weights[edge_weight[1]]))
      adjacent_vertices_and_their_weights[edge_weight[1]].insert(
          make_pair(edge_weight[0], stoul(edge_weight[2])));
    else
      adjacent_vertices_and_their_weights[edge_weight[1]][edge_weight[0]] =
          stoul(edge_weight[2]);
  }
}

void find_shortest_path(
    const unordered_map<string, unordered_map<string, size_t>>&
        adjacent_vertices_and_their_weights,
    unordered_set<string>& already_visited_vertices,
    const string& current_vertex,
    const string& dest_vertex,
    string& shortest_path,
    vector<string>& shortest_path_vertices,
    size_t& shortest_path_weight,
    const size_t path_weight = 0) {
  const auto cv_iter = adjacent_vertices_and_their_weights.find(current_vertex);
  if (cv_iter == end(adjacent_vertices_and_their_weights))
    return;

  for (const auto& neighbor_vertex : cv_iter->second) {
    if (already_visited_vertices.find(neighbor_vertex.first) !=
        end(already_visited_vertices))
      continue;

    if (path_weight + neighbor_vertex.second >= shortest_path_weight)
      continue;

    if (neighbor_vertex.first == dest_vertex) {
      shortest_path_weight = path_weight + neighbor_vertex.second;
      ostringstream oss{};
      for (const string& v : shortest_path_vertices)
        oss << v << '-';
      oss << dest_vertex;
      shortest_path = oss.str();
      continue;
    }

    already_visited_vertices.insert(neighbor_vertex.first);
    shortest_path_vertices.emplace_back(neighbor_vertex.first);

    find_shortest_path(adjacent_vertices_and_their_weights,
                       already_visited_vertices, neighbor_vertex.first,
                       dest_vertex, shortest_path, shortest_path_vertices,
                       shortest_path_weight,
                       path_weight + neighbor_vertex.second);

    shortest_path_vertices.pop_back();
    already_visited_vertices.erase(neighbor_vertex.first);
  }
}

string weighted_path_v2(string* str_arr, const size_t str_arr_size) {
  vector<string> vertices{};
  unordered_map<string, unordered_map<string, size_t>>
      adjacent_vertices_and_their_weights{};

  create_graph_adjacency_list(str_arr, str_arr_size, vertices,
                              adjacent_vertices_and_their_weights);

  size_t shortest_path_weight{string::npos};
  string shortest_path{"-1"};
  unordered_set<string> already_visited_vertices{};
  vector<string> shortest_path_vertices{vertices.front()};

  find_shortest_path(adjacent_vertices_and_their_weights,
                     already_visited_vertices, vertices.front(),
                     vertices.back(), shortest_path, shortest_path_vertices,
                     shortest_path_weight, 0);

  return shortest_path;
}

int main() {
  // string A[] = gets(stdin);
  // cout << weighted_path_v2(A, sizeof(A)/sizeof(*A));
  string B[] = {"4", "A", "B", "C", "D", "A|B|1", "B|D|9", "B|C|3", "C|D|4"};
  cout << weighted_path_v2(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "A-B-C-D"
  string C[] = {"7",     "A",     "B",     "C",     "D",
                "E",     "F",     "G",     "A|B|1", "A|E|9",
                "B|C|2", "C|D|1", "D|F|2", "E|D|6", "F|G|2"};
  cout << weighted_path_v2(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "A-B-C-D-F-G"
  string D[] = {"4", "A", "B", "C", "D", "A|B|2", "C|B|11", "C|D|3", "B|D|2"};
  cout << weighted_path_v2(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "A-B-D"
  string E[] = {"4", "x", "y", "z", "w", "x|y|2", "y|z|14", "z|y|31"};
  cout << weighted_path_v2(E, sizeof(E) / sizeof(*E))
       << '\n';  // expected output: "-1"
  string F[] = {"6",     "A",     "B",     "C",     "D",     "E",     "F",
                "B|A|2", "A|F|3", "A|C|4", "B|D|1", "D|E|1", "C|D|4", "F|E|1"};
  cout << weighted_path_v2(F, sizeof(F) / sizeof(*F))
       << '\n';  // expected output: "A-F"
  string G[] = {"6",     "D",     "B",     "C",     "A",      "E",     "F",
                "B|A|2", "A|F|3", "A|C|4", "B|D|1", "D|E|12", "C|D|4", "F|E|1"};
  cout << weighted_path_v2(G, sizeof(G) / sizeof(*G))
       << '\n';  // expected output: "D-B-A-F"
  string H[] = {"8",     "C",     "B",     "A",      "D",     "E",
                "F",     "G",     "H",     "C|D|1",  "D|F|2", "G|F|2",
                "G|E|1", "E|B|1", "H|B|1", "C|A|13", "B|A|2", "C|E|9"};
  cout << weighted_path_v2(H, sizeof(H) / sizeof(*H))
       << '\n';  // expected output: "C-D-F-G-E-B-H"
  string I[] = {"5",     "c",     "a",      "b",      "d",    "e",
                "c|a|3", "a|b|2", "a|d|34", "b|e|15", "e|d|2"};
  cout << weighted_path_v2(I, sizeof(I) / sizeof(*I))
       << '\n';  // expected output: "c-a-b-e"
  string J[] = {"8",     "C",     "B",     "A",      "D",     "E",
                "F",     "G",     "H",     "C|D|1",  "D|F|2", "G|F|2",
                "G|E|1", "E|B|1", "H|B|1", "C|A|13", "B|A|2", "C|E|1"};
  cout << weighted_path_v2(J, sizeof(J) / sizeof(*J))
       << '\n';  // expected output: "C-E-B-H"

  return 0;
}
