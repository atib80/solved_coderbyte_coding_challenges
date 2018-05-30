/*
Coderbyte coding challenge: Bipartite Matching

Using the C++ language, have the function BipartiteMatching(strArr) read strArr
which will be an array of hyphenated letters representing paths from the first
node to the second node. For example: ["a->d", "a->e", "b->f", "c->e"] means
that there is a path from node a to d, a to e, b to f, and so on. The graph will
be bipartite meaning that it is possible to separate the nodes into two disjoint
sets such that every edge only connects a node from the lefthand side to a node
on the righthand side. Your program should determine the maximum cardinality
matching of the bipartite graph, which means finding the largest possible number
of non-adjacent edges that are matching. So for the example above, your program
should return 3 because it is possible to connect every single node on the left
to a node on the right.

The input will only contain lowercase alphabetic characters with a -> between
them signifying an edge between them going from the left node to the right node.
The input will contain at least 1 edge connecting 2 nodes.

Sample test cases:

Input:  "a->w", "a->x", "b->x", "b->y", "c->x", "c->z", "d->w"
Output: 4

Input:  "a->b", "c->b", "c->d", "e->b"
Output: 2
*/

#include <cctype>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

void find_max_cardinality(const vector<string>& edges,
                          const size_t pos,
                          unordered_set<char>& lhs_visited_nodes,
                          unordered_set<char>& rhs_visited_nodes,
                          size_t& max_cardinality,
                          const size_t cardinality = 0) {
  if (pos == edges.size()) {
    if (cardinality > max_cardinality)
      max_cardinality = cardinality;
    return;
  }

  for (size_t j{}; j < edges.size(); j++) {
    if (!lhs_visited_nodes.count(edges[j][0]) &&
        !rhs_visited_nodes.count(edges[j][3])) {
      lhs_visited_nodes.insert(edges[j][0]);
      rhs_visited_nodes.insert(edges[j][3]);
      find_max_cardinality(edges, j + 1, lhs_visited_nodes, rhs_visited_nodes,
                           max_cardinality, cardinality + 1);
      lhs_visited_nodes.erase(edges[j][0]);
      rhs_visited_nodes.erase(edges[j][3]);
    }
  }
}

string BipartiteMatching(const string* str_arr, const size_t str_arr_size) {
  const vector<string> edges(str_arr, str_arr + str_arr_size);
  unordered_set<char> lhs_visited_nodes{};
  unordered_set<char> rhs_visited_nodes{};
  size_t max_cardinality{1};

  find_max_cardinality(edges, 0, lhs_visited_nodes, rhs_visited_nodes,
                       max_cardinality);
  return to_string(max_cardinality);
}

int main() {
  // const string A[] = gets(stdin);
  // cout << BipartiteMatching(A, sizeof(A) / sizeof(*A));
  const string B[] = {"a->d", "a->e", "b->f", "c->e"};
  cout << BipartiteMatching(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: 3
  const string C[] = {"a->w", "a->x", "b->x", "b->y", "c->x", "c->z", "d->w"};
  cout << BipartiteMatching(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: 4
  const string D[] = {"a->b", "c->b", "c->d", "e->b"};
  cout << BipartiteMatching(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: 2

  return 0;
}
