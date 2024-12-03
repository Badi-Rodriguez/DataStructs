//
// Created by Badi on 11/14/2024.
//

#ifndef PROJECT_ESPRIT_MODEL_C_DOUBLELIST_H
#define PROJECT_ESPRIT_MODEL_C_DOUBLELIST_H

#include <iostream>
#include <vector>
#include "BiNode.h"

class DoubleList {
private:
    BiNode* head;
    BiNode* tail;
public:
    DoubleList() = default;
    DoubleList(BiNode *head, BiNode *tail);
    ~DoubleList();
    BiNode* fetch_head();
    std::vector<int> * get_vector();
    int find(int);
    void pop_front();
    void pop_back();
    void remove_target(int);
};


#endif //PROJECT_ESPRIT_MODEL_C_DOUBLELIST_H
