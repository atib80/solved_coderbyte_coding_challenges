/*
Coderbyte coding challenge: Hamiltonian Path

Using the C++ language, have the function HamiltonianPath(strArr) take strArr which will be an array of length three. 
The first part of the array will be a list of vertices in a graph in the form (A,B,C,...), 
the second part of the array will be the edges connecting the vertices in the form (A-B,C-D,...) 
where each edge is bidirectional. The last part of the array will be a set of vertices in the form (X,Y,Z,...) 
and your program will have to determine whether or not the set of vertices given forms a Hamiltonian path on the graph 
which means that every vertex in the graph is visited only once in the order given.

For example: if strArr is ["(A,B,C,D)","(A-B,A-D,B-D,A-C)","(C,A,D,B)"] then the vertices (C,A,D,B) in this order 
do in fact form a Hamiltonian path on the graph so your program should return the string yes. 
If for example the last part of the array was (D,A,B,C) then this doesn't form a Hamiltonian path 
because once you get to B you can't get to C in the graph without passing through the visited vertices again. 
Here your program should return the vertex where the path had to terminate, in this case your program should return B.

The graph will have at least 2 vertices and all the vertices in the graph will be connected.

Sample test cases:

Input:  "(A,B,C,D)","(A-B,A-D,B-D,A-C)","(C,A,D,B)"
Output: "yes"

Input:  "(A,B,C)","(B-A,C-B)","(C,B,A)"
Output: "yes"

Input:  "(X,Y,Z,Q)","(X-Y,Y-Q,Y-Z)","(Z,Y,Q,X)"
Output: "Q"
*/

#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>

using namespace std;

string trim(const string& str)
{
	const size_t str_len{str.length()};

	if (!str_len)
		return string{};

	size_t first{}, last{str_len - 1};

	for (; first <= last; ++first)
	{
		if (!isspace(str[first]))
			break;
	}

	if (first > last)
		return string{};

	for (; last > first; --last)
	{
		if (!isspace(str[last]))
			break;
	}

	return str.substr(first, last - first + 1);
}

vector<string> split(const string& source,
                     const char* needle,
                     size_t const max_count = string::npos)
{
	vector<string> parts{};

	string needle_st{needle};

	const size_t source_len{source.length()};

	const size_t needle_len{needle_st.size()};

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

		if ((current - prev) > 0)
			parts.emplace_back(source.substr(prev, current - prev));

		prev = current + needle_len;

		if (prev >= source_len)
			break;
	}

	if (prev < source_len)
	{
		if (string::npos == max_count)
			parts.emplace_back(source.substr(prev));

		else if ((string::npos != max_count) && (parts.size() < max_count))
			parts.emplace_back(source.substr(prev));
	}

	return parts;
}

set<char> get_graph_vertices(const string& str)
{
	set<char> vertices{};

	auto vertices_str = split(str, ",");
	for (auto& vertex : vertices_str)
	{
		vertex = trim(vertex);
		if (!vertex.empty()) vertices.insert(vertex[0]);
	}

	return vertices;
}

set<string> get_graph_edges(const string& str)
{
	set<string> edges{};

	auto paths = split(str, ",");
	for (auto& path : paths)
	{
		path = trim(path);
		if (3 == path.size())
		{
			path.erase(1, 1);
			edges.insert(path);
			swap(path[0], path[1]);
			edges.insert(path);
		}
	}

	return edges;
}

vector<char> get_graph_hamiltonian_vertices(const string& str)
{
	vector<char> vertices{};

	auto vertices_str = split(str, ",");
	for (auto& vertex : vertices_str)
	{
		vertex = trim(vertex);
		if (!vertex.empty()) vertices.emplace_back(vertex[0]);
	}

	return vertices;
}

string HamiltonianPath(string* str_arr, const size_t str_arr_size)
{
	if (3 != str_arr_size) return "not possible";

	str_arr[0] = trim(str_arr[0]);
	str_arr[0].erase(begin(str_arr[0]));
	str_arr[0].erase(--end(str_arr[0]));

	set<char> vertices{get_graph_vertices(str_arr[0])};

	str_arr[1] = trim(str_arr[1]);
	str_arr[1].erase(begin(str_arr[1]));
	str_arr[1].erase(--end(str_arr[1]));

	set<string> paths{get_graph_edges(str_arr[1])};

	str_arr[2] = trim(str_arr[2]);
	str_arr[2].erase(begin(str_arr[2]));
	str_arr[2].erase(--end(str_arr[2]));

	vector<char> hpv{get_graph_hamiltonian_vertices(str_arr[2])};

	unordered_set<char> visited_vertices{hpv[0]};

	for (size_t i{}; i < hpv.size() - 1; i++)
	{
		const string current_path{hpv[i], hpv[i + 1]};

		if (visited_vertices.find(hpv[i + 1]) != end(visited_vertices)) return string(1, hpv[i]);

		if (paths.find(current_path) == end(paths)) return string(1, hpv[i]);

		visited_vertices.insert(hpv[i + 1]);
	}

	return "yes";
}

int main()
{
	// string A[] = gets(stdin);
	// cout << HamiltonianPath(A, sizeof(A)/sizeof(*A));
	string B[] = {"(A,B,C,D)","(A-B,A-D,B-D,A-C)","(C,A,D,B)"};
	cout << HamiltonianPath(B, sizeof(B) / sizeof(*B)) << '\n'; // expected output: "yes"
	string C[] = {"(A,B,C)","(B-A,C-B)","(C,B,A)"};
	cout << HamiltonianPath(C, sizeof(C) / sizeof(*C)) << '\n'; // expected output: "yes"
	string D[] = {"(X,Y,Z,Q)","(X-Y,Y-Q,Y-Z)","(Z,Y,Q,X)"};
	cout << HamiltonianPath(D, sizeof(D) / sizeof(*D)) << '\n'; // expected output: "Q"
	string E[] = {"(A,B,C,D)","(A-B,A-D,B-D,A-C)","(D,A,B,C)"};
	cout << HamiltonianPath(E, sizeof(E) / sizeof(*E)) << '\n'; // expected output: "B"
	string F[] = {"(A,B,C,D,E,F,G)","(A-B,A-D,B-D,B-C,C-F,E-D,F-E,G-F)","(G,F,E,D,B,C,A)"};
	cout << HamiltonianPath(F, sizeof(F) / sizeof(*F)) << '\n'; // expected output: "C"

	return 0;
}
