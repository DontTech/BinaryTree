cmake_minimum_required(VERSION 3.8)
project(BinaryTree CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp BinaryTree.h Node.h NodeTraits.h)
add_executable(BinaryTree ${SOURCE_FILES})
