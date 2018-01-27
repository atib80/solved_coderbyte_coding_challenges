/*
Coderbyte coding challenge: LCS

Using the C++ language, have the function LCS(strArr) take the strArr parameter
being passed which will be an array of two strings containing only the
characters {a,b,c} and have your program return the length of the longest common
subsequence common to both strings. A common subsequence for two strings does
not require each character to occupy consecutive positions within the original
strings. For example: if strArr is ["abcabb","bacb"] then your program should
return 3 because one longest common subsequence for these two strings is "bab"
and there are also other 3-length subsequences such as "acb" and "bcb" but 3 is
the longest common subsequence for these two strings.

Sample test cases:

Input:  "abc","cb"
Output: 1

Input:  "bcacb","aacabb"
Output: 3
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <locale>
#include <string>
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

size_t find_longest_common_sequence(const vector<string> &strings)
{

    string left{strings[0]};
    string right{strings[1]};
    size_t longest{};

    for (size_t k{}; k < left.length(); k++)
    {
        size_t count{};

        for (int i{}; i < left.length(); i++)
        {
            for (int j{}; j < right.length(); j++)
            {
                if (left[i] == right[j])
                {
                    count++;
                    left = left.substr(i + 1);
                    right = right.substr(j + 1);
                    i = -1;
                    break;
                }
            }
        }

        if (count > longest)
            longest = count;

        left = strings[0].substr(k);
        right = strings[1];
    }

    return longest;
}

string LCS(string *str_arr, const size_t str_arr_size)
{

    for (size_t i{}; i < str_arr_size; i++)
        str_arr[i] = trim(str_arr[i]);

    vector<string> strings(str_arr, str_arr + str_arr_size);

    const size_t max_lcs_len1{find_longest_common_sequence(strings)};

    swap(strings[0], strings[1]);

    const size_t max_lcs_len2{find_longest_common_sequence(strings)};

    return (max_lcs_len1 > max_lcs_len2 ? to_string(max_lcs_len1)
                                        : to_string(max_lcs_len2));
}

int main()
{

    // string A[] = gets(stdin);
    // cout << LCS(A, sizeof(A)/sizeof(*A));
    string B[] = {"abcabb", "bacb"};
    cout << LCS(B, sizeof(B) / sizeof(*B)) << '\n'; // expected output: "3"
    string C[] = {"abc", "cb"};
    cout << LCS(C, sizeof(C) / sizeof(*C)) << '\n'; // expected output: "1"
    string D[] = {"bcacb", "aacabb"};
    cout << LCS(D, sizeof(D) / sizeof(*D)) << '\n'; // expected output: "3"

    return 0;
}