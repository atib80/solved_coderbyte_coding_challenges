/*
Coderbyte coding challenge: Weighted Path

Using the C++ language, have the function WeightedPath(strArr) take strArr which will be an array of strings which models a non-looping weighted Graph. 
The structure of the array will be as follows: The first element in the array will be the number of nodes N (points) in the array as a string. 
The next N elements will be the nodes which can be anything (A, B, C .. Brick Street, Main Street .. etc.). 
Then after the Nth element, the rest of the elements in the array will be the connections between all of the nodes along with their weights (integers) 
separated by the pipe symbol (|). They will look like this: (A|B|3, B|C|12 .. Brick Street|Main Street|14 .. etc.). 
Although, there may exist no connections at all.

An example of strArr may be: ["4","A","B","C","D","A|B|1","B|D|9","B|C|3","C|D|4"]. 
Your program should return the shortest path when the weights are added up from node to node from the first Node to the last Node in the array separated by dashes. 
So in the example above the output should be A-B-C-D. 
Here is another example with strArr being ["7","A","B","C","D","E","F","G","A|B|1","A|E|9","B|C|2","C|D|1","D|F|2","E|D|6","F|G|2"]. 
The output for this array should be A-B-C-D-F-G. 
There will only ever be one shortest path for the array. 
If no path between the first and last node exists, return -1. 
The array will at minimum have two nodes. 
Also, the connection A-B for example, means that A can get to B and B can get to A. 
A path may not go through any Node more than once.

Sample test cases:

Input:  "4","A","B","C","D", "A|B|2", "C|B|11", "C|D|3", "B|D|2"
Output: "A-B-D"

Input:  "4","x","y","z","w","x|y|2","y|z|14", "z|y|31"
Output: "-1"
*/

#include <iostream>
#include <sstream>
#include <cctype>
#include <climits>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

string trim(const string& str)
{
	const size_t str_len{ str.length() };

	if (!str_len) return string{};

	size_t first{}, last{ str_len - 1 };

	for (; first <= last; ++first)
	{
		if (!isspace(str[first])) break;
	}

	if (first > last) return string{};

	for (; last > first; --last)
	{
		if (!isspace(str[last])) break;
	}

	return str.substr(first, last - first + 1);
}

vector<string> split(const string& source, const char* needle, size_t const max_count = string::npos)
{
	vector<string> parts{};

	string needle_st { needle };

	const size_t source_len{ source.length() };

	const size_t needle_len{ needle_st.size() };

	if ((0u == source_len) || (0u == needle_len)) return parts;

	size_t number_of_parts{}, prev{};

	while (true)
	{
		const size_t current { source.find(needle_st, prev) };

		if (string::npos == current) break;

		number_of_parts++;

		if ((string::npos != max_count) && (parts.size() == max_count)) break;

		if ((current - prev) > 0) parts.emplace_back(source.substr(prev, current - prev));

		prev = current + needle_len;

		if (prev >= source_len) break;
	}

	if (prev < source_len)
	{
		if (string::npos == max_count) parts.emplace_back(source.substr(prev));

		else if ((string::npos != max_count) && (parts.size() < max_count)) parts.emplace_back(source.substr(prev));
	}

	return parts;
}

string shortest_path(vector<string> str_arr)
{
	const size_t N { stoul(str_arr[0]) };
	
	vector<string> vertices(N);
	
	unordered_map<string, int> graph_edge_weight{};

	for (size_t i{}; i < N; i++) vertices[i] = trim(str_arr[i + 1]);

	for (size_t i{ N + 1 }; i < str_arr.size(); i++)
	{
		str_arr[i] = trim(str_arr[i]);

		const size_t sep_pos1{ str_arr[i].find('|') };

		if (string::npos == sep_pos1) return "not possible";

		const string v1{ str_arr[i].substr(0, sep_pos1) };

		const size_t sep_pos2{ str_arr[i].find('|', sep_pos1 + 1) };

		if (string::npos == sep_pos2) return "not possible";

		const string v2{ str_arr[i].substr(sep_pos1 + 1, sep_pos2 - (sep_pos1 + 1)) };

		const int w{ stoi(str_arr[i].substr(sep_pos2 + 1)) };

		string key{ v1 + v2 };

		auto itr = graph_edge_weight.find(key);

		if (itr != end(graph_edge_weight)) {

			if (w < itr->second) itr->second = w;

		} else {

			key = v2 + v1;

			itr = graph_edge_weight.find(key);

			if (itr != end(graph_edge_weight)) {

				if (w < itr->second) itr->second = w;
			
			} else {

				key = v1 + v2;

				graph_edge_weight.insert(make_pair(key, w));

			}
		}
	}

	int min_distance{ INT_MAX };

	string current_path;

	const string source_vertex{ vertices[0] };

	const string destination_vertex{ vertices[N - 1] };

	vertices.erase(begin(vertices));

	sort(begin(vertices), end(vertices));

	do {
	
		string current_edge{ source_vertex + vertices[0] };

		if (graph_edge_weight.find(current_edge) == end(graph_edge_weight)) {

			current_edge = vertices[0] + source_vertex;

			if (graph_edge_weight.find(current_edge) == end(graph_edge_weight)) continue;
			
		}

		ostringstream oss{};

		oss << source_vertex << '-' << vertices[0];

		int current_weight{ graph_edge_weight.find(current_edge)->second };

		if (destination_vertex == vertices[0]) {
			
			if (current_weight < min_distance) {

				min_distance = current_weight;

				current_path = oss.str();

			}
			
			continue;
		}

		unordered_set<string> visited_nodes{ vertices[0] };

		bool is_path_connected{ true };

		for (size_t i{}; i < vertices.size() - 1; i++)
		{
			current_edge = vertices[i] + vertices[i + 1];

			if (visited_nodes.find(vertices[i + 1]) != end(visited_nodes)) {
				
				is_path_connected = false;
				break;

			}

			if (graph_edge_weight.find(current_edge) == end(graph_edge_weight)) {
				current_edge = vertices[i + 1] + vertices[i];

				if (graph_edge_weight.find(current_edge) == end(graph_edge_weight)) {
					
					is_path_connected = false;					
					break;

				}
			}

			visited_nodes.insert(vertices[i + 1]);

			current_weight += graph_edge_weight.find(current_edge)->second;

			if (current_weight >= min_distance) {

				is_path_connected = false;
				break;

			}

			oss << '-' << vertices[i + 1];

			if (destination_vertex == vertices[i + 1]) break;
		}

		if (is_path_connected && (current_weight < min_distance)) {

			min_distance = current_weight;

			current_path = oss.str();
		}

	} while (next_permutation(begin(vertices), end(vertices)));

	if (INT_MAX == min_distance) return "-1";

	return current_path;
}

int main()
{
	//cout << shortest_path(move(vector<string>{gets(stdin)}));
	// expected output: "A-B-C-D"
	cout << shortest_path(move(vector<string>{"4", "A", "B", "C", "D", "A|B|1", "B|D|9", "B|C|3", "C|D|4"})) << '\n';
	// expected output: "A-B-C-D-F-G"
	cout << shortest_path(move(vector<string>{"7", "A", "B", "C", "D", "E", "F", "G", "A|B|1", "A|E|9", "B|C|2", "C|D|1", "D|F|2", "E|D|6", "F|G|2"})) << '\n';
	// expected output: "A-B-D"
	cout << shortest_path(move(vector<string>{"4", "A", "B", "C", "D", "A|B|2", "C|B|11", "C|D|3", "B|D|2"})) << '\n';
	// expected output: "-1"
	cout << shortest_path(move(vector<string>{"4", "x", "y", "z", "w", "x|y|2", "y|z|14", "z|y|31"})) << '\n';
	// expected output: "A-F"
	cout << shortest_path(move(vector<string>{"6", "A", "B", "C", "D", "E", "F", "B|A|2", "A|F|3", "A|C|4", "B|D|1", "D|E|1", "C|D|4", "F|E|1"})) << '\n';
	// expected output: "D-B-A-F"
	cout << shortest_path(move(vector<string>{"6", "D", "B", "C", "A", "E", "F", "B|A|2", "A|F|3", "A|C|4", "B|D|1", "D|E|12", "C|D|4", "F|E|1"})) << '\n';
	// expected output: "C-D-F-G-E-B-H"
	cout << shortest_path(move(vector<string>{"8", "C", "B", "A", "D", "E", "F", "G", "H", "C|D|1", "D|F|2", "G|F|2", "G|E|1", "E|B|1", "H|B|1", "C|A|13", "B|A|2", "C|E|9"})) << '\n';
	// expected output: "c-a-b-e"
	cout << shortest_path(move(vector<string>{"5", "c", "a", "b", "d", "e", "c|a|3", "a|b|2", "a|d|34", "b|e|15", "e|d|2"})) << '\n';
	// expected output: "C-E-B-H"	
	cout << shortest_path(move(vector<string>{"8", "C", "B", "A", "D", "E", "F", "G", "H", "C|D|1", "D|F|2", "G|F|2", "G|E|1", "E|B|1", "H|B|1", "C|A|13", "B|A|2", "C|E|1"})) << '\n';

	return 0;
}
