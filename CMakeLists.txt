cmake_minimum_required(VERSION 4.2)
project(cpp_task)

set(CMAKE_CXX_STANDARD 23)

add_executable(cpp_task
    src/main.cpp
    src/LinkedList.cpp
    src/LinkedListTest.cpp
    src/testing_framework.cpp
)
