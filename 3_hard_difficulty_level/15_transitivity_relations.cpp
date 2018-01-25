/*
Coderbyte coding challenge: Transitivity Relations

Using the C++ language, have the function TransitivityRelations(strArr) read the strArr parameter being passed
which will make up an NxN matrix where the rows are separated by each pair of parentheses (the matrix will range from 2x2 to 5x5).
The matrix represents connections between nodes in a graph where each node corresponds to the Nth element in the matrix (with 0 being the first node).
If a connection exists from one node to another, it will be represented by a 1,
if not it will be represented by a 0.
For example: suppose strArr were a 3x3 matrix with input ["(1,1,1)","(1,0,0)","(0,1,0)"],
this means that there is a connection from node 0->0, 0->1, and 0->2.
For node 1 the connections are 1->0, and for node 2 the connections are 2->1.
This can be interpreted as a connection existing from node X to node Y if there is a 1 in the Xth row and Yth column.
Note: a connection from X->Y does not imply a connection from Y->X.

What your program should determine is whether or not the matrix, which represents connections among the nodes, is transitive.
A transitive relation means that if the connections 0->1 and 1->2 exist for example, then there must exist the connection 0->2.
More generally, if there is a relation xRy and yRz, then xRz should exist within the matrix.
If a matrix is completely transitive, return the string transitive.
If it isn't, your program should return the connections needed, in the following format,
in order for the matrix to be transitive: (N1,N2)-(N3,N4)-(...).
So for the example above, your program should return (1,2)-(2,0).
You can ignore the reflexive property of nodes in your answers.
Return the connections needed in lexicographical order [e.g. (0,1)-(0,4)-(1,4)-(2,3)-(4,1)].

Sample test cases:

Input:  "(1,1,1)","(0,1,1)","(0,1,1)"
Output: "transitive"

Input:  "(0,1,0,0)","(0,0,1,0)","(0,0,1,1)","(0,0,0,1)"
Output: "(0,2)-(0,3)-(1,3)"
*/

#define _CRT_SECURE_NO_WARNINGS

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <stdexcept>
#include <algorithm>

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

vector<string> split(const string &source, const char *needle, size_t const max_count = string::npos)
{
    vector<string> parts{};

    string needle_st{needle};

    const size_t source_len{source.length()};

    const size_t needle_len{needle_st.size()};

    if ((0u == source_len) || (0u == needle_len))
        return parts;

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

vector<vector<size_t>> parse_matrix_values(const string *str_arr, const size_t str_arr_size)
{
    const size_t dim{str_arr_size};

    vector<vector<size_t>> matrix(dim, vector<size_t>{});

    for (auto &row : matrix)
        row.resize(dim);

    size_t i{};

    for_each(str_arr, str_arr + str_arr_size, [&](const string &str) {
        string line{trim(str)};
        line.erase(begin(line));
        line.erase(--end(line));

        const vector<string> row_values_str = split(line, ",", dim);

        if (dim != row_values_str.size())
        {
            ostringstream oss{};
            oss << "Row " << (i + 1) << " of matrix does not contain " << dim << " entries!";
            throw runtime_error(oss.str());
        }

        for (size_t j{}; j != dim; j++)
            matrix[i][j] = stoul(row_values_str[j]);
        i++;
    });

    return matrix;
}

void find_missing_matrix_connections(vector<vector<size_t>> &matrix, set<string> &connections,
                                     set<string> &missing_connections)
{
    for (size_t i{}; i < matrix.size(); i++)
    {
        for (size_t j{}; j < matrix.size(); j++)
        {
            if (i == j || !matrix[i][j])
                continue;

            for (size_t k{}; k < matrix.size(); k++)
            {
                if (j == k || i == k || !matrix[j][k])
                    continue;

                char buffer[16];
                sprintf(buffer, "(%lu,%lu)", i, k);

                if (connections.find(buffer) == end(connections))
                {
                    connections.insert(buffer);
                    missing_connections.insert(buffer);
                    matrix[i][k] = 1;
                    find_missing_matrix_connections(matrix, connections, missing_connections);
                }
            }
        }
    }
}

string TransitivityRelations(string *str_arr, const size_t str_arr_size)
{
    vector<vector<size_t>> matrix{parse_matrix_values(str_arr, str_arr_size)};

    const size_t N{matrix.size()};

    set<string> connections{};

    char buffer[16];

    for (size_t i{}; i < N; i++)
    {
        for (size_t j{}; j < N; j++)
        {
            if (i == j || !matrix[i][j])
                continue;

            sprintf(buffer, "(%lu,%lu)", i, j);

            connections.insert(buffer);
        }
    }

    set<string> missing_connections{};

    find_missing_matrix_connections(matrix, connections, missing_connections);

    if (missing_connections.empty())
        return "transitive";

    ostringstream oss{};

    for (const string &path : missing_connections)
        oss << path << '-';

    string result{oss.str()};
    result.erase(--end(result));
    return result;
}

int main()
{
    // string A[] = gets(stdin);
    // cout << TransitivityRelations(A, sizeof(A) / sizeof(*A));
    string A[] = {"(1,1,1)", "(1,0,0)", "(0,1,0)"};
    cout << TransitivityRelations(A, sizeof(A) / sizeof(*A)) << '\n'; // expected output: "(1,2)-(2,0)"
    string B[] = {"(1,1,1)", "(0,1,1)", "(0,1,1)"};
    cout << TransitivityRelations(B, sizeof(B) / sizeof(*B)) << '\n'; // expected output: "transitive"
    string C[] = {"(0,1,0,0)", "(0,0,1,0)", "(0,0,1,1)", "(0,0,0,1)"};
    cout << TransitivityRelations(C, sizeof(C) / sizeof(*C)) << '\n'; // expected output: "(0,2)-(0,3)-(1,3)"

    return 0;
}
