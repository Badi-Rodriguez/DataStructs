#ifndef PROJECT_ESPRIT_MODEL_C_XFASTTRIE_H
#define PROJECT_ESPRIT_MODEL_C_XFASTTRIE_H

#include <unordered_map>
#include "DoubleList.h"
#include "HashTable.h"

template <typename Key, typename Value>
struct xfast_leaf {
    Key key;
    Value value;

    xfast_leaf(Key key, Value value) : key(key), value(value) {}
};

template <typename Key, typename Value>
struct xfast_node {
    xfast_node* left;  // left child
    xfast_node* right; // right child
    xfast_leaf<Key, Value>* leaf; // the leaf node at this node

    xfast_node() : left(nullptr), right(nullptr), leaf(nullptr) {}
};

template<typename Key, typename Value>
class XFastTrie {
private:
    typedef xfast_node<Key, Value> Node;
    typedef xfast_leaf<Key, Value> Leaf;

    static const int BITS = sizeof(Key) * 8;  // Number of bits in Key
    Node* root;
    HashTable<Key, Node*> hashTable[BITS];  // Hash table for each level

public:
    XFastTrie() : root(new Node()) {}  // Constructor

    void insert(Key key, Value value) {
        Node* currentNode = root;

        // Traverse the trie based on the binary representation of the key
        for (int i = BITS - 1; i >= 0; --i) {
            bool bit = (key >> i) & 1;

            if (bit == 0) {
                if (currentNode->left == nullptr) {
                    currentNode->left = new Node();
                }
                currentNode = currentNode->left;
            } else {
                if (currentNode->right == nullptr) {
                    currentNode->right = new Node();
                }
                currentNode = currentNode->right;
            }
        }

        // Insert the key-value pair as a leaf at the current node
        currentNode->leaf = new Leaf(key, value);

        // Add the node to the hash table at the correct level (using the key's bits)
        for (int i = BITS - 1; i >= 0; --i) {
            bool bit = (key >> i) & 1;
            hashTable[i].insert(key, currentNode);
        }
    }

    Leaf* find(Key key) {
        Node* currentNode = root;

        // Traverse the trie based on the binary representation of the key
        for (int i = BITS - 1; i >= 0; --i) {
            bool bit = (key >> i) & 1;

            if (bit == 0) {
                if (currentNode->left != nullptr) {
                    currentNode = currentNode->left;
                } else {
                    return nullptr;
                }
            } else {
                if (currentNode->right != nullptr) {
                    currentNode = currentNode->right;
                } else {
                    return nullptr;
                }
            }
        }

        return currentNode->leaf;
    }

    Leaf* succ(Key key) {
        Node* currentNode = root;
        Node* successor = nullptr;

        for (int i = BITS - 1; i >= 0; --i) {
            bool bit = (key >> i) & 1;

            if (bit == 0) {
                if (currentNode->right != nullptr) {
                    currentNode = currentNode->right;
                } else {
                    if (currentNode->left != nullptr) {
                        successor = currentNode->left;
                    }
                }
            } else {
                if (currentNode->left != nullptr) {
                    currentNode = currentNode->left;
                } else {
                    if (currentNode->right != nullptr) {
                        successor = currentNode->right;
                    }
                }
            }
        }

        if (successor != nullptr) {
            return successor->leaf;
        }

        return nullptr;  // No successor found
    }

    Leaf* pred(Key key) {
        Node* currentNode = root;
        Node* predecessor = nullptr;

        for (int i = BITS - 1; i >= 0; --i) {
            bool bit = (key >> i) & 1;

            if (bit == 0) {
                if (currentNode->left != nullptr) {
                    currentNode = currentNode->left;
                } else {
                    if (currentNode->right != nullptr) {
                        predecessor = currentNode->right;
                    }
                }
            } else {
                if (currentNode->right != nullptr) {
                    currentNode = currentNode->right;
                } else {
                    if (currentNode->left != nullptr) {
                        predecessor = currentNode->left;
                    }
                }
            }
        }

        if (predecessor != nullptr) {
            return predecessor->leaf;
        }

        return nullptr;  // No predecessor found
    }

    // Helper function to delete a key from the trie recursively
    bool deleteRecursively(Node* currentNode, Key key, int bitIndex) {
        if (bitIndex < 0) {
            return false;  // Base case: We've reached the end of the key without finding it
        }

        bool bit = (key >> bitIndex) & 1;  // Get the bit at the current position

        // Traverse to the left or right child based on the bit
        Node* childNode = bit == 0 ? currentNode->left : currentNode->right;

        if (childNode == nullptr) {
            return false;  // Key doesn't exist, no node to traverse
        }

        // Recurse down to the correct child node
        bool childDeleted = deleteRecursively(childNode, key, bitIndex - 1);

        // If child is deleted, we might need to clean up the current node
        if (childDeleted) {
            // Check if the node is now a leaf and has no children
            if (childNode->left == nullptr && childNode->right == nullptr && childNode->leaf == nullptr) {
                delete childNode;  // Delete the child node as it's no longer needed
                if (bit == 0) {
                    currentNode->left = nullptr;  // Nullify the reference to the child
                } else {
                    currentNode->right = nullptr;
                }
            }
        }

        // If the key is found, remove it and update the hash table
        if (bitIndex == 0 && childNode->leaf != nullptr && childNode->leaf->key == key) {
            // Remove from hash table at each level
            for (int i = BITS - 1; i >= 0; --i) {
                bool bitAtLevel = (key >> i) & 1;
                hashTable[i].remove(key);
            }

            // Remove the leaf
            delete childNode->leaf;
            childNode->leaf = nullptr;
            return true;  // Key deleted successfully
        }

        return false;
    }

    // Public method to delete a key
    void deleteKey(Key key) {
        deleteRecursively(root, key, BITS - 1);  // Start from the root and the highest bit
    }

    // Function to get all the nodes in the X-Fast Trie (recursive traversal)
    void getNodes(Node* node, std::vector<Node*>& nodes) const {
        if (node == nullptr) return;

        // If node has a leaf, add it to the list
        if (node->leaf != nullptr) {
            nodes.push_back(node);
        }

        // Recursively add left and right child nodes
        getNodes(node->left, nodes);
        getNodes(node->right, nodes);
    }

    // Public method to get all nodes starting from the root
    std::vector<Node*> getAllNodes() const {
        std::vector<Node*> nodes;
        getNodes(root, nodes);  // Start recursive traversal from the root
        return nodes;
    }

};

#endif //PROJECT_ESPRIT_MODEL_C_XFASTTRIE_H


