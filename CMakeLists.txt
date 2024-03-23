cmake_minimum_required(VERSION 3.26)
project(ciaod)

set(CMAKE_CXX_STANDARD 17)

add_executable(task1 1/1.cpp)
add_executable(task2 2/main1.cpp 2/FunctionsDefault.cpp 2/FunctionsDefault.h 2/FunctionsBin.h 2/FunctionsBin.cpp)
add_executable(task3 3/main.cpp 3/HashTable.h 3/HashTable.cpp 3/FunctionsBin.h 3/FunctionsBin.cpp)
