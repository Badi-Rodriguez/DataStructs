//
// Created by Badi on 11/14/2024.
//

#ifndef PROJECT_ESPRIT_MODEL_C_BINODE_H
#define PROJECT_ESPRIT_MODEL_C_BINODE_H


struct BiNode {
private:
    char symbol;
public:
    int data;
    BiNode* prev; // The one before
    BiNode* next; // The one after
};


#endif //PROJECT_ESPRIT_MODEL_C_BINODE_H
