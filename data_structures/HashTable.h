#ifndef PROJECT_ESPRIT_MODEL_C_HASHTABLE_H
#define PROJECT_ESPRIT_MODEL_C_HASHTABLE_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <functional>
#include "DoubleList.h"

// Custom hash function for strings
int custom_hash_function(const std::string& key) {
    int hash = 0;
    for (char ch : key) {
        hash = (hash * 31) + ch;  // Simple hash function example
    }
    return hash;
}

// HashNode structure
template <typename K, typename V>
struct HashNode {
    K key;
    V value;
    HashNode(K key, V value) : key(key), value(value) {}
};

// HashTable class
template <typename K, typename V>
class HashTable {
private:
    static const int BUCKET_COUNT = 100;
    std::vector<DoubleList<HashNode<K, V>>> table;  // Using templated DoubleList

    // Specialization for string keys
    int hash_function(const std::string& key) const {
        return custom_hash_function(key) % BUCKET_COUNT;
    }

public:
    HashTable() : table(BUCKET_COUNT) {}

    // Insert or update a key-value pair
    void insert(const K& key, const V& value) {
        int index = hash_function(key);
        auto& bucket = table[index];

        for (auto& node : bucket) {
            if (node.key == key) {
                node.value = value;  // Update existing value
                return;
            }
        }

        bucket.push_back(HashNode<K, V>(key, value));  // Insert new key-value pair
    }

    // Get the value associated with a key, throws exception if not found
    V get(const K& key) const {
        int index = hash_function(key);
        const auto& bucket = table[index];

        for (const auto& node : bucket) {
            if (node.key == key) {
                return node.value;
            }
        }

        throw std::out_of_range("Key not found: " + std::to_string(key));
    }

    // Get a pointer to the value associated with a key, or return nullptr if not found
    V* getTarget(const K& key) {
        int index = hash_function(key);
        auto& bucket = table[index];

        for (auto& node : bucket) {
            if (node.key == key) {
                return &node.value;
            }
        }

        return nullptr;
    }

    // Remove a key-value pair by key, throws exception if not found
    void remove(const K& key) {
        int index = hash_function(key);
        auto& bucket = table[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                bucket.erase(it);
                return;
            }
        }

        throw std::out_of_range("Key not found: " + std::to_string(key));
    }

    // Check if a key exists in the table
    bool contains(const K& key) const {
        int index = hash_function(key);
        const auto& bucket = table[index];

        for (const auto& node : bucket) {
            if (node.key == key) {
                return true;
            }
        }

        return false;
    }

    // Retrieve all nodes from the hash table
    std::vector<HashNode<K, V>> getAllNodes() const {
        std::vector<HashNode<K, V>> allNodes;
        for (const auto& bucket : table) {
            for (const auto& node : bucket) {
                allNodes.push_back(node);  // Add each node to the list
            }
        }
        return allNodes;
    }
};

#endif //PROJECT_ESPRIT_MODEL_C_HASHTABLE_H


