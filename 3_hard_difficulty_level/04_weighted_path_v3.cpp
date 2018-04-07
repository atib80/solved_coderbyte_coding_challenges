/*
Coderbyte coding challenge: Weighted Path v3

(alternative solution implemented by using brute-force method)

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
#include <limits>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

string trim(const string& input)
{
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
                     size_t const max_count = string::npos)
{
  vector<string> parts{};

  string needle_st{needle};

  const size_t source_len{source.length()};

  const size_t needle_len{needle_st.length()};

  if (!source_len)
    return parts;

  if (!needle_len)
  {
    const size_t upper_limit{max_count < source_len ? max_count : source_len};
    for (size_t i{}; i < upper_limit; i++)
      parts.emplace_back(1, source[i]);
    return parts;
  }

  size_t number_of_parts{}, prev{};

  while (true)
  {
    const size_t current{source.find(needle_st, prev)};

    if (string::npos == current)
      break;

    number_of_parts++;

    if ((string::npos != max_count) && (parts.size() == max_count))
      break;

    if (current - prev > 0)
      parts.emplace_back(source.substr(prev, current - prev));

    prev = current + needle_len;

    if (prev >= source_len)
      break;
  }

  if (prev < source_len)
  {
    if (string::npos == max_count)
      parts.emplace_back(source.substr(prev));

    else if (parts.size() < max_count)
      parts.emplace_back(source.substr(prev));
  }

  return parts;
}

string weighted_path_v3(string* str_arr, const size_t str_arr_size)
{
  const size_t N{stoul(str_arr[0])};

  string vertices(N, '*');

  unordered_map<string, int> graph_edge_weight{};

  for (size_t i{1}; i <= N; i++)
    vertices[i - 1] = str_arr[i][0];

  for (size_t i{N + 1}; i < str_arr_size; i++)
  {
    str_arr[i] = trim(str_arr[i]);

    const char v1{str_arr[i][0]};

    const char v2{str_arr[i][2]};

    const int w{stoi(str_arr[i].substr(4))};

    string key{{v1, v2}};

    auto itr = graph_edge_weight.find(key);

    if (itr != end(graph_edge_weight))
    {
      if (w < itr->second)
        itr->second = w;

      swap(key[0], key[1]);

      itr = graph_edge_weight.find(key);

      if (itr != end(graph_edge_weight))
        if (w < itr->second)
          itr->second = w;
    }
    else
    {
      graph_edge_weight[key] = w;
      swap(key[0], key[1]);
      graph_edge_weight[key] = w;
    }
  }

  int min_distance{numeric_limits<int>::max()};

  string current_path{"-1"};

  const char source_vertex{vertices.front()};

  const char destination_vertex{vertices.back()};

  vertices.erase(begin(vertices));

  sort(begin(vertices), end(vertices));

  do
  {
    string current_edge{{source_vertex, vertices.front()}};

    if (graph_edge_weight.find(current_edge) == end(graph_edge_weight))
      continue;

    ostringstream oss{};

    oss << source_vertex << '-' << vertices.front();

    int current_weight{graph_edge_weight[current_edge]};

    if (destination_vertex == vertices.front())
    {
      if (current_weight < min_distance)
      {
        min_distance = current_weight;

        current_path = oss.str();
      }

      continue;
    }

    unordered_set<char> visited_nodes{vertices.front()};

    bool is_path_connected{true};

    for (size_t i{}; i < vertices.length() - 1; i++)
    {
      current_edge.assign({vertices[i], vertices[i + 1]});

      if (visited_nodes.find(vertices[i + 1]) != end(visited_nodes))
      {
        is_path_connected = false;
        break;
      }

      if (graph_edge_weight.find(current_edge) == end(graph_edge_weight))
      {
        is_path_connected = false;
        break;
      }

      visited_nodes.insert(vertices[i + 1]);

      current_weight += graph_edge_weight[current_edge];

      if (current_weight >= min_distance)
      {
        is_path_connected = false;
        break;
      }

      oss << '-' << vertices[i + 1];

      if (destination_vertex == vertices[i + 1])
        break;
    }

    if (is_path_connected && current_weight < min_distance)
    {
      min_distance = current_weight;

      current_path = oss.str();
    }
  }
  while (next_permutation(begin(vertices), end(vertices)));

  return current_path;
}

int main()
{
  // string A[] = gets(stdin);
  // cout << weighted_path_v3(A, sizeof(A), sizeof(*A));  

  string B[] = {"4", "A", "B", "C", "D", "A|B|1", "B|D|9", "B|C|3", "C|D|4"};
  cout << weighted_path_v3(B, sizeof(B) / sizeof(*B)) << '\n'; // expected output: "A-B-C-D"

  string C[] = {"7", "A", "B", "C", "D", "E", "F", "G", "A|B|1", "A|E|9", "B|C|2", "C|D|1", "D|F|2", "E|D|6", "F|G|2"};
  cout << weighted_path_v3(C, sizeof(C) / sizeof(*C)) << '\n'; // expected output: "A-B-C-D-F-G"

  string D[] = {"4", "A", "B", "C", "D", "A|B|2", "C|B|11", "C|D|3", "B|D|2"};
  cout << weighted_path_v3(D, sizeof(D) / sizeof(*D)) << '\n'; // expected output: "A-B-D"

  string E[] = {"4", "x", "y", "z", "w", "x|y|2", "y|z|14", "z|y|31"};
  cout << weighted_path_v3(E, sizeof(E) / sizeof(*E)) << '\n'; // expected output: "-1"

  string F[] = {"6", "A", "B", "C", "D", "E", "F", "B|A|2", "A|F|3", "A|C|4", "B|D|1", "D|E|1", "C|D|4", "F|E|1"};
  cout << weighted_path_v3(F, sizeof(F) / sizeof(*F)) << '\n'; // expected output: "A-F"

  string G[] = {"6", "D", "B", "C", "A", "E", "F", "B|A|2", "A|F|3", "A|C|4", "B|D|1", "D|E|12", "C|D|4", "F|E|1"};
  cout << weighted_path_v3(G, sizeof(G) / sizeof(*G)) << '\n'; // expected output: "D-B-A-F"

  string H[] = {
    "8", "C", "B", "A", "D", "E", "F", "G", "H", "C|D|1", "D|F|2", "G|F|2", "G|E|1", "E|B|1", "H|B|1", "C|A|13", "B|A|2",
    "C|E|9"
  };
  cout << weighted_path_v3(H, sizeof(H) / sizeof(*H)) << '\n'; // expected output: "C-D-F-G-E-B-H"

  string I[] = {"5", "c", "a", "b", "d", "e", "c|a|3", "a|b|2", "a|d|34", "b|e|15", "e|d|2"};
  cout << weighted_path_v3(I, sizeof(I) / sizeof(*I)) << '\n'; // expected output: "c-a-b-e"

  string J[] = {
    "8", "C", "B", "A", "D", "E", "F", "G", "H", "C|D|1", "D|F|2","G|F|2", "G|E|1", "E|B|1", "H|B|1", "C|A|13", "B|A|2",
    "C|E|1"
  };
  cout << weighted_path_v3(J, sizeof(J) / sizeof(*J)) << '\n'; // expected output: "C-E-B-H"

  return 0;
}
