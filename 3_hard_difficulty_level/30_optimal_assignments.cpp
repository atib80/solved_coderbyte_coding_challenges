/*
Coderbyte coding challenge: Optimal Assignments

Using the C++ language, have the function OptimalAssignments(strArr) read strArr
which will represent an NxN matrix and it will be in the following format:
["(n,n,n...)","(...)",...] where the n's represent integers. This matrix
represents a machine at row i performing task at column j. The cost for this is
matrix[i][j]. Your program should determine what machine should perform what
task so as to minimize the whole cost and it should return the pairings of
machines to tasks in the following format: (i-j)(...)... Only one machine can
perform one task. For example: if strArr is ["(5,4,2)","(12,4,3)","(3,4,13)"]
then your program should return (1-3)(2-2)(3-1) because assigning the machines
to these tasks gives the least cost. The matrix will range from 2x2 to 6x6,
there will be no negative costs in the matrix, and there will always be a unique
answer.

Sample test cases:

Input:  "(1,2,1)","(4,1,5)","(5,2,1)"
Output: "(1-1)(2-2)(3-3)"

Input:  "(13,4,7,6)","(1,11,5,4)","(6,7,2,8)","(1,3,5,9)"
Output: "(1-2)(2-4)(3-3)(4-1)"
*/

#include <strsafe.h>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
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

vector<vector<size_t>> parse_matrix_cost_values(const string* str_arr,
                                                const size_t str_arr_size) {
  const size_t max_number_of_tasks{str_arr_size};

  vector<vector<size_t>> machine(max_number_of_tasks,
                                 vector<size_t>(max_number_of_tasks));

  for (size_t i{}; i < max_number_of_tasks; i++) {
    string line{trim(str_arr[i])};
    line.erase(begin(line));
    line.erase(--end(line));

    const vector<string> line_cost_values_str{split(line, ",")};

    if (max_number_of_tasks != line_cost_values_str.size()) {
      char buffer[256];
      StringCchPrintfA(
          buffer, sizeof(buffer) / sizeof(*buffer),
          "Row %lu of machine's matrix does not contain %lu entries!", i + 1,
          max_number_of_tasks);
      throw invalid_argument(buffer);
    }

    for (size_t j{}; j < max_number_of_tasks; j++)
      machine[i][j] = stoul(line_cost_values_str[j]);
  }

  return machine;
}

string OptimalAssignments(const string* str_arr, const size_t str_arr_size) {
  const size_t max_number_of_tasks{str_arr_size};

  const vector<vector<size_t>> machine{
      parse_matrix_cost_values(str_arr, str_arr_size)};

  vector<size_t> indices(max_number_of_tasks);

  for (size_t i{}; i < max_number_of_tasks; i++)
    indices[i] = i;

  size_t minimum_cost{};
  string min_cost_indices{};
  char buffer[256];
  const size_t buffer_size{sizeof(buffer) / sizeof(*buffer)};

  size_t offset{};
  for (size_t i{}, j{}; i < max_number_of_tasks; i++, j++) {
    minimum_cost += machine[i][indices[j]];
    StringCchPrintfA(buffer + offset, buffer_size - offset, "(%lu-%lu)",
                     (i + 1), (indices[j] + 1));
    if (S_OK != StringCchLength(buffer, STRSAFE_MAX_CCH, &offset))
      throw runtime_error{
          "buffer's length exceeds maximum allowed specified by "
          "STRSAFE_MAX_CCH!"};
  }

  min_cost_indices = buffer;

  while (next_permutation(begin(indices), end(indices))) {
    size_t current_cost{};

    for (size_t i{}, j{}; i < max_number_of_tasks; i++, j++) {
      current_cost += machine[i][indices[j]];
      if (current_cost >= minimum_cost)
        break;
    }

    if (current_cost < minimum_cost) {
      minimum_cost = current_cost;
      offset = 0;
      for (size_t i{}, j{}; i < max_number_of_tasks; i++, j++) {
        StringCchPrintfA(buffer + offset, buffer_size - offset, "(%lu-%lu)",
                         (i + 1), (indices[j] + 1));
        if (S_OK != StringCchLength(buffer, STRSAFE_MAX_CCH, &offset))
          throw runtime_error{
              "buffer's length exceeds maximum allowed specified by "
              "STRSAFE_MAX_CCH!"};
      }
      min_cost_indices = buffer;
    }
  }

  return min_cost_indices;
}

int main() {
  // const string A[] = gets(stdin);
  // cout << OptimalAssignments(A, sizeof(A)/sizeof(*A));
  const string B[] = {"(5,4,2)", "(12,4,3)", "(3,4,13)"};
  cout << OptimalAssignments(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: (1-3)(2-2)(3-1)
  const string C[] = {"(1,2,1)", "(4,1,5)", "(5,2,1)"};
  cout << OptimalAssignments(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "(1-1)(2-2)(3-3)"
  const string D[] = {"(13,4,7,6)", "(1,11,5,4)", "(6,7,2,8)", "(1,3,5,9)"};
  cout << OptimalAssignments(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "(1-2)(2-4)(3-3)(4-1)"

  return 0;
}
