#include "./LinkedList.h"
#include "./testing_framework.h"

#include "./LinkedListTest.h"
#include <cassert>
#include <utility>

LinkedList CreateList() {
  LinkedList list;
  for (int i = 1; i <= 3; i++) {
    list.push_back(i);
  }
  ASSERT_EQUAL(list.size(), 3);
  return list;
}

void TestLinkedListBeginIterator() {
  auto list = CreateList();

  auto it = list.begin();
  ASSERT(it);

  ASSERT_EQUAL(it->value, 1);
  it = it->next();
  ASSERT_EQUAL(it->value, 2);
  it = it->next();
  ASSERT_EQUAL(it->value, 3);
  ASSERT_EQUAL(it->next(), list.end());
}

void TestLinkedListErase() {
  auto list = CreateList();

  list.erase(list.begin());
  ASSERT_EQUAL(list.size(), 2);

  auto it = list.begin();
  ASSERT(it);

  ASSERT_EQUAL(it->value, 2);
  it = it->next();
  ASSERT_EQUAL(it->value, 3);
  ASSERT_EQUAL(it->next(), list.end());
}

void TestLinkedListEraseAll() {
  auto list = CreateList();

  list.erase(list.begin());
  ASSERT_EQUAL(list.size(), 2);

  list.erase(list.begin());
  ASSERT_EQUAL(list.size(), 1);

  list.erase(list.begin());
  ASSERT_EQUAL(list.size(), 0);

  ASSERT(!list.begin());
  ASSERT(!list.end());
  ASSERT_EQUAL(list.begin(), list.end());
}

void TestLinkedListClear() {
  auto list = CreateList();

  list.clear();

  ASSERT_EQUAL(list.size(), 0);

  ASSERT(!list.begin());
  ASSERT(!list.end());
  ASSERT_EQUAL(list.begin(), list.end());
}

void TestLinkedListCopyCtor() {
  auto list = CreateList();

  LinkedList copied(list);
  ASSERT_EQUAL(copied.size(), 3);
  ASSERT_EQUAL(list.size(), 3);

  auto list_it = list.begin();
  int value = 1;

  for (auto it = copied.begin(); it != copied.end(); it = it->next()) {
    ASSERT_HINT(it != list_it, "copied list iterator should also be a copy");
    ASSERT_EQUAL(it->value, value++);

    list_it = list_it->next();
  }

  copied.clear();
  ASSERT_EQUAL(list.size(), 3);
}

void TestLinkedListMoveCtor() {
  auto list = CreateList();

  LinkedList moved = std::move(list);
  ASSERT_EQUAL(moved.size(), 3);
  ASSERT(list.empty());

  int value = 1;

  for (auto it = moved.begin(); it != moved.end(); it = it->next()) {
    ASSERT_EQUAL(it->value, value++);
  }
}

void TestLinkedList() {
  RUN_TEST(TestLinkedListBeginIterator);
  RUN_TEST(TestLinkedListErase);
  RUN_TEST(TestLinkedListEraseAll);
  RUN_TEST(TestLinkedListClear);
  RUN_TEST(TestLinkedListCopyCtor);
  RUN_TEST(TestLinkedListMoveCtor);
}
