#include <algorithm>
#include <cstddef>
#include <memory>
#include <utility>

#include "LinkedList.h"

// TLinkedElement

TLinkedElement::TLinkedElement() {}

TLinkedElement::TLinkedElement(int value) : value(value) {}

TLinkedElement *TLinkedElement::prev() { return prev_.lock().get(); }

TLinkedElement *TLinkedElement::next() { return next_.get(); }

const TLinkedElement *TLinkedElement::prev() const {
  return prev_.lock().get();
}

const TLinkedElement *TLinkedElement::next() const { return next_.get(); }

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

LinkedList::LinkedList(LinkedList &&other) noexcept
    : head_(std::move(other.head_)), tail_(std::move(other.tail_)),
      size_(other.size_) {
  other.size_ = 0;
}

LinkedList::~LinkedList() { clear(); }

void LinkedList::clear() {
  auto tail = tail_;

  while (tail) {
    tail->next_ = nullptr;
    // move closer to head
    tail = tail->prev_.lock();
  }

  head_ = nullptr;
  tail_ = nullptr;
  size_ = 0;
}

void LinkedList::push_back(int a) {
  auto elem = std::make_shared<TLinkedElement>(a);

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

  if (!elem) {
    return;
  }

  auto prev = elem->prev_.lock();
  auto next = elem->next_;

  elem->prev_.reset();
  elem->next_.reset();

  if (prev) {
    prev->next_ = next;
  } else {
    head_ = next;
  }

  if (next) {
    next->prev_ = prev;
  } else {
    tail_ = prev;
  }

  size_--;
}

TLinkedElement *LinkedList::begin() { return head_.get(); }
TLinkedElement *LinkedList::end() { return nullptr; }

const TLinkedElement *LinkedList::cbegin() const { return head_.get(); }
const TLinkedElement *LinkedList::cend() const { return nullptr; }

void LinkedList::swap(LinkedList &other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

bool LinkedList::empty() const { return size_ == 0; }

std::size_t LinkedList::size() const { return size_; }

// end LinkedList
