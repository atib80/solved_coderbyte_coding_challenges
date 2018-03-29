#include <cassert>
#include <iostream>

using namespace std;

template <typename T>
struct node {
  T data;
  node<T>* next;

  node(const T& d, node<T>* const n = nullptr) : data{d}, next{n} {}
  ~node() {
    if (next) {
      cout << "Deleting next node (" << next->data
           << ") in singly-linked list...\n";
      delete next;
    }
  }
};

void append_second_list(node<int>** list_front, node<int>** list_back) {
  assert(list_front && list_back);

  if (!*list_front) {
    *list_front = *list_back;
    *list_back = nullptr;
    return;
  }

  node<int>* head{*list_front};

  while (head->next)
    head = head->next;

  head->next = *list_back;
  *list_back = nullptr;
}

void split_front_back(node<int>* src_list,
                      node<int>** list_front,
                      node<int>** list_back) {
  assert(list_front && list_back);

  if (!src_list) {
    *list_front = nullptr;
    list_back = nullptr;
    return;
  }

  if (!src_list->next) {
    *list_front = src_list;
    (*list_front)->next = nullptr;
    *list_back = nullptr;
    return;
  }

  node<int>* slow_step{src_list};
  node<int>* fast_step{src_list};

  while (fast_step) {
    fast_step = fast_step->next;
    if (!fast_step)
      break;

    fast_step = fast_step->next;

    if (fast_step)
      slow_step = slow_step->next;
  }

  *list_front = src_list;
  *list_back = slow_step->next;
  slow_step->next = nullptr;
}

int main() {
  node<int>* list_front_head = new node<int>{1};
  node<int>* list_front_node1 = new node<int>{2};
  node<int>* list_front_node2 = new node<int>{3};
  node<int>* list_front_node3 = new node<int>{4};
  node<int>* list_front_node4 = new node<int>{5};
  node<int>* list_front_node5 = new node<int>{6};

  list_front_head->next = list_front_node1;
  list_front_node1->next = list_front_node2;
  list_front_node2->next = list_front_node3;
  list_front_node3->next = list_front_node4;
  list_front_node4->next = list_front_node5;

  node<int>* list_back_head = new node<int>{7};
  node<int>* list_back_node1 = new node<int>{8};
  node<int>* list_back_node2 = new node<int>{9};
  node<int>* list_back_node3 = new node<int>{10};
  node<int>* list_back_node4 = new node<int>{11};
  node<int>* list_back_node5 = new node<int>{12};

  list_back_head->next = list_back_node1;
  list_back_node1->next = list_back_node2;
  list_back_node2->next = list_back_node3;
  list_back_node3->next = list_back_node4;
  list_back_node4->next = list_back_node5;

  append_second_list(&list_front_head, &list_back_head);

  for (auto current_node = list_front_head; current_node;
       current_node = current_node->next) {
    cout << current_node->data << ' ';
  }

  cout << "\n\nDeleting head node (" << list_front_head->data
       << ") of singly-linked list...\n";
  delete list_front_head;

  return 0;
}
