#ifndef PROJECT_ESPRIT_MODEL_C_DOUBLELIST_H
#define PROJECT_ESPRIT_MODEL_C_DOUBLELIST_H

#include <iostream>
#include <vector>
#include "BiNode.h"

template <typename T>  // Add template parameter
class DoubleList {
private:
    BiNode<T>* head;
    BiNode<T>* tail;

public:
    DoubleList() : head(nullptr), tail(nullptr) {}
    ~DoubleList();

    // Basic operations
    BiNode<T>* fetch_head();
    std::vector<T>* get_vector();  // Converts list to vector
    int find(const T& value);
    void pop_front();
    void pop_back();
    void remove_target(const T& value);

    // New operations for flexibility
    void push_front(const T& value);
    void push_back(const T& value);
};

#endif //PROJECT_ESPRIT_MODEL_C_DOUBLELIST_H



