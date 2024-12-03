//
// Created by Badi on 12/2/2024.
//

#include "data_structures/YFastTrie.h"
#include <iostream>

void YFastTrieTest() {
    std::cout << "Running YFastTrie Tests..." << std::endl;

    // Create a YFastTrie instance
    YFastTrie<int, std::string> trie;

    // Insert key-value pairs
    trie.insert(10, "Ten");
    trie.insert(20, "Twenty");
    trie.insert(30, "Thirty");
    trie.insert(40, "Forty");

    // Test find operation
    std::cout << "Find 10: " << trie.find(10)->value << std::endl;  // Should print "Ten"
    std::cout << "Find 20: " << trie.find(20)->value << std::endl;  // Should print "Twenty"
    std::cout << "Find 50: " << (trie.find(50) == nullptr ? "Not Found" : trie.find(50)->value) << std::endl;  // Should print "Not Found"

    // Test successor and predecessor
    std::cout << "Succ of 10: " << (trie.succ(10) == nullptr ? "No Successor" : trie.succ(10)->value) << std::endl;  // Should print "Twenty"
    std::cout << "Pred of 30: " << (trie.pred(30) == nullptr ? "No Predecessor" : trie.pred(30)->value) << std::endl;  // Should print "Twenty"

    // Test delete operation
    trie.deleteKey(20);  // Should delete key 20
    std::cout << "Find 20 after delete: " << (trie.find(20) == nullptr ? "Not Found" : trie.find(20)->value) << std::endl;  // Should print "Not Found"
}

