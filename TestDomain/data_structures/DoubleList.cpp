//
// Created by Badi on 11/14/2024.
//

#include "DoubleList.h"

DoubleList::DoubleList(BiNode *head, BiNode *tail) {
    this->head = head ? head : nullptr;
    this->tail = tail ? tail : nullptr;
}

DoubleList::~DoubleList() {
    while (head) {
        pop_front();  // Or simply delete nodes if you manage memory manually
    }
}

BiNode *DoubleList::fetch_head() {
    return head;
}

std::vector<int> * DoubleList::get_vector() {
    return nullptr;
}

int DoubleList::find(int value) {
    BiNode* current = head;
    int index = 0;
    while (current) {
        if (current->data == value) {
            return index;  // Or return a pointer to the node, depending on your design
        }
        current = current->next;
        index++;
    }
    return -1;  // Not found
}

void DoubleList::pop_front() {
    if (head) {
        BiNode* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;  // If the list becomes empty
        }
        delete temp;
    }
}

void DoubleList::pop_back() {
    if (tail) {
        BiNode* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;  // If the list becomes empty
        }
        delete temp;
    }
}

void DoubleList::remove_target(int value) {
    int index = find(value);
    if (index != -1) {
        BiNode* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        // Now remove the node
        if (current->prev) {
            current->prev->next = current->next;
        } else {
            head = current->next;  // Removed the head
        }
        if (current->next) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;  // Removed the tail
        }
        delete current;
    }
}

