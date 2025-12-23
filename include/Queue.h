#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>

template <typename T>
struct QNode {
    T data;
    QNode* next;
    QNode(T d) : data(d), next(nullptr) {}
};

template <typename T>
class Queue {
private:
    QNode<T>* frontNode;
    QNode<T>* rearNode;
public:
    Queue() : frontNode(nullptr), rearNode(nullptr) {}

    void push(T val) {
        QNode<T>* newNode = new QNode<T>(val);
        if (rearNode == nullptr) {
            frontNode = rearNode = newNode;
            return;
        }
        rearNode->next = newNode;
        rearNode = newNode;
    }

    void pop() {
        if (frontNode == nullptr) return;
        QNode<T>* temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode == nullptr) rearNode = nullptr;
        delete temp;
    }

    T getFront() {
        if (frontNode != nullptr) return frontNode->data;
        throw std::runtime_error("Queue is empty");
    }

    bool empty() {
        return frontNode == nullptr;
    }
    
    ~Queue() {
        while (!empty()) pop();
    }
};

#endif
