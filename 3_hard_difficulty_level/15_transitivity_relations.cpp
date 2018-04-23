/*
Coderbyte coding challenge: Transitivity Relations

Using the C++ language, have the function TransitivityRelations(strArr) read the
strArr parameter being passed which will make up an NxN matrix where the rows
are separated by each pair of parentheses (the matrix will range from 2x2 to
5x5). The matrix represents connections between nodes in a graph where each node
corresponds to the Nth element in the matrix (with 0 being the first node). If a
connection exists from one node to another, it will be represented by a 1, if
not it will be represented by a 0. For example: suppose strArr were a 3x3 matrix
with input ["(1,1,1)","(1,0,0)","(0,1,0)"], this means that there is a
connection from node 0->0, 0->1, and 0->2. For node 1 the connections are 1->0,
and for node 2 the connections are 2->1. This can be interpreted as a connection
existing from node X to node Y if there is a 1 in the Xth row and Yth column.
Note: a connection from X->Y does not imply a connection from Y->X.

What your program should determine is whether or not the matrix, which
represents connections among the nodes, is transitive. A transitive relation
means that if the connections 0->1 and 1->2 exist for example, then there must
exist the connection 0->2. More generally, if there is a relation xRy and yRz,
then xRz should exist within the matrix. If a matrix is completely transitive,
return the string transitive. If it isn't, your program should return the
connections needed, in the following format, in order for the matrix to be
transitive: (N1,N2)-(N3,N4)-(...). So for the example above, your program should
return (1,2)-(2,0). You can ignore the reflexive property of nodes in your
answers. Return the connections needed in lexicographical order [e.g.
(0,1)-(0,4)-(1,4)-(2,3)-(4,1)].

Sample test cases:

Input:  "(1,1,1)","(0,1,1)","(0,1,1)"
Output: "transitive"

Input:  "(0,1,0,0)","(0,0,1,0)","(0,0,1,1)","(0,0,0,1)"
Output: "(0,2)-(0,3)-(1,3)"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>
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

vector<vector<int>> parse_matrix_values(const string* str_arr,
                                        const size_t dim) {
  vector<vector<int>> matrix(dim, vector<int>(dim));

  size_t i{};

  for_each(str_arr, str_arr + dim, [&](const string& str) {
    string line{trim(str)};
    line.erase(begin(line));
    line.erase(--end(line));

    const vector<string> row_values_str{split(line, ",", dim)};

    if (dim != row_values_str.size()) {
      ostringstream oss{};
      oss << "Row " << (i + 1) << " of matrix does not contain " << dim
          << " entries!";
      throw invalid_argument(oss.str());
    }

    for (size_t j{}; j < dim; j++)
      matrix[i][j] = stoi(row_values_str[j]);
    i++;
  });

  return matrix;
}

void find_missing_matrix_connections(vector<vector<int>> matrix,
                                     unordered_set<size_t> connections,
                                     set<size_t>& missing_connections) {
  const size_t dim{matrix.size()};

START:
  for (size_t i{}; i < dim; i++) {
    for (size_t j{}; j < dim; j++) {
      if (i == j || !matrix[i][j])
        continue;

      for (size_t k{}; k < dim; k++) {
        if (j == k || i == k || !matrix[j][k])
          continue;

        const size_t translated_index{i * dim + k};

        if (!connections.count(translated_index)) {
          connections.insert(translated_index);
          missing_connections.insert(translated_index);
          matrix[i][k] = 1;
          goto START;
        }
      }
    }
  }
}

string TransitivityRelations(string* str_arr, const size_t str_arr_size) {
  vector<vector<int>> matrix{parse_matrix_values(str_arr, str_arr_size)};

  const size_t dim{matrix.size()};

  unordered_set<size_t> connections{};

  for (size_t i{}; i < dim; i++) {
    for (size_t j{}; j < dim; j++) {
      if (i == j || !matrix[i][j])
        continue;

      connections.insert(i * dim + j);
    }
  }

  set<size_t> missing_connections{};

  find_missing_matrix_connections(move(matrix), move(connections),
                                  missing_connections);

  if (missing_connections.empty())
    return "transitive";

  ostringstream oss{};

  for (const size_t index_pair : missing_connections)
    oss << '(' << index_pair / dim << ',' << index_pair % dim << ')' << '-';

  string result{oss.str()};
  result.erase(--end(result));
  return result;
}

int main() {
  // string A[] = gets(stdin);
  // cout << TransitivityRelations(A, sizeof(A) / sizeof(*A));
  string A[] = {"(1,1,1)", "(1,0,0)", "(0,1,0)"};
  cout << TransitivityRelations(A, sizeof(A) / sizeof(*A))
       << '\n';  // expected output: "(1,2)-(2,0)"
  string B[] = {"(1,1,1)", "(0,1,1)", "(0,1,1)"};
  cout << TransitivityRelations(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "transitive"
  string C[] = {"(0,1,0,0)", "(0,0,1,0)", "(0,0,1,1)", "(0,0,0,1)"};
  cout << TransitivityRelations(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "(0,2)-(0,3)-(1,3)"

  return 0;
}
