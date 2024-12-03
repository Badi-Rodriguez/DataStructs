//
// Created by Badi on 12/3/2024.
//

#ifndef DATASTRUCTS_BPLUSTREE_H
#define DATASTRUCTS_BPLUSTREE_H


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// B+ Tree Node structure
class BPlusTreeNode {
public:
    vector<int> keys;                // Keys in the node
    vector<BPlusTreeNode*> children; // Pointers to child nodes
    BPlusTreeNode* next;             // Pointer to the next leaf (for leaf nodes only)
    bool isLeaf;                     // Flag to indicate if the node is a leaf

    BPlusTreeNode(bool leaf) : isLeaf(leaf), next(nullptr) {}
};

// B+ Tree class
class BPlusTree {
private:
    int degree; // Minimum degree (defines the order of the tree)
    BPlusTreeNode* root;

    // Helper function to split a child node
    void splitChild(BPlusTreeNode* parent, int index) {
        BPlusTreeNode* fullChild = parent->children[index];
        int midIndex = degree - 1;

        // Create a new node for the right half
        BPlusTreeNode* newChild = new BPlusTreeNode(fullChild->isLeaf);

        // Move the second half of keys to the new node
        newChild->keys.assign(fullChild->keys.begin() + midIndex + 1, fullChild->keys.end());
        fullChild->keys.resize(midIndex);

        // Move the second half of children (if not a leaf)
        if (!fullChild->isLeaf) {
            newChild->children.assign(fullChild->children.begin() + midIndex + 1, fullChild->children.end());
            fullChild->children.resize(midIndex + 1);
        }

        // Update linked list pointers for leaves
        if (fullChild->isLeaf) {
            newChild->next = fullChild->next;
            fullChild->next = newChild;
        }

        // Insert the middle key into the parent
        parent->keys.insert(parent->keys.begin() + index, fullChild->keys[midIndex]);
        parent->children.insert(parent->children.begin() + index + 1, newChild);
    }

    // Helper function to insert a key into a non-full node
    void insertNonFull(BPlusTreeNode* node, int key) {
        if (node->isLeaf) {
            // Insert the key into the leaf in sorted order
            node->keys.insert(lower_bound(node->keys.begin(), node->keys.end(), key), key);
        } else {
            // Find the child to recurse on
            int index = upper_bound(node->keys.begin(), node->keys.end(), key) - node->keys.begin();
            if (node->children[index]->keys.size() == 2 * degree - 1) {
                // Split the child if it's full
                splitChild(node, index);
                if (key > node->keys[index])
                    index++;
            }
            insertNonFull(node->children[index], key);
        }
    }

    // Helper function for printing (in-order traversal)
    void printNode(BPlusTreeNode* node, int depth) {
        if (node) {
            for (int i = 0; i < depth; i++) cout << "  ";
            for (int key : node->keys) cout << key << " ";
            cout << (node->isLeaf ? "(Leaf)" : "(Internal)") << endl;

            if (!node->isLeaf) {
                for (auto child : node->children) {
                    printNode(child, depth + 1);
                }
            }
        }
    }

public:
    BPlusTree(int degree) : degree(degree), root(new BPlusTreeNode(true)) {}

    // Insert a key into the tree
    void insert(int key) {
        if (root->keys.size() == 2 * degree - 1) {
            // If the root is full, split it and create a new root
            BPlusTreeNode* newRoot = new BPlusTreeNode(false);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0);
            root = newRoot;
        }
        insertNonFull(root, key);
    }

    // Print the B+ Tree
    void print() {
        cout << "B+ Tree Structure:" << endl;
        printNode(root, 0);
    }
};

int main() {
    int degree = 3; // B+ Tree order
    BPlusTree tree(degree);

    vector<int> keys = {10, 20, 5, 6, 12, 30, 7, 17};

    for (int key : keys) {
        cout << "Inserting key: " << key << endl;
        tree.insert(key);
        tree.print();
        cout << "--------------------------------" << endl;
    }

    return 0;
}



#endif //DATASTRUCTS_BPLUSTREE_H
