// HashTableTest.cpp
#include <iostream>
#include "data_structures/HashTable.h"

void HashTableTest() {
    // Create a HashTable instance
    HashTable<int, std::string> hashTable;

    // Insert key-value pairs
    hashTable.insert(1, "Apple");
    hashTable.insert(2, "Banana");
    hashTable.insert(3, "Cherry");

    // Test get function
    try {
        std::cout << "Value for key 1: " << hashTable.get(1) << std::endl;  // Expected: Apple
        std::cout << "Value for key 2: " << hashTable.get(2) << std::endl;  // Expected: Banana
        std::cout << "Value for key 3: " << hashTable.get(3) << std::endl;  // Expected: Cherry
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }

    // Test contains function
    std::cout << "Contains key 2: " << (hashTable.contains(2) ? "Yes" : "No") << std::endl;  // Expected: Yes
    std::cout << "Contains key 4: " << (hashTable.contains(4) ? "Yes" : "No") << std::endl;  // Expected: No

    // Test remove function
    try {
        hashTable.remove(2);  // Remove key 2
        std::cout << "Key 2 removed." << std::endl;
        hashTable.get(2);  // Try to get key 2, should throw exception
    } catch (const std::out_of_range& e) {
        std::cout << "Exception: " << e.what() << std::endl;  // Expected: Key not found
    }

    // Test after removal
    std::cout << "Contains key 2: " << (hashTable.contains(2) ? "Yes" : "No") << std::endl;  // Expected: No
}
