cmake_minimum_required(VERSION 3.28)

# Project name and C++ standard version
project(TestDomain)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)

# Define include directories (where header files are located)
include_directories(${CMAKE_SOURCE_DIR}/data_structures)

# Create executable with source files
add_executable(TestDomain
        main.cpp
        data_structures/BiNode.cpp
        data_structures/BST.cpp
        data_structures/DoubleList.cpp
        data_structures/ForwardList.cpp
        data_structures/HashTable.cpp
        data_structures/Node.cpp
        data_structures/PriorityQueue.cpp
        data_structures/YFastTrie.cpp
        data_structures/XFastTrie.cpp
        XFastTrieTest.cpp
        XFastTrieTest.h
        HashTableTest.cpp
        HashTableTest.h
        YFastTrieTest.cpp
        YFastTrieTest.h
        UnionFind.cpp
        searches.cpp
)

# Optional: If you want to separate header files explicitly
# target_include_directories(TestDomain PRIVATE ${CMAKE_SOURCE_DIR}/data_structures)

