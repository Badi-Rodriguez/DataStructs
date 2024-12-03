#include "DoubleList.h"

// Destructor
template <typename T>
DoubleList<T>::~DoubleList() {
    while (head) {
        pop_front();
    }
}

// Fetch head of the list
template <typename T>
BiNode<T>* DoubleList<T>::fetch_head() {
    return head;
}

// Convert list to vector
template <typename T>
std::vector<T>* DoubleList<T>::get_vector() {
    auto* result = new std::vector<T>();
    BiNode<T>* current = head;
    while (current) {
        result->push_back(current->data);
        current = current->next;
    }
    return result;  // Caller is responsible for deleting the vector
}

// Find a value in the list
template <typename T>
int DoubleList<T>::find(const T& value) {
    BiNode<T>* current = head;
    int index = 0;
    while (current) {
        if (current->data == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;  // Not found
}

// Remove the front node
template <typename T>
void DoubleList<T>::pop_front() {
    if (head) {
        BiNode<T>* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;  // If the list becomes empty
        }
        delete temp;
    }
}

// Remove the back node
template <typename T>
void DoubleList<T>::pop_back() {
    if (tail) {
        BiNode<T>* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;  // If the list becomes empty
        }
        delete temp;
    }
}

// Add a value to the front
template <typename T>
void DoubleList<T>::push_front(const T& value) {
    BiNode<T>* newNode = new BiNode<T>(value);
    if (head) {
        newNode->next = head;
        head->prev = newNode;
    } else {
        tail = newNode;  // If the list is empty, new node is both head and tail
    }
    head = newNode;
}

// Add a value to the back
template <typename T>
void DoubleList<T>::push_back(const T& value) {
    BiNode<T>* newNode = new BiNode<T>(value);
    if (tail) {
        newNode->prev = tail;
        tail->next = newNode;
    } else {
        head = newNode;  // If the list is empty, new node is both head and tail
    }
    tail = newNode;
}

// Remove a target node by value
template <typename T>
void DoubleList<T>::remove_target(const T& value) {
    BiNode<T>* nodeToRemove = head;
    while (nodeToRemove && nodeToRemove->data != value) {
        nodeToRemove = nodeToRemove->next;
    }

    if (nodeToRemove) {
        if (nodeToRemove->prev) {
            nodeToRemove->prev->next = nodeToRemove->next;
        } else {
            head = nodeToRemove->next;  // Node is head
        }

        if (nodeToRemove->next) {
            nodeToRemove->next->prev = nodeToRemove->prev;
        } else {
            tail = nodeToRemove->prev;  // Node is tail
        }

        delete nodeToRemove;
    }
}

// Explicitly instantiate the template functions if necessary (optional in some cases)
template class DoubleList<int>;  // Explicit instantiation for int



