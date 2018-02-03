/*
Coderbyte coding challenge: Vertex Covering

Using the C++ language, have the function VertexCovering(strArr) take strArr
which will be an array of length three. The first part of the array will be a
list of vertices in a graph in the form (A,B,C,...), the second part of the
array will be the edges connecting the vertices in the form (A-B,C-D,...) where
each edge is bidirectional. The last part of the array will be a set of vertices
in the form (X,Y,Z,...) and your program will have to determine whether or not
the set of vertices given covers every edge in the graph such that every edge is
incident to at least one vertex in the set.

For example: if strArr is ["(A,B,C,D)","(A-B,A-D,B-D,A-C)","(A,B)"] then the
vertices (A,B) are in fact one of the endpoints of every edge in the graph, so
every edge has been accounted for. Therefore your program should return the
string yes. But, if for example the last part of the array was (C,B) then these
vertices don't cover all the edges because the edge connecting A-D is left out.
If this is the case your program should return the edges given in the second
part of the array that are left out in the same order they were listed, so for
this example your program should return (A-D).

The graph will have at least 2 vertices and all the vertices in the graph will
be connected. The third part of the array listing the vertices may be empty,
where it would only contain the parenthesis with no values within it: "()"

Sample test cases:

Input:  "(A,B,C,D)","(A-B,A-D,B-D,A-C)","(C)"
Output: "(A-B,A-D,B-D)"

Input:  "(X,Y,Z,Q)","(X-Y,Y-Q,Y-Z)","(Z,Y,Q)"
Output: "yes"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

string trim(const string& str) {
  const size_t str_len{str.length()};

  if (!str_len)
    return string{};

  size_t first{}, last{str_len - 1};

  for (; first <= last; ++first) {
    if (!isspace(str[first]))
      break;
  }

  if (first > last)
    return string{};

  for (; last > first; --last) {
    if (!isspace(str[last]))
      break;
  }

  return str.substr(first, last - first + 1);
}

vector<string> split(const string& source,
                     const char* needle,
                     size_t const max_count = string::npos) {
  vector<string> parts{};

  string needle_st{needle};

  const size_t source_len{source.length()};

  const size_t needle_len{needle_st.size()};

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

    if ((string::npos != max_count) && (parts.size() == max_count))
      break;

    if ((current - prev) > 0)
      parts.emplace_back(source.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (prev < source_len) {
    if (string::npos == max_count)
      parts.emplace_back(source.substr(prev));

    else if ((string::npos != max_count) && (parts.size() < max_count))
      parts.emplace_back(source.substr(prev));
  }

  return parts;
}

unordered_set<char> get_graph_vertices(const string& str) {
  unordered_set<char> vertices{};

  auto vertices_str = split(str, ",");
  for (auto& vertex : vertices_str) {
    vertex = trim(vertex);
    if (!vertex.empty())
      vertices.insert(vertex[0]);
  }

  return vertices;
}

vector<string> get_graph_edges(const string& str) {
  vector<string> edges{};

  auto paths = split(str, ",");
  for (auto& path : paths) {
    path = trim(path);
    edges.emplace_back(path);
  }

  return edges;
}

unordered_set<char> get_target_vertices(const string& str) {
  unordered_set<char> vertices{};

  auto vertices_str = split(str, ",");
  for (auto& vertex : vertices_str) {
    vertex = trim(vertex);
    if (!vertex.empty())
      vertices.insert(vertex[0]);
  }

  return vertices;
}

string VertexCovering(string* str_arr, const size_t str_arr_size) {
  if (str_arr_size < 3u)
    return "not possible";

  str_arr[0] = trim(str_arr[0]);
  str_arr[0].erase(begin(str_arr[0]));
  str_arr[0].erase(--end(str_arr[0]));

  const unordered_set<char> graph_vertices{get_graph_vertices(str_arr[0])};

  if (graph_vertices.size() < 2u)
    return "not possible";

  str_arr[1] = trim(str_arr[1]);
  str_arr[1].erase(begin(str_arr[1]));
  str_arr[1].erase(--end(str_arr[1]));

  const vector<string> graph_edges{get_graph_edges(str_arr[1])};

  if (graph_edges.empty())
    return "not possible";

  str_arr[2] = trim(str_arr[2]);
  str_arr[2].erase(begin(str_arr[2]));
  str_arr[2].erase(--end(str_arr[2]));

  const unordered_set<char> target_vertices{get_target_vertices(str_arr[2])};

  ostringstream oss{};
  oss << '(';
  const size_t edges_count{graph_edges.size()};

  bool is_found_not_connected_vertex{};

  for (size_t i{}; i < edges_count; i++) {
    if (target_vertices.find(graph_edges[i][0]) != end(target_vertices) ||
        target_vertices.find(graph_edges[i][2]) != end(target_vertices))
      continue;

    is_found_not_connected_vertex = true;
    oss << graph_edges[i] << ',';
  }

  if (!is_found_not_connected_vertex)
    return "yes";

  string result{oss.str()};
  result.back() = ')';
  return result;
}

int main() {
  
  string A[] = gets(stdin);
  cout << VertexCovering(A, sizeof(A)/sizeof(*A));
  // string B[] = {"(A,B,C,D)", "(A-B,A-D,B-D,A-C)", "(A,B)"};
  // cout << VertexCovering(B, sizeof(B) / sizeof(*B)) << '\n';  // expected output: "yes"
  // string C[] = {"(A,B,C,D)", "(A-B,A-D,B-D,A-C)", "(C,B)"};
  // cout << VertexCovering(C, sizeof(C) / sizeof(*C)) << '\n';  // expected output: "(A,D)"
  // string D[] = {"(A,B,C,D)", "(A-B,A-D,B-D,A-C)", "(C)"};
  // cout << VertexCovering(D, sizeof(D) / sizeof(*D)) << '\n';  // expected output: "(A-B,A-D,B-D)"
  // string E[] = {"(X,Y,Z,Q)", "(X-Y,Y-Q,Y-Z)", "(Z,Y,Q)"};
  // cout << VertexCovering(E, sizeof(E) / sizeof(*E)) << '\n';  // expected output: "yes"

  return 0;
}
