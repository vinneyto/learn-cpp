#include "./LinkedList.h"

#include <cassert>
#include <gtest/gtest.h>
#include <utility>

LinkedList CreateList() {
  LinkedList list;
  for (int i = 1; i <= 3; i++) {
    list.push_back(i);
  }
  EXPECT_EQ(list.size(), 3);
  return list;
}

TEST(LinkedListTest, LinkedListBeginIterator) {
  auto list = CreateList();

  auto it = list.begin();
  EXPECT_TRUE(it);

  EXPECT_EQ(it->value, 1);
  it = it->next();
  EXPECT_EQ(it->value, 2);
  it = it->next();
  EXPECT_EQ(it->value, 3);
  EXPECT_EQ(it->next(), list.end());
}

TEST(LinkedListTest, LinkedListErase) {
  auto list = CreateList();

  list.erase(list.begin());
  EXPECT_EQ(list.size(), 2);

  auto it = list.begin();
  EXPECT_TRUE(it);

  EXPECT_EQ(it->value, 2);
  it = it->next();
  EXPECT_EQ(it->value, 3);
  EXPECT_EQ(it->next(), list.end());
}

TEST(LinkedListTest, LinkedListEraseAll) {
  auto list = CreateList();

  list.erase(list.begin());
  EXPECT_EQ(list.size(), 2);

  list.erase(list.begin());
  EXPECT_EQ(list.size(), 1);

  list.erase(list.begin());
  EXPECT_EQ(list.size(), 0);

  EXPECT_TRUE(!list.begin());
  EXPECT_TRUE(!list.end());
  EXPECT_EQ(list.begin(), list.end());
}

TEST(LinkedListTest, LinkedListClear) {
  auto list = CreateList();

  list.clear();

  EXPECT_EQ(list.size(), 0);

  EXPECT_TRUE(!list.begin());
  EXPECT_TRUE(!list.end());
  EXPECT_EQ(list.begin(), list.end());
}

TEST(LinkedListTest, LinkedListCopyCtor) {
  auto list = CreateList();

  LinkedList copied(list);
  EXPECT_EQ(copied.size(), 3);
  EXPECT_EQ(list.size(), 3);

  auto list_it = list.begin();
  int value = 1;

  for (auto it = copied.begin(); it != copied.end(); it = it->next()) {
    ASSERT_NE(it, list_it) << "copied list iterator should also be a copy";
    EXPECT_EQ(it->value, value++);

    list_it = list_it->next();
  }

  copied.clear();
  EXPECT_EQ(list.size(), 3);
}

TEST(LinkedListTest, LinkedListMoveCtor) {
  auto list = CreateList();

  LinkedList moved = std::move(list);
  EXPECT_EQ(moved.size(), 3);
  EXPECT_TRUE(list.empty());

  int value = 1;

  for (auto it = moved.begin(); it != moved.end(); it = it->next()) {
    EXPECT_EQ(it->value, value++);
  }
}
