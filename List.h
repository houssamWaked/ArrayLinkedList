/*-- List.h ---------------------------------------------------------------
 
  This header file defines the List class for managing a linked list of nodes.
  Basic operations are:
     Constructor:        Initializes an empty list.
     isEmpty:            Checks if the list is empty.
     traverse:           Traverses and applies a function to each element.
     size:               Returns the number of elements in the list.
     find:               Finds a node by its value.
     clear:              Clears the list by deleting all elements.
     insertFront:        Inserts an element at the front of the list.
     deleteFront:        Deletes the front element of the list.
     insertAfter:        Inserts an element after a given position.
     deleteAfter:        Deletes an element after a given position.
     insertBack:         Inserts an element at the end of the list.
     insertSorted:       Inserts an element in sorted order.
     remove:             Removes a node by its value.
     getFreeListHead:    Returns the index of the first free node in the pool.
     printList():        Prints to std::cout.
     operator<<:         Prints to any std::ostream.
-------------------------------------------------------------------------*/

#ifndef LIST_H
#define LIST_H

#include "NodePool.h"
#include <functional>
#include <stdexcept>
#include <iostream>
#include <string>

using namespace std;

template<typename T, int NUM_NODES = 2048>
class List {
public:
    static const int NULL_VALUE = NodePool<T, NUM_NODES>::NULL_VALUE;

    // Constructor, copy, assign, destructor
    List();
    List(const List& other);
    List& operator=(const List& other);
    ~List();

    // Core operations
    bool isEmpty() const;
    void traverse(const function<void(const T&)>& visit) const;
    int size() const;
    int find(const T& item) const;
    void clear();

    // Insert/Delete
    void insertFront(const T& item);
    void deleteFront();
    void insertAfter(int pos, const T& item);
    void deleteAfter(int pos);
    void insertSorted(const T& item);
    bool remove(const T& item);

    // Helpers
    int getFreeListHead() const;

    // Print to cout
    void printList() const;

private:
    // Internal helper
    void insertBack(const T& item);

    NodePool<T, NUM_NODES> pool;
    int head;
};

// Implementation

template<typename T, int NUM_NODES>
List<T, NUM_NODES>::List() : pool(), head(NULL_VALUE) {}

template<typename T, int NUM_NODES>
List<T, NUM_NODES>::List(const List& other) : pool(), head(NULL_VALUE) {
    other.traverse([this](const T& v){ insertBack(v); });
}

template<typename T, int NUM_NODES>
List<T, NUM_NODES>& List<T, NUM_NODES>::operator=(const List& other) {
    if (this != &other) {
        clear();
        other.traverse([this](const T& v){ insertBack(v); });
    }
    return *this;
}

template<typename T, int NUM_NODES>
List<T, NUM_NODES>::~List() {
    clear();
}

template<typename T, int NUM_NODES>
bool List<T, NUM_NODES>::isEmpty() const {
    return head == NULL_VALUE;
}

template<typename T, int NUM_NODES>
void List<T, NUM_NODES>::traverse(const function<void(const T&)>& visit) const {
    int ptr = head;
    while (ptr != NULL_VALUE) {
        visit(pool.data()[ptr].data);
        ptr = pool.data()[ptr].next;
    }
}

template<typename T, int NUM_NODES>
int List<T, NUM_NODES>::size() const {
    int count = 0, ptr = head;
    while (ptr != NULL_VALUE) {
        ++count;
        ptr = pool.data()[ptr].next;
    }
    return count;
}

template<typename T, int NUM_NODES>
int List<T, NUM_NODES>::find(const T& item) const {
    int ptr = head;
    while (ptr != NULL_VALUE) {
        if (pool.data()[ptr].data == item) return ptr;
        ptr = pool.data()[ptr].next;
    }
    return NULL_VALUE;
}

template<typename T, int NUM_NODES>
void List<T, NUM_NODES>::clear() {
    while (!isEmpty()) deleteFront();
}

template<typename T, int NUM_NODES>
void List<T, NUM_NODES>::insertFront(const T& item) {
    int idx = pool.newNode();
    pool.data()[idx].data = item;
    pool.data()[idx].next = head;
    head = idx;
}

template<typename T, int NUM_NODES>
void List<T, NUM_NODES>::deleteFront() {
    if (isEmpty())
        throw underflow_error("List::deleteFront() on empty list");
    int old = head;
    head = pool.data()[old].next;
    pool.deleteNode(old);
}

template<typename T, int NUM_NODES>
void List<T, NUM_NODES>::insertAfter(int pos, const T& item) {
    if (pos == NULL_VALUE || pos < 0 || pos >= NUM_NODES)
        throw out_of_range("List::insertAfter invalid position");
    int idx = pool.newNode();
    pool.data()[idx].data = item;
    pool.data()[idx].next = pool.data()[pos].next;
    pool.data()[pos].next = idx;
}

template<typename T, int NUM_NODES>
void List<T, NUM_NODES>::deleteAfter(int pos) {
    if (pos == NULL_VALUE || pos < 0 || pos >= NUM_NODES)
        throw out_of_range("List::deleteAfter invalid position");
    int tgt = pool.data()[pos].next;
    if (tgt == NULL_VALUE)
        throw out_of_range("List::deleteAfter no successor");
    pool.data()[pos].next = pool.data()[tgt].next;
    pool.deleteNode(tgt);
}

template<typename T, int NUM_NODES>
void List<T, NUM_NODES>::insertBack(const T& item) {
    if (isEmpty())
        insertFront(item);
    else {
        int ptr = head;
        while (pool.data()[ptr].next != NULL_VALUE)
            ptr = pool.data()[ptr].next;
        insertAfter(ptr, item);
    }
}

template<typename T, int NUM_NODES>
void List<T, NUM_NODES>::insertSorted(const T& item) {
    if (isEmpty() || item < pool.data()[head].data)
        insertFront(item);
    else {
        int prev = head, curr = pool.data()[prev].next;
        while (curr != NULL_VALUE && pool.data()[curr].data < item) {
            prev = curr;
            curr = pool.data()[prev].next;
        }
        insertAfter(prev, item);
    }
}

template<typename T, int NUM_NODES>
bool List<T, NUM_NODES>::remove(const T& item) {
    if (isEmpty()) return false;
    if (pool.data()[head].data == item) {
        deleteFront();
        return true;
    }
    int prev = head, curr = pool.data()[prev].next;
    while (curr != NULL_VALUE && pool.data()[curr].data != item) {
        prev = curr;
        curr = pool.data()[prev].next;
    }
    if (curr == NULL_VALUE) return false;
    deleteAfter(prev);
    return true;
}

template<typename T, int NUM_NODES>
int List<T, NUM_NODES>::getFreeListHead() const {
    return pool.getFreeListHead();
}

template<typename T, int NUM_NODES>
void List<T, NUM_NODES>::printList() const {
    cout << "List contents: ";
    traverse([](const T& s) {
        cout << s << " ";
    });
    cout << "\nFree-list head index: " << pool.getFreeListHead() << "\n";
}

// Provide operator<< as a standalone template (must be after the class)
template<typename T, int NUM_NODES>
ostream& operator<<(ostream& os, const List<T, NUM_NODES>& lst) {
    // reuse printList logic but direct to os
    lst.traverse([&os](const T& s) {
        os << s << " ";
    });
    os << "\nFree-list head index: " << lst.getFreeListHead() << "\n";
    return os;
}

#endif // LIST_H
