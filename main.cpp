#include <cstddef>
#include <iostream>

/*
Task:
Implement linked list
https://en.cppreference.com/cpp/container/list
https://en.wikipedia.org/wiki/Linked_list

For memory allocation de allocation you should use new and delete from c++
No malloc or any other allocators

Limitation:
You shouldn't use any stl container like std::list and other
You shouldn't use smart pointer
You shoundn't use templates
You shoundn't use AI for code generation or bug fixing
You shoundn't use overthinking, keep as simple as possible

Bonus:
Don't have memory leaks
*/

class LinkedList;

struct TLinkedElement {
  friend class LinkedList;

  int value;

  TLinkedElement *prev();
  TLinkedElement *next();

private:
  TLinkedElement *prev_ = nullptr;
  TLinkedElement *next_ = nullptr;
};

class LinkedList {
public:
  LinkedList();

  /*resources should be free after list is destroyed*/
  ~LinkedList();

  /*
  Insert element to tail of list
  */
  void push_back(int a);

  /*
  Remove that element from list
  if user access TLinkedElement after destroy that UB
  */
  void erase(TLinkedElement *elem);

  /*
  return first element from linked list
  should be O(1)
  if user access TLinkedElement after destroy LinkedList that UB
  */
  TLinkedElement *begin();

  /*
  return special element from linked list that
  indicate end of list
  if user access state of end, that UB
  */
  TLinkedElement *end();

  bool empty();

private:
  TLinkedElement *head_ = nullptr;
  TLinkedElement *tail_ = nullptr;
};

TLinkedElement *TLinkedElement::prev() { return prev_; }

TLinkedElement *TLinkedElement::next() { return next_; }

LinkedList::LinkedList() {}

LinkedList::~LinkedList() {
  auto tail = tail_;

  while (tail) {
    // taking prev
    auto prev = tail->prev_;
    // delete itself
    tail->prev_ = nullptr;
    tail->next_ = nullptr;
    delete tail;
    // move closer to head
    tail = prev;
  }

  head_ = nullptr;
  tail_ = nullptr;
}

void LinkedList::push_back(int a) {
  auto elem = new TLinkedElement();
  elem->value = a;

  if (empty()) {
    head_ = elem;
    tail_ = elem;
  } else {
    elem->prev_ = tail_;
    tail_->next_ = elem;
    tail_ = elem;
  }
}

void LinkedList::erase(TLinkedElement *elem) {
  auto prev = elem->prev_;
  auto next = elem->next_;

  // first and only one element
  if (!next && !prev && elem == head_) {
    delete elem;
    head_ = nullptr;
    tail_ = nullptr;
    return;
  }

  // may be last element
  if (prev) {
    prev->next_ = next;
    if (elem == tail_) {
      tail_ = prev;
    }
  }

  // may be first element
  if (next) {
    next->prev_ = prev;
    if (elem == head_) {
      head_ = next;
    }
  }

  elem->prev_ = nullptr;
  elem->next_ = nullptr;
  delete elem;
}

TLinkedElement *LinkedList::begin() { return head_; }

TLinkedElement *LinkedList::end() { return nullptr; }

bool LinkedList::empty() { return !head_ && !tail_; }

/// example usage
int main() {
  LinkedList list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  // output: 1, 2, 3
  for (TLinkedElement *it = list.begin(); it != list.end(); it = it->next()) {
    std::cout << it->value << ' ';
  }
  std::cout << std::endl;
  list.erase(list.begin());
  // output: 2, 3
  for (TLinkedElement *it = list.begin(); it != list.end(); it = it->next()) {
    std::cout << it->value << ' ';
  }
  return 0;
}
