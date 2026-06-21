#include <cstddef>
#include <utility>

#include "LinkedList.h"

// TLinkedElement

TLinkedElement::TLinkedElement() {}

TLinkedElement::TLinkedElement(int value) : value(value) {}

TLinkedElement *TLinkedElement::prev() { return prev_; }

TLinkedElement *TLinkedElement::next() { return next_; }

const TLinkedElement *TLinkedElement::prev() const { return prev_; }

const TLinkedElement *TLinkedElement::next() const { return next_; }

// end TLinkedElement

// LinkedList

LinkedList::LinkedList() {}

LinkedList::LinkedList(const LinkedList &other) {
  LinkedList tmp;

  for (const TLinkedElement *it = other.cbegin(); it != other.cend();
       it = it->next()) {
    tmp.push_back(it->value);
  }

  // in case error thrown before - tmp will be destored by raii
  swap(tmp);
}

LinkedList::LinkedList(LinkedList &&other) {
  swap(other); // swap eats && as first argument - is it ok?

  other.clear();
}

LinkedList::~LinkedList() { clear(); }

void LinkedList::clear() {
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
  size_ = 0;
}

void LinkedList::push_back(int a) {
  auto elem = new TLinkedElement(a);

  if (empty()) {
    head_ = elem;
    tail_ = elem;
  } else {
    elem->prev_ = tail_;
    tail_->next_ = elem;
    tail_ = elem;
  }

  size_++;
}

void LinkedList::erase(TLinkedElement *elem) {
  if (empty()) {
    return;
  }

  auto prev = elem->prev_;
  auto next = elem->next_;

  // first and only one element
  if (!next && !prev && elem == head_) {
    delete elem;
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
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

  size_--;
}

TLinkedElement *LinkedList::begin() { return head_; }
TLinkedElement *LinkedList::end() { return nullptr; }

const TLinkedElement *LinkedList::cbegin() const { return head_; }
const TLinkedElement *LinkedList::cend() const { return nullptr; }

void LinkedList::swap(LinkedList &other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

bool LinkedList::empty() const { return size_ == 0; }

std::size_t LinkedList::size() const { return size_; }

// end LinkedList
