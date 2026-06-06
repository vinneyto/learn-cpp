#pragma once

#include <cstddef>
class LinkedList;

struct TLinkedElement {
  friend class LinkedList;

  TLinkedElement();

  TLinkedElement(int value);

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

  LinkedList(const LinkedList &other);

  LinkedList(LinkedList &&other) noexcept;

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

  TLinkedElement *cbegin() const;
  TLinkedElement *cend() const;

  TLinkedElement *rbegin();
  TLinkedElement *rend();

  TLinkedElement *crbegin() const;
  TLinkedElement *crend() const;

  void clear();

  void swap(LinkedList &other);

  bool empty() const;

  std::size_t size() const;

private:
  TLinkedElement *head_ = nullptr;
  TLinkedElement *tail_ = nullptr;

  std::size_t size_ = 0;
};
