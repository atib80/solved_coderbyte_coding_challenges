/*
Coderbyte coding challenge: Gas Station

Using the C++ language, have the function GasStation(strArr) take strArr which
will be an an array consisting of the following elements: N which will be the
number of gas stations in a circular route and each subsequent element will be
the string g:c where g is the amount of gas in gallons at that gas station and c
will be the amount of gallons of gas needed to get to the following gas station.
For example strArr may be: ["4","3:1","2:2","1:2","0:1"].
Your goal is to return the index of the starting gas station that will allow you
to travel around the whole route once, otherwise return the string impossible.
For the example above, there are 4 gas stations, and your program should return
the string 1 because starting at station 1 you receive 3 gallons of gas and
spend 1 getting to the next station. Then you have 2 gallons + 2 more at the
next station and you spend 2 so you have 2 gallons when you get to the 3rd
station. You then have 3 but you spend 2 getting to the final station, and at
the final station you receive 0 gallons and you spend your final gallon getting
to your starting point. Starting at any other gas station would make getting
around the route impossible, so the answer is 1. If there are multiple gas
stations that are possible to start at, return the smallest index (of the gas
station). N will be >= 2.




Sample test cases:

Input:  "4","1:1","2:2","1:2","0:1"
Output: "impossible"

Input:  "4","0:1","2:2","1:2","3:1"
Output: "4"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
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

string GasStation(string* str_arr, const size_t str_arr_size) {
  const size_t N{stoul(trim(*str_arr))};

  vector<pair<int, int>> gas_stations{};

  for (size_t i{1}; i < str_arr_size; i++) {
    str_arr[i] = trim(str_arr[i]);

    const size_t sep_pos{str_arr[i].find(':')};

    gas_stations.emplace_back(stoi(str_arr[i].substr(0, sep_pos)),
                              stoi(str_arr[i].substr(sep_pos + 1)));
  }

  for (size_t i{}; i < N; i++) {
    size_t ci{i};
    int gallons{};

    while (true) {
      gallons += gas_stations[ci].first;

      if (gas_stations[ci].second > gallons)
        break;

      gallons -= gas_stations[ci].second;

      ci = ci + 1 == N ? 0 : ci + 1;

      if (ci == i)
        return to_string(i + 1);
    }
  }

  return "impossible";
}

int main() {
  // string A[] = gets(stdin);
  // cout << GasStation(A, sizeof(A)/sizeof(*A));
  string B[] = {"4", "3:1", "2:2", "1:2", "0:1"};
  cout << GasStation(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "1"
  string C[] = {"4", "1:1", "2:2", "1:2", "0:1"};
  cout << GasStation(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "impossible"
  string D[] = {"4", "0:1", "2:2", "1:2", "3:1"};
  cout << GasStation(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "4"

  return 0;
}
