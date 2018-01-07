/*
Coderbyte coding challenge: Binary Tree LCA

Using the C++ language, have the function BinaryTreeLCA(strArr) take the array of strings stored in strArr, which will contain 3 elements: 
the first element will be a binary tree with all unique values in a format similar to how a binary heap is implemented with NULL nodes at any level 
represented with a #, the second and third elements will be two different values, and your goal is to find the lowest common ancestor of these two values. 
For example: if strArr is ["[12, 5, 9, 6, 2, 0, 8, #, #, 7, 4, #, #, #, #]", "6", "4"] then this tree looks like the following:

     [12]
  [5]    [9] 
[6][2]  [0][8]
  [7][4]


For the input above, your program should return 5 because that is the value of the node that is the LCA of the two nodes with values 6 and 4.
You can assume the two nodes you are searching for in the tree will exist somewhere in the tree.

Sample test cases:

Input:  "[5, 2, 6, 1, #, 8, #]", "2", "6"
Output: 5

Input:  "[5, 2, 6, 1, #, 8, 12, #, #, #, #, #, #, 3, #]", "3", "12"
Output: 12
*/

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

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

vector<string> split(const string& source, const char* needle, size_t const max_count = string::npos)
{
  vector<string> parts{}; 

  string needle_st{needle};

  const size_t source_len{source.length()};

  const size_t needle_len{needle_st.size()};

  if ((0u == source_len) || (0u == needle_len)) return parts;

  size_t number_of_parts{}, prev{};

  while (true)
  {
    const size_t current = source.find(needle_st, prev);

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

string BinaryTreeLCA(string* str_arr, const size_t str_arr_size) {

  if (str_arr_size < 3u) return "-1";

  for (size_t i{}; i != str_arr_size; i++) str_arr[i] = trim(str_arr[i]);

  str_arr[0].erase(begin(str_arr[0]));

  str_arr[0].erase(--end(str_arr[0]));

  vector<string> numbers_str { split(str_arr[0], ", ") };

  for (auto& number_str : numbers_str) number_str = trim(number_str);

  const string number1_str { str_arr[1] };
  const string number2_str { str_arr[2] };

  size_t number1_index{string::npos}, number2_index{string::npos};

  for (size_t i{}; i < numbers_str.size(); i++) {

    if ("#" == numbers_str[i]) continue;

    if ((string::npos != number1_index) && (string::npos != number2_index)) break;
      
      if ((number1_str == numbers_str[i]) && (string::npos == number1_index)) number1_index = i;

      else if ((number2_str == numbers_str[i]) && (string::npos == number2_index)) number2_index = i;      
  }

  if (number1_index < number2_index) {

    if ((number2_index - number1_index) == 1) return numbers_str[(number2_index - 1)/2];

      number2_index = (number2_index - 1) / 2;

      while (number1_index != number2_index) {

        if (number2_index > number1_index) {

          number2_index = (number2_index - 1) / 2;

        }

        if (number1_index > number2_index) {

          number1_index = (number1_index - 1) / 2;
          
        }

      }


  } else {

    if ((number1_index - number2_index) == 1) return numbers_str[(number1_index - 1)/2];

    number1_index = (number1_index - 1) / 2;

      while (number1_index != number2_index) {

        if (number1_index > number2_index) {

          number1_index = (number1_index - 1) / 2;
          
        }

        if (number2_index > number1_index) {

          number2_index = (number2_index - 1) / 2;

        }        

      }
  }  

  return numbers_str[number1_index];            
}

int main() { 
   
  // string A[] = gets(stdin);
  // cout << BinaryTreeLCA(A, sizeof(A)/sizeof(*A));
  string B[] = {"[12, 5, 9, 6, 2, 0, 8, #, #, 7, 4, #, #, #, #]", "6", "4"};
  cout << BinaryTreeLCA(B, sizeof(B)/sizeof(*B)) << '\n'; // expected output: "5"
  string C[] = {"[5, 2, 6, 1, #, 8, #]", "2", "6"};       
  cout << BinaryTreeLCA(C, sizeof(C)/sizeof(*C)) << '\n'; // expected output: "5"
  string D[] = {"[5, 2, 6, 1, #, 8, 12, #, #, #, #, #, #, 3, #]", "3", "12"};
  cout << BinaryTreeLCA(D, sizeof(D)/sizeof(*D)) << '\n'; // expected output: "12"

  return 0;    
}
