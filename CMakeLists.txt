cmake_minimum_required(VERSION 3.15)
project(practice)

set(CMAKE_CXX_STANDARD 14)

#aux_source_directory(. SRC_LIST) #搜索当前目录下的所有.cpp文件

include_directories(Vector Utils List Stack Queue BinaryTree Graph SearchTree)
add_executable(practice main.cpp SearchTree/Splay.h SearchTree/BTree.h)