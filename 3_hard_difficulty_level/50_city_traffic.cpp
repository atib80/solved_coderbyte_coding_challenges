/*
Coderbyte coding challenge: City Traffic
Using the C++ language, have the function CityTraffic(strArr) read strArr which
will be a representation of an undirected graph in a form similar to an
adjacency list. Each element in the input will contain an integer which will
represent the population for that city, and then that will be followed by a
comma separated list of its neighboring cities and their populations (these will
be separated by a colon). For example: strArr may be ["1:[5]", "4:[5]", "3:[5]",
"5:[1,4,3,2]", "2:[5,15,7]", "7:[2,8]", "8:[7,38]", "15:[2]", "38:[8]"]. This
graph then looks like the following picture:
         38
         /
        8
       /
      7
     /
1   2
 \ / \
  5  15
 / \
4   3
Each node represents the population of that city and each edge represents a road
to that city. Your goal is to determine the maximum traffic that would occur via
a single road if everyone decided to go to that city. For example: if every
single person in all the cities decided to go to city 7, then via the upper road
the number of people coming in would be (8 + 38) = 46. If all the cities beneath
city 7 decided to go to it via the lower road, the number of people coming in
would be (2 + 15 + 1 + 3 + 4 + 5) = 30. So the maximum traffic coming into the
city 7 would be 46 because the maximum value of (30, 46) = 46.
Your program should determine the maximum traffic for every single city and
return the answers in a comma separated string in the format:
city:max_traffic,city:max_traffic,... The cities should be outputted in sorted
order by the city number. For the above example, the output would therefore be:
1:82,2:53,3:80,4:79,5:70,7:46,8:38,15:68,38:45. The cities will all be unique
positive integers and there will not be any cycles in the graph. There will
always be at least 2 cities in the graph.
Sample test cases:
Input:  "1:[5]", "2:[5]", "3:[5]", "4:[5]", "5:[1,2,3,4]"
Output: "1:14,2:13,3:12,4:11,5:4"
Input:  "1:[5]", "2:[5,18]", "3:[5,12]", "4:[5]", "5:[1,2,3,4]", "18:[2]",
"12:[3]" Output: "1:44,2:25,3:30,4:41,5:20,12:33,18:27"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
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

struct node {
  explicit node(const int id, vector<int> neighboring_node_ids)
      : node_id{id}, neighbors{move(neighboring_node_ids)} {}
  int node_id;
  vector<int> neighbors;
};

int find_max_traffic_for_graph_node(const map<int, node>& graph,
                                    const int node_id,
                                    unordered_set<int>& visited_nodes) {
  if (!graph.count(node_id))
    return 0;

  const vector<int>& current_node_neighbors{graph.at(node_id).neighbors};
  int max_traffic{node_id};

  for (const int next_neighbor_node_id : current_node_neighbors) {
    if (visited_nodes.count(next_neighbor_node_id))
      continue;
    visited_nodes.insert(next_neighbor_node_id);
    max_traffic += find_max_traffic_for_graph_node(graph, next_neighbor_node_id,
                                                   visited_nodes);
    visited_nodes.erase(next_neighbor_node_id);
  }

  return max_traffic;
}

map<int, node> create_city_graph_from_input_string_array(
    string* str_arr,
    const size_t str_arr_size) {
  map<int, node> city_graph{};

  for (size_t i{}; i < str_arr_size; i++) {
    str_arr[i] = trim(str_arr[i]);
    vector<string> parts{split(str_arr[i], ":[")};
    if (parts.size() < 2)
      continue;
    parts[1].erase(--end(parts[1]));
    const vector<string> neighbor_parts{split(parts[1], ",")};
    vector<int> neighbor_ids{};
    for (const string& node_id_str : neighbor_parts)
      neighbor_ids.emplace_back(stoi(node_id_str));
    city_graph.insert(
        make_pair(stoi(parts[0]), node{stoi(parts[0]), move(neighbor_ids)}));
  }

  return city_graph;
}

string find_maximum_traffic_for_all_city_nodes(
    const map<int, node>& city_graph) {
  unordered_set<int> visited_nodes{};
  ostringstream oss{};

  for (const pair<int, node>& current_node : city_graph) {
    visited_nodes.insert(current_node.first);
    int max_traffic_for_current_node{};

    for (const int neighbor_node_id : current_node.second.neighbors) {
      visited_nodes.insert(neighbor_node_id);

      const int current_neighbor_node_max_traffic{
          find_max_traffic_for_graph_node(city_graph, neighbor_node_id,
                                          visited_nodes)};

      if (current_neighbor_node_max_traffic > max_traffic_for_current_node)
        max_traffic_for_current_node = current_neighbor_node_max_traffic;

      visited_nodes.erase(neighbor_node_id);
    }

    oss << current_node.first << ':' << max_traffic_for_current_node << ',';

    visited_nodes.erase(current_node.first);
  }

  string output{oss.str()};
  output.erase(--end(output));
  return output;
}

string CityTraffic(string* str_arr, const size_t str_arr_size) {
  const map<int, node> city_graph{
      create_city_graph_from_input_string_array(str_arr, str_arr_size)};
  return find_maximum_traffic_for_all_city_nodes(city_graph);
}

int main() {
  // string A[] = gets(stdin);
  // cout << CityTraffic(A, sizeof(A)/sizeof(*A));
  string B[] = {"1:[5]",   "4:[5]",    "3:[5]",  "5:[1,4,3,2]", "2:[5,15,7]",
                "7:[2,8]", "8:[7,38]", "15:[2]", "38:[8]"};
  cout << CityTraffic(B, sizeof(B) / sizeof(*B)) << '\n';
  // expected output: "1:82,2:53,3:80,4:79,5:70,7:46,8:38,15:68,38:45"
  string C[] = {"1:[5]", "2:[5]", "3:[5]", "4:[5]", "5:[1,2,3,4]"};
  cout << CityTraffic(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "1:14,2:13,3:12,4:11,5:4"
  string D[] = {"1:[5]",       "2:[5,18]", "3:[5,12]", "4:[5]",
                "5:[1,2,3,4]", "18:[2]",   "12:[3]"};
  cout << CityTraffic(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "1:44,2:25,3:30,4:41,5:20,12:33,18:27"

  return 0;
}
