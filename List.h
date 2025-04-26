#ifndef LIST_H
#define LIST_H

#include "NodePool.h"
#include <functional>
#include <stdexcept>

template<typename T, int NUM_NODES = 2048>
class List {
public:
    static const int NULL_VALUE = NodePool<T, NUM_NODES>::NULL_VALUE;

    List();
    List(const List& other);
    List& operator=(const List& other);
    ~List();

    bool isEmpty() const;
    void traverse(const std::function<void(const T&)>& visit) const;
    int size() const;
    int find(const T& item) const;
    void clear();

    void insertFront(const T& item);
    void deleteFront();
    void insertAfter(int pos, const T& item);
    void deleteAfter(int pos);
    void insertSorted(const T& item);
    bool remove(const T& item);

    int getFreeListHead() const;

private:
    void insertBack(const T& item);

    NodePool<T, NUM_NODES> pool;
    int                    head;
};

#endif
