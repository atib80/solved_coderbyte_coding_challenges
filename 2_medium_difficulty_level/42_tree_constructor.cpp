/*
Coderbyte coding challenge: Tree Constructor

Using the C++ language, have the function TreeConstructor(strArr) take the array of strings stored in strArr, 
which will contain pairs of integers in the following format: (i1,i2), where i1 represents a child node in a tree 
and the second integer i2 signifies that it is the parent of i1. 
For example: if strArr is ["(1,2)", "(2,4)", "(7,2)"], then this forms the following tree:    

     [4]
   [2]
 [1][7]

which you can see forms a proper binary tree. 
Your program should, in this case, return the string true because a valid binary tree can be formed. 
If a proper binary tree cannot be formed with the integer pairs, then return the string false. 
All of the integers within the tree will be unique, which means there can only be one node in the tree with the given integer value.

Sample test cases:

Input:  "(1,2)", "(2,4)", "(5,7)", "(7,2)", "(9,5)"
Output: "true"

Input:  "(1,2)", "(3,2)", "(2,12)", "(5,2)"
Output: "false"
*/

#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

string trim(const string& str)
{
  size_t begin_str{};
  size_t end_str{str.size() - 1};

  if (0u == str.length()) return string{};

  for (; begin_str <= end_str; ++begin_str)
  {
    if (!isspace(str[begin_str])) break;
  }

  if (begin_str > end_str) return string{};

  for (; end_str > begin_str; --end_str)
  {
    if (!isspace(str[end_str])) break;
  }

  return str.substr(begin_str, end_str - begin_str + 1);
}

using namespace std;

string TreeConstructor(string* str_arr, const size_t str_arr_size) {

  vector<pair<int, int>> child_parent_value_pairs(str_arr_size);

  for (size_t i{}; i != str_arr_size; i++) {
  	str_arr[i] = trim(str_arr[i]);
  	str_arr[i].erase(begin(str_arr[i]));
  	str_arr[i].erase(--end(str_arr[i]));
  	const size_t comma_pos{str_arr[i].find(',')};
  	if (string::npos == comma_pos) return string{"Not possible!"};
  	const string child_number_str { str_arr[i].substr(0, comma_pos) };
  	const string parent_number_str { str_arr[i].substr(comma_pos + 1) };
  	const int child_number { stoi(child_number_str) };
  	const int parent_number { stoi(parent_number_str) };
  	child_parent_value_pairs[i] = make_pair(child_number, parent_number);
  }

  if ((1u == child_parent_value_pairs.size()) && (child_parent_value_pairs[0].first < child_parent_value_pairs[0].second)) return string{"true"};

  map<int, size_t> child_value_count{}, parent_value_count{};

  map<int, vector<int>> parent_children_values{};

  sort(begin(child_parent_value_pairs), end(child_parent_value_pairs), [](const pair<int, int>& lp, const pair<int, int>& rp) {

  	return (lp.second < rp.second);
  });

 
  for (const auto& cp : child_parent_value_pairs) {

  	if (child_value_count.find(cp.first) == end(child_value_count)) child_value_count.insert(make_pair(cp.first, 1u));
  	else return string{"false"};

  	if (parent_value_count.find(cp.second) == end(parent_value_count)) parent_value_count.insert(make_pair(cp.second, 1u));
  	else {
  		
  		parent_value_count[cp.second]++;
  		if (parent_value_count[cp.second] > 2u) return string{"false"};
  	}

  	if (parent_children_values.find(cp.second) == end(parent_children_values)) {
  		parent_children_values.insert(make_pair(cp.second, vector<int>{}));
  		parent_children_values[cp.second].emplace_back(cp.first);
  	}
  	else {
  		parent_children_values[cp.second].emplace_back(cp.first);
  	}
  
  }

  for (const auto& cp_values : parent_children_values) {

  	if (cp_values.second.size() > 2u) return string{"false"};

  	if (2u == cp_values.second.size()) {

  		if ((cp_values.second[0] < cp_values.first) && (cp_values.second[1] < cp_values.first)) return string{"false"};

  		if ((cp_values.second[0] > cp_values.first) && (cp_values.second[1] > cp_values.first)) return string{"false"};

  	}

  }

  return string{"true"}; 
            
}

int main() { 
   
  // string A[] = gets(stdin);
  // cout << TreeConstructor(A, sizeof(A)/sizeof(*A));
  string B[] = {"(1,2)", "(2,4)", "(7,2)"};
  cout << TreeConstructor(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: "true"
  string C[] = {"(1,2)", "(2,4)", "(5,7)", "(7,2)", "(9,5)"};
  cout << TreeConstructor(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: "true"
  string D[] = {"(1,2)", "(3,2)", "(2,12)", "(5,2)"};
  cout << TreeConstructor(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: "false"
  string E[] = {"(10,20)"};
  cout << TreeConstructor(E, sizeof(E)/sizeof(*E)) << '\n'; // expected output: "true"
  
  return 0;    
}
