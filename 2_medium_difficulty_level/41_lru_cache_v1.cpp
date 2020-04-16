/*
Coderbyte coding challenge: LRU Cache

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
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

struct Node {
  Node(Node* p, Node* n, const string& v) : prev{p}, next{n}, value{v} {}
  Node(const string& v) : value{v} {}

  Node* prev{};
  Node* next{};
  const string value;
};

class Cache {
 public:
  Cache(const size_t capacity) : capacity_{capacity} {}
  virtual void update_cache(const string& value) = 0;

 protected:
  unordered_map<string, Node*> cache_{};
  const size_t capacity_;
  Node* tail{};
  Node* head{};
};

class LRU_Cache : public Cache {
 public:
  explicit LRU_Cache(const size_t capacity) : Cache(capacity) {}

  ~LRU_Cache() {
    auto current = head;

    while (current) {
      auto const next = current->next;

      cache_.erase(current->value);

      delete current;

      current = next;
    }

    head = tail = nullptr;
  }

  void update_cache(const string& value) override {
    if (cache_.find(value) != end(cache_)) {
      Node* const n = cache_[value];

      if (head == n)
        return;

      if (tail == n) {
        if (tail->prev) {
          tail->prev->next = nullptr;
          tail = tail->prev;
        }

      } else {
        if (n->prev)
          n->prev->next = n->next;
        if (n->next)
          n->next->prev = n->prev;
      }

      n->next = head;

      head->prev = n;

      n->prev = nullptr;

      head = n;

      return;
    }

    if (!head) {
      head = new Node(value);
      tail = head;
      cache_.insert(make_pair(value, head));
      return;
    }

    if (capacity_ == cache_.size()) {
      auto const last = tail;

      if (tail->prev) {
        tail->prev->next = nullptr;
        tail = tail->prev;
      }

      cache_.erase(last->value);

      delete last;
    }

    Node* const new_node = new Node(value);
    new_node->next = head;
    head->prev = new_node;
    head = new_node;
    cache_.insert(make_pair(value, head));
  }

  string get_lru_cache_contents() const {
    ostringstream oss{};

    auto current = head;

    while (current) {
      auto const next = current->next;

      oss << current->value;

      if (next)
        oss << '-';

      current = next;
    }

    string contents{oss.str()};

    reverse(begin(contents), end(contents));

    return contents;
  }
};

string LRUCache(const string* str_arr, const size_t str_arr_size) {
  LRU_Cache lru_cache(5);

  for (size_t i{}; i < str_arr_size; i++) {
    lru_cache.update_cache(str_arr[i]);
  }

  return lru_cache.get_lru_cache_contents();
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
