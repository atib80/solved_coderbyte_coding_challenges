/*
Coderbyte coding challenge: HTML Elements

Using the C++ language, have the function HTMLElements(str) read the str
parameter being passed which will be a string of HTML DOM elements and plain
text. The elements that will be used are: b, i, em, div, p. For example: if str
is "<div><b><p>hello world</p></b></div>" then this string of DOM elements is
nested correctly so your program should return the string true. If a string is
not nested correctly, return the first element encountered where, if changed
into a different element, would result in a properly formatted string. If the
string is not formatted properly, then it will only be one element that needs to
be changed.

For example: if str is "<div><i>hello</i>world</b>" then your program should
return the string div because if the first <div> element were changed into a
<b>, the string would be properly formatted.

Sample test cases:

Input:  "<div><div><b></b></div></p>"
Output: "div"

Input:  "<div>abc</div><p><em><i>test test test</b></em></p>"
Output: "i"
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <stack>
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

string check_if_html_document_is_correctly_structured(const string& html_text) {
  const size_t html_text_len{html_text.length()};

  stack<string> start_tag_names{};

  size_t first_start_tag_pos{};

  size_t tag_end_pos;

  while (first_start_tag_pos < html_text_len &&
         (first_start_tag_pos = html_text.find('<', first_start_tag_pos)) !=
             string::npos) {
    if (html_text[first_start_tag_pos + 1] != '/') {
      tag_end_pos = html_text.find('>', first_start_tag_pos + 1);

      if (string::npos == tag_end_pos)
        return "false";

      const string start_tag_name{html_text.substr(
          first_start_tag_pos + 1, tag_end_pos - (first_start_tag_pos + 1))};

      start_tag_names.emplace(start_tag_name);

    } else {
      tag_end_pos = html_text.find('>', first_start_tag_pos + 2);

      if (tag_end_pos == string::npos)
        return "false";

      const string end_tag_name{html_text.substr(
          first_start_tag_pos + 2, tag_end_pos - (first_start_tag_pos + 2))};

      if (!start_tag_names.empty()) {
        if (end_tag_name != start_tag_names.top())
          return start_tag_names.top();

        start_tag_names.pop();

      } else
        return "false";
    }

    first_start_tag_pos = tag_end_pos + 1;
  }

  if (!start_tag_names.empty())
    return start_tag_names.top();

  return "true";
}

string HTMLElements(string str) {
  return check_if_html_document_is_correctly_structured(str);
}

int main() {
  // cout << HTMLElements(move(string{gets(stdin)}));
  cout << HTMLElements(move(string{"<div><b><p>hello world</p></b></div>"}))
       << '\n';  // expected output: "true"
  cout << HTMLElements(move(string{"<div><i>hello</i>world</b>"}))
       << '\n';  // expected output: "div"
  cout << HTMLElements(move(string{"<div><div><b></b></div></p>"}))
       << '\n';  // expected output: "div"
  cout << HTMLElements(move(
              string{"<div>abc</div><p><em><i>test test test</b></em></p>"}))
       << '\n';  // expected output: "i"
  cout << HTMLElements(move(string{"<div>"}))
       << '\n';  // expected output: "div"

  return 0;
}
