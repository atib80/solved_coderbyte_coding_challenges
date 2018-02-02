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

#include <cctype>
#include <iostream>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

string trim(const string &str)
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

vector<string> get_available_paths_from_input_string_array(
    const string *str_arr,
    const size_t str_arr_size)
{
    set<string> paths{};

    for (size_t i{}; i != str_arr_size; i++)
    {
        string path{trim(str_arr[i])};
        for (auto &ch : path)
            ch = tolower(ch);
        path.erase(1, 1);
        paths.insert(path);
        swap(path[0], path[1]);
        paths.insert(path);
    }

    return vector<string>(begin(paths), end(paths));
}

void find_max_path_length(vector<string> &paths,
                          const size_t current_path_index,
                          unordered_set<char> &visited_nodes,
                          size_t &max_path_length,
                          const size_t iter_count)
{
    const string current_path{paths[current_path_index]};
    paths[current_path_index] = "-1";

    for (size_t i{}; i < paths.size(); i++)
    {
        if (current_path_index == i || "-1" == paths[i])
            continue;

        if ((paths[i][0] == current_path[1]) && (paths[i][1] != current_path[0]) &&
            (visited_nodes.find(paths[i][0]) == end(visited_nodes)))
        {
            visited_nodes.insert(paths[i][0]);
            find_max_path_length(paths, i, visited_nodes, max_path_length,
                                 iter_count + 1);
            visited_nodes.erase(paths[i][0]);
        }
    }

    if (iter_count > max_path_length)
        max_path_length = iter_count;

    paths[current_path_index] = current_path;
}

string FarthestNodes(const string *str_arr, const size_t str_arr_size)
{
    vector<string> paths{
        get_available_paths_from_input_string_array(str_arr, str_arr_size)};

    size_t max_path_length{};
    unordered_set<char> visited_nodes{};

    for (size_t i{}; i < paths.size(); i++)
    {
        visited_nodes.insert(paths[i][0]);
        find_max_path_length(paths, i, visited_nodes, max_path_length, 1);
        visited_nodes.erase(paths[i][0]);
    }

    return to_string(max_path_length);
}

int main()
{
    // const string A[] = gets(stdin);
    // cout << FarthestNodes(A, sizeof(A)/sizeof(*A));
    const string B[] = {"a-b", "b-c", "b-d"};
    cout << FarthestNodes(B, sizeof(B) / sizeof(*B))
         << '\n'; // expected output: "2"
    const string C[] = {"b-e", "b-c", "c-d", "a-b", "e-f"};
    cout << FarthestNodes(C, sizeof(C) / sizeof(*C))
         << '\n'; // expected output: "4"
    const string D[] = {"b-a", "c-e", "b-c", "d-c"};
    cout << FarthestNodes(D, sizeof(D) / sizeof(*D))
         << '\n'; // expected output: "3"

    return 0;
}