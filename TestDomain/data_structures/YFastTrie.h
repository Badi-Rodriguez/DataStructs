#ifndef PROJECT_ESPRIT_MODEL_C_YFASTTRIE_H
#define PROJECT_ESPRIT_MODEL_C_YFASTTRIE_H

#include "XFastTrie.h"
#include "HashTable.h"

template <typename Key, typename Value>
class YFastTrie {
// Dynamic portion (Hash table)

public:
    YFastTrie();  // Constructor

    // Insert key-value pair into both static and dynamic portions
    void insert(Key key, Value value);

    // Find a key in the dynamic hash table, and if not found, look it up in the static X-Fast Trie
    xfast_leaf<Key, Value>* find(Key key);

    // Find the successor of the key (first check dynamic portion, then static)
    xfast_leaf<Key, Value>* succ(Key key);

    // Find the predecessor of the key (first check dynamic portion, then static)
    xfast_leaf<Key, Value>* pred(Key key);

    // Delete the key from both the dynamic portion and static portion
    void deleteKey(Key key);

    XFastTrie<Key, Value> xfastTrie;
// Static portion (X-Fast Trie)
HashTable<Key, xfast_leaf<Key, Value>> dynamicHashTable;
};

#endif //PROJECT_ESPRIT_MODEL_C_YFASTTRIE_H
