/*
Coderbyte coding challenge: LRU Cache v3

LRU Cache v3 is my third alternative solution to Coderbyte's LRU cache
coding challenge which makes use of a list<char> container for storing
all of LRU cache's contents in a sequential order based on the order of arrival
of its elements and an unordered_map<char, list<char>::iterator>
associative container for providing quick lookup of LRU cache's previously
stored elements.

Using the C++ language, have the function LRUCache(strArr) take the array of
characters stored in strArr, which will contain characters ranging from A to Z
in some arbitrary order, and determine what elements still remain in a virtual
cache that can hold up to 5 elements with an LRU cache algorithm implemented.
For example: if strArr is ["A", "B", "C", "D", "A", "E", "D", "Z"], then the
following steps are taken:

(1) A does not exist in the cache, so access it and store it in the cache.
(2) B does not exist in the cache, so access it and store it in the cache as
well. So far the cache contains: ["A", "B"]. (3) Same goes for C, so the cache
is now: ["A", "B", "C"]. (4) Same goes for D, so the cache is now: ["A", "B",
"C", "D"]. (5) Now A is accessed again, but it exists in the cache already so it
is brought to the front: ["B", "C", "D", "A"]. (6) E does not exist in the
cache, so access it and store it in the cache: ["B", "C", "D", "A", "E"]. (7) D
is accessed again so it is brought to the front: ["B", "C", "A", "E", "D"]. (8)
Z does not exist in the cache so add it to the front and remove the least
recently used element: ["C", "A", "E", "D", "Z"].

Now the caching steps have been completed and your program should return the
order of the cache with the elements joined into a string, separated by a
hyphen. Therefore, for the example above your program should return C-A-E-D-Z.

Sample test cases:

Input:  "A", "B", "A", "C", "A", "B"
Output: "C-A-B"

Input:  "A", "B", "C", "D", "E", "D", "Q", "Z", "C"
Output: "E-D-Q-Z-C"
*/

#include <algorithm>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

constexpr size_t max_capacity{5};

template <typename _Container>
string join(const _Container& items, const string& needle) {
  ostringstream oss{};

  auto start = begin(items);

  const auto last = end(items);

  while (start != last) {
    oss << *start << needle;

    ++start;
  }

  string result{oss.str()};

  const size_t needle_len{needle.length()};

  result.erase(result.length() - needle_len, needle_len);

  return result;
}

string get_lru_cache_contents(const list<char>& lru_cache) {
  return join(lru_cache, "-");
}

list<char> build_lru_cache_contents(const string* str_arr,
                                    const size_t str_arr_size) {
  list<char> lru_cache{};
  unordered_map<char, list<char>::iterator> lru_cache_index{};

  for (const string* current_item{str_arr};
       current_item != str_arr + str_arr_size; ++current_item) {
    const char cache_item{(*current_item)[0]};

    if (lru_cache_index.find(cache_item) != end(lru_cache_index)) {
      lru_cache.erase(lru_cache_index[cache_item]);
      const auto new_cache_item_iter_pos =
          lru_cache.insert(end(lru_cache), cache_item);
      lru_cache_index[cache_item] = new_cache_item_iter_pos;

    } else if (lru_cache.size() == max_capacity) {
      lru_cache_index.erase(lru_cache.front());
      lru_cache.pop_front();
      const auto new_cache_item_iter_pos =
          lru_cache.insert(end(lru_cache), cache_item);
      lru_cache_index[cache_item] = new_cache_item_iter_pos;

    } else {
      const auto new_cache_item_iter_pos =
          lru_cache.insert(end(lru_cache), cache_item);
      lru_cache_index[cache_item] = new_cache_item_iter_pos;
    }
  }

  return lru_cache;
}

string LRUCache(const string* str_arr, const size_t str_arr_size) {
  const list<char> lru_cache{build_lru_cache_contents(str_arr, str_arr_size)};

  return get_lru_cache_contents(lru_cache);
}

int main() {
  // const string A[] = gets(stdin);
  // cout << LRUCache(A, sizeof(A)/sizeof(*A));
  const string B[] = {"A", "B", "C", "D", "A", "E", "D", "Z"};
  cout << LRUCache(B, sizeof(B) / sizeof(*B))
       << '\n';  // expected output: "C-A-E-D-Z"
  const string C[] = {"A", "B", "A", "C", "A", "B"};
  cout << LRUCache(C, sizeof(C) / sizeof(*C))
       << '\n';  // expected output: "C-A-B"
  const string D[] = {"A", "B", "C", "D", "E", "D", "Q", "Z", "C"};
  cout << LRUCache(D, sizeof(D) / sizeof(*D))
       << '\n';  // expected output: "E-D-Q-Z-C"

  return 0;
}
