#include "YFastTrie.h"

// Constructor
template<typename Key, typename Value>
YFastTrie<Key, Value>::YFastTrie() {}

// Insert key-value pair into both static and dynamic portions
template<typename Key, typename Value>
void YFastTrie<Key, Value>::insert(Key key, Value value) {
    // Insert into the static portion (X-Fast Trie)
    xfastTrie.insert(key, value);

    // Insert into the dynamic hash table
    dynamicHashTable.insert(key, xfast_leaf<Key, Value>(key, value));
}

// Find a key in the dynamic hash table, and if not found, look it up in the static X-Fast Trie
template<typename Key, typename Value>
xfast_leaf<Key, Value>* YFastTrie<Key, Value>::find(Key key) {
    // First, check the dynamic portion (hash table)
    xfast_leaf<Key, Value>* leaf = dynamicHashTable.getTarget(key);
    if (leaf != nullptr) {
        return leaf;  // If found in dynamic portion, return the leaf
    }

    // If not found in the dynamic portion, look it up in the static X-Fast Trie
    return xfastTrie.find(key);
}

// Find the successor of the key (first check dynamic portion, then static)
template<typename Key, typename Value>
xfast_leaf<Key, Value>* YFastTrie<Key, Value>::succ(Key key) {
    // First, check the dynamic portion (hash table)
    xfast_leaf<Key, Value>* leaf = dynamicHashTable.getTarget(key);
    if (leaf != nullptr) {
        return leaf;  // If found in dynamic portion, return the leaf
    }

    // If not found in dynamic portion, check static portion (X-Fast Trie)
    return xfastTrie.succ(key);
}

// Find the predecessor of the key (first check dynamic portion, then static)
template<typename Key, typename Value>
xfast_leaf<Key, Value>* YFastTrie<Key, Value>::pred(Key key) {
    // First, check dynamic portion (hash table)
    xfast_leaf<Key, Value>* leaf = dynamicHashTable.getTarget(key);
    if (leaf != nullptr) {
        return leaf;  // If found in dynamic portion, return the leaf
    }

    // If not found in dynamic portion, check static portion (X-Fast Trie)
    return xfastTrie.pred(key);
}

// Delete the key from both the dynamic portion and static portion
template<typename Key, typename Value>
void YFastTrie<Key, Value>::deleteKey(Key key) {
    // Remove from dynamic hash table
    dynamicHashTable.remove(key);

    // Remove from static X-Fast Trie
    xfastTrie.deleteKey(key);
}

// Explicit template instantiation (for int type, you can add more as needed)
template class YFastTrie<int, std::string>;

