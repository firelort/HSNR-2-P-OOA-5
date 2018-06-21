//
// Created by hartings on 04.06.18.
//

#ifndef OOA4_PRIORITYQUEUE_H
#define OOA4_PRIORITYQUEUE_H

#include <iostream>
#include "Execption.h"

using namespace std;

template<typename T>
class PriorityQueueEntry {
public:
    float priority;
    T value;
    PriorityQueueEntry<T> *next, *prev;

    PriorityQueueEntry(T value, float priority) {
        this->value = value;
        this->priority = priority;
        next = nullptr;
        prev = nullptr;
    }
};

template<typename T>
class PriorityQueue {
private:
    int _size;
    PriorityQueueEntry<T> *_head;
    PriorityQueueEntry<T> *_tail;
public:
    PriorityQueue();
    void insert(T value, float priority);
    T extractMin();
    T extractMax();
    void remove(T value);
    void decreaseKey(T value, float newPriority) {
        remove(value);
        insert(value, newPriority);
    }
    int getSize() {
        return _size;
    }
};

template <typename T>
PriorityQueue<T>::PriorityQueue() {
    _head = nullptr;
    _tail = nullptr;
    _size = 0;
}

template <typename T>
void PriorityQueue<T>::insert(T value, float priority) {
    if (_size == 0) { // List is empty
        _head = new PriorityQueueEntry<T>(value, priority);
        _tail = _head;
        _size++;
        return;
    }

    PriorityQueueEntry<T> *newEntry = new PriorityQueueEntry<T>(value, priority);

    if (priority < _head->priority) {
        newEntry->next = _head;
        _head->prev = newEntry;
        _head = newEntry;
    } else if (_tail->priority <= priority) {
        newEntry->prev = _tail;
        _tail = newEntry;
        newEntry->prev->next = newEntry;
    } else {
        PriorityQueueEntry<T> *compareEntry = _head;

        while (compareEntry != nullptr && compareEntry->priority < priority) {
            compareEntry = compareEntry->next;
        }

        if (compareEntry == nullptr)
            throw MyExecption("PriorityQueue: Unable to insert an entry.");

        newEntry->prev = compareEntry->prev;
        newEntry->next = compareEntry;
        compareEntry->prev = newEntry;
        newEntry->prev->next = newEntry;
        //TODO: Überlegen mit nur 1 Element...
    }
    _size += 1;
}

template <typename T>
T PriorityQueue<T>::extractMin() {
    T result = nullptr;

    if (_size == 0)
        throw MyExecption("PriorityQueue is empty");

    result = _head->value;

    if (_size == 1) {
        delete _head;
        _head = nullptr;
        _tail == nullptr;
    } else {
        _head = _head->next;
        delete _head->prev;
        _head->prev = nullptr;
    }
    _size -= 1;
    return result;
}

template <typename T>
T PriorityQueue<T>::extractMax() {
    T result;

    if (_size == 0)
        throw MyExecption("PriorityQueue is empty.");

    result = _tail->value;

    if (_size == 1) {
        delete _tail;
        _tail == nullptr;
        _head == nullptr;
    } else {
        _tail = _tail->prev;
        delete _tail->next;
        _tail->next = nullptr;
    }
    _size--;
    return result;
}

template <typename T>
void PriorityQueue<T>::remove(T value) {
    if (_size == 0)
        throw MyExecption("PriorityQueue is empty");

    if (value == _head->value)
        extractMin();
    else if (value == _tail->value)
        extractMax();
    else {
        PriorityQueueEntry<T> *compareEntry = _head->next;

        while (compareEntry->next != nullptr && compareEntry->value != value) {
            compareEntry = compareEntry->next;
        }

        if (compareEntry->next == nullptr)
            throw MyExecption("PriorityQueue: Error Element couldn't be removed. Does it exist?");

        compareEntry->prev->next = compareEntry->next;
        compareEntry->next->prev = compareEntry->prev;
        delete compareEntry;
        _size -= 1;
    }
}







#endif //OOA4_PRIORITYQUEUE_H
