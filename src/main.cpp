#include <cassert>
#include <cstddef>
#include <iostream>

#include "LinkedList.h"

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

// testing
int main() {
  LinkedList list;

  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  for (auto it = list.begin(); it != list.end(); it = it->next()) {
    std::cout << it->value << std::endl;
  }

  return 0;
}
