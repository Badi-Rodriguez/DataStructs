#include <iostream>
#include "XFastTrie.h"

void XFastTrieTest() {
    // Create a new XFastTrie instance
    XFastTrie<int, std::string> trie;

    // Insert some key-value pairs
    trie.insert(5, "Apple");
    trie.insert(10, "Banana");
    trie.insert(3, "Cherry");

    // Test find function
    auto result = trie.find(5);
    if (result) {
        std::cout << "Found key 5: " << result->value << std::endl;
    } else {
        std::cout << "Key 5 not found." << std::endl;
    }

    result = trie.find(10);
    if (result) {
        std::cout << "Found key 10: " << result->value << std::endl;
    } else {
        std::cout << "Key 10 not found." << std::endl;
    }

    // Test predecessor function
    auto predResult = trie.pred(10);
    if (predResult) {
        std::cout << "Predecessor of 10: " << predResult->value << std::endl;
    } else {
        std::cout << "No predecessor for 10." << std::endl;
    }

    // Test successor function
    auto succResult = trie.succ(10);
    if (succResult) {
        std::cout << "Successor of 10: " << succResult->value << std::endl;
    } else {
        std::cout << "No successor for 10." << std::endl;
    }
}