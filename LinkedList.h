#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <vector>

template <typename T>
struct LNode {
    T data;
    LNode* next;
    LNode(T d) : data(d), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    LNode<T>* head;
    LNode<T>* tail;
public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    void push_back(T val) {
        LNode<T>* newNode = new LNode<T>(val);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void display() const {
        LNode<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << std::endl;
            temp = temp->next;
        }
    }

    std::vector<T> toVector() const {
        std::vector<T> vec;
        LNode<T>* temp = head;
        while (temp != nullptr) {
            vec.push_back(temp->data);
            temp = temp->next;
        }
        return vec;
    }
    
    ~LinkedList() {
        LNode<T>* current = head;
        while (current != nullptr) {
            LNode<T>* next = current->next;
            delete current;
            current = next;
        }
    }
};

#endif
