#ifndef PROJECT_ESPRIT_MODEL_C_HASHTABLE_H
#define PROJECT_ESPRIT_MODEL_C_HASHTABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
#include <functional>

// Node structure for the linked list in each bucket
template <typename K, typename V>
struct HashNode {
    K key;
    V value;
    HashNode(K key, V value) : key(key), value(value) {}
};

// Hash Map using separate chaining
template <typename K, typename V>
class HashTable {
private:
    static const int BUCKET_COUNT = 100;  // Number of buckets in the hash table
    std::vector<std::list<HashNode<K, V>>> table;  // Array of lists for chaining

    // Hash function to compute the index for a key
    int hash_function(K key) const {
        return std::hash<K>()(key) % BUCKET_COUNT;
    }

public:
    HashTable() : table(BUCKET_COUNT) {}

    // Insert key-value pair into the map
    void insert(K key, V value) {
        int index = hash_function(key);
        auto& bucket = table[index];

        // Check if the key already exists, if so, update the value
        for (auto& node : bucket) {
            if (node.key == key) {
                node.value = value;  // Update existing value
                return;
            }
        }

        // Otherwise, insert the new key-value pair
        bucket.push_back(HashNode<K, V>(key, value));
    }

    // Get value by key
    V get(K key) {
        int index = hash_function(key);
        auto& bucket = table[index];

        for (auto& node : bucket) {
            if (node.key == key) {
                return node.value;
            }
        }

        throw std::out_of_range("Key not found.");
    }

    // New function: getTarget to get a pointer to the value or return nullptr
    V* getTarget(const K& key) {  // Use the correct template parameters K and V
        int index = hash_function(key);
        auto& bucket = table[index];

        for (auto& node : bucket) {
            if (node.key == key) {
                return &(node.value);  // Return pointer to the value
            }
        }

        return nullptr;  // Return nullptr if the key is not found
    }

    // Remove key-value pair by key
    void remove(K key) {
        int index = hash_function(key);
        auto& bucket = table[index];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                bucket.erase(it);
                return;
            }
        }

        throw std::out_of_range("Key not found.");
    }

    // Check if a key exists in the map
    bool contains(K key) const {
        int index = hash_function(key);
        auto& bucket = table[index];

        for (auto& node : bucket) {
            if (node.key == key) {
                return true;
            }
        }

        return false;
    }

    // Function to get all key-value pairs from the hash table
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

