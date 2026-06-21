cmake_minimum_required(VERSION 4.2)

project(cpp_task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(cpp_task
    src/main.cpp
    src/LinkedList.cpp
)

add_executable(cpp_task_tests
    src/LinkedList.cpp
    src/LinkedListTest.cpp
)

target_link_libraries(
    cpp_task_tests
    PRIVATE
    GTest::gtest_main
)

enable_testing()

include(GoogleTest)
gtest_discover_tests(cpp_task_tests)
