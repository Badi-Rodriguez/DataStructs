cmake_minimum_required(VERSION 3.28)
project(DataStructs)

set(CMAKE_CXX_STANDARD 14)

include_directories(data_structures)
include_directories(TestDomain)
include_directories(TestDomain/data_structures)

add_executable(DataStructs
        data_structures/BiNode.cpp
        data_structures/BiNode.h
        data_structures/BST.cpp
        data_structures/BST.h
        data_structures/DoubleList.cpp
        data_structures/DoubleList.h
        data_structures/ForwardList.cpp
        data_structures/ForwardList.h
        data_structures/HashTable.cpp
        data_structures/HashTable.h
        data_structures/Node.cpp
        data_structures/Node.h
        data_structures/PriorityQueue.cpp
        data_structures/PriorityQueue.h
        data_structures/XFastTrie.cpp
        data_structures/XFastTrie.h
        TestDomain/data_structures/BiNode.cpp
        TestDomain/data_structures/BiNode.h
        TestDomain/data_structures/BST.cpp
        TestDomain/data_structures/BST.h
        TestDomain/data_structures/DoubleList.cpp
        TestDomain/data_structures/DoubleList.h
        TestDomain/data_structures/ForwardList.cpp
        TestDomain/data_structures/ForwardList.h
        TestDomain/data_structures/HashTable.cpp
        TestDomain/data_structures/HashTable.h
        TestDomain/data_structures/Node.cpp
        TestDomain/data_structures/Node.h
        TestDomain/data_structures/PriorityQueue.cpp
        TestDomain/data_structures/PriorityQueue.h
        TestDomain/data_structures/XFastTrie.cpp
        TestDomain/data_structures/XFastTrie.h
        TestDomain/data_structures/YFastTrie.cpp
        TestDomain/data_structures/YFastTrie.h
        TestDomain/Dijikstra.cpp
        TestDomain/HashTableTest.cpp
        TestDomain/HashTableTest.h
        TestDomain/main.cpp
        TestDomain/XFastTrieTest.cpp
        TestDomain/XFastTrieTest.h
        TestDomain/YFastTrieTest.cpp
        TestDomain/YFastTrieTest.h
        TestDomain/Kruskal.cpp)
