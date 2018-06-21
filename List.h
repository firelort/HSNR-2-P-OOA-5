//
// Created by hartings on 23.05.18.
//

#ifndef OOA3_LIST_H
#define OOA3_LIST_H

#include "Execption.h"
#include <iostream>
using namespace std;

template <class T>
class Entry {
public:
    T _value;
    Entry<T> *_next;
    Entry(T value) {
        _value = value;
        _next = nullptr;
    }
};

template <class T>
class List{
private:
    Entry<T> *_head;
    Entry<T> *_tail;
    unsigned int listSize;
public:
    List<T>(){
        _head = nullptr;
        _tail = nullptr;
        listSize = 0;
    }

    unsigned int getListSize(){
        return listSize;
    }

    T getValueAtPos(unsigned int pos){
        Entry<T> *referenceEntry;
        referenceEntry = _head;
        unsigned int count = 0;

        if(listSize < pos)
            throw MyExecption("Error: Out of bounds.");

        while (count < pos) {
            referenceEntry = referenceEntry->_next;
            count += 1;
        }
        return referenceEntry->_value;
    }

    void insertNewEntry(T value){
        Entry<T> *entry = new Entry<T>(value);
        if(_head == nullptr){
            _head = entry;
            _tail = entry;
        } else {
            _tail->_next = entry;
            _tail = entry;
        }
        listSize += 1;
    }

   Entry<T> *getHeadElement(void) {
        return _head;
    }
};

#endif //OOA3_LIST_H
