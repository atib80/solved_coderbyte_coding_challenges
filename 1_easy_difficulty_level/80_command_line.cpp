/*
Coderbyte coding challenge:

Using the C++ language, have the function CommandLine(str) take the str
parameter being passed which represents the parameters given to a command in an
old PDP system. The parameters are alphanumeric tokens (without spaces) followed
by an equal sign and by their corresponding value. Multiple parameters/value
pairs can be placed on the command line with a single space between each pair.
Parameter tokens and values cannot contain equal signs but values can contain
spaces. The purpose of the function is to isolate the parameters and values to
return a list of parameter and value lengths. It must provide its result in the
same format and in the same order by replacing each entry (tokens and values) by
its corresponding length.

For example, if str is: "SampleNumber=3234 provider=Dr. M. Welby patient=John
Smith priority=High" then your function should return the string "12=4 8=12 7=10
8=4" because "SampleNumber" is a 12 character token with a 4 character value
("3234") followed by "provider" which is an 8 character token followed by a 12
character value ("Dr. M. Welby"), etc.

Sample test cases:

Input:  "letters=A B Z T numbers=1 2 26 20 combine=true"
Output: "7=7 7=9 7=4"

Input:  "a=3 b=4 a=23 b=a 4 23 c="
Output: "1=1 1=1 1=2 1=6 1=0"
*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
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

string CommandLine(string str) {
  str = trim(str);

  vector<pair<string, string>> cmd_args{};

  size_t prev{};
  string key{};

  while (true) {
    const size_t next{str.find('=', prev)};

    if (string::npos == next) {
      if (!key.empty() && prev) {
        const string value{str.substr(prev)};

        cmd_args.emplace_back(make_pair(key, value));
      }

      break;
    }

    if (!prev) {
      key = str.substr(0, next);

    } else {
      size_t key_si{next};

      while (str[key_si] != ' ')
        --key_si;

      size_t value_si{key_si};

      while (str[value_si] != '=')
        --value_si;

      ++value_si;

      const string value{str.substr(value_si, key_si - value_si)};

      cmd_args.emplace_back(make_pair(key, value));

      ++key_si;

      key = str.substr(key_si, next - key_si);
    }

    prev = next + 1;
  }

  ostringstream oss{};

  for (size_t i{}; i < cmd_args.size() - 1; i++) {
    oss << cmd_args[i].first.length() << '=' << cmd_args[i].second.length()
        << ' ';
  }

  oss << cmd_args.back().first.length() << '='
      << cmd_args.back().second.length();

  return oss.str();
}

int main() {
  // cout << CommandLine(move(string{gets(stdin)}));
  cout << CommandLine(
              move(string{"letters=A B Z T numbers=1 2 26 20 combine=true"}))
       << '\n';  // expected output: "7=7 7=9 7=4"
  cout << CommandLine(move(string{"SampleNumber=3234 provider=Dr. M. Welby "
                                  "patient=John Smith priority=High"}))
       << '\n';  //  expected output: "12=4 8=12 7=10 8=4"
  cout << CommandLine(move(string{"a=3 b=4 a=23 b=a 4 23 c="}))
       << '\n';  // expected output: "1=1 1=1 1=2 1=6 1=0"

  return 0;
}
