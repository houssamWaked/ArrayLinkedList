#include "List.h"
#include <stdexcept>
#include <functional>
#include <string>

template<typename T, int NUM_NODES>
List<T, NUM_NODES>::List()
  : pool(), head(NULL_VALUE) {}

template<typename T, int NUM_NODES>
List<T, NUM_NODES>::List(const List& other)
  : pool(), head(NULL_VALUE) {
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
void List<T, NUM_NODES>::traverse(const std::function<void(const T&)>& visit) const {
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
        throw std::underflow_error("List::deleteFront() on empty list");
    int old = head;
    head = pool.data()[old].next;
    pool.deleteNode(old);
}

template<typename T, int NUM_NODES>
void List<T, NUM_NODES>::insertAfter(int pos, const T& item) {
    if (pos == NULL_VALUE || pos < 0 || pos >= NUM_NODES)
        throw std::out_of_range("List::insertAfter invalid position");
    int idx = pool.newNode();
    pool.data()[idx].data = item;
    pool.data()[idx].next = pool.data()[pos].next;
    pool.data()[pos].next = idx;
}

template<typename T, int NUM_NODES>
void List<T, NUM_NODES>::deleteAfter(int pos) {
    if (pos == NULL_VALUE || pos < 0 || pos >= NUM_NODES)
        throw std::out_of_range("List::deleteAfter invalid position");
    int tgt = pool.data()[pos].next;
    if (tgt == NULL_VALUE)
        throw std::out_of_range("List::deleteAfter no successor");
    pool.data()[pos].next = pool.data()[tgt].next;
    pool.deleteNode(tgt);
}

template<typename T, int NUM_NODES>
void List<T, NUM_NODES>::insertBack(const T& item) {
    if (isEmpty()) {
        insertFront(item);
    } else {
        int ptr = head;
        while (pool.data()[ptr].next != NULL_VALUE)
            ptr = pool.data()[ptr].next;
        insertAfter(ptr, item);
    }
}

template<typename T, int NUM_NODES>
void List<T, NUM_NODES>::insertSorted(const T& item) {
    if (isEmpty() || item < pool.data()[head].data) {
        insertFront(item);
    } else {
        int prev = head, curr = pool.data()[prev].next;
        while (curr != NULL_VALUE && pool.data()[curr].data < item) {
            prev = curr; curr = pool.data()[prev].next;
        }
        insertAfter(prev, item);
    }
}

template<typename T, int NUM_NODES>
bool List<T, NUM_NODES>::remove(const T& item) {
    if (isEmpty()) return false;
    if (pool.data()[head].data == item) {
        deleteFront(); return true;
    }
    int prev = head, curr = pool.data()[prev].next;
    while (curr != NULL_VALUE && pool.data()[curr].data != item) {
        prev = curr; curr = pool.data()[prev].next;
    }
    if (curr == NULL_VALUE) return false;
    deleteAfter(prev);
    return true;
}

template<typename T, int NUM_NODES>
int List<T, NUM_NODES>::getFreeListHead() const {
    return pool.getFreeListHead();
}


template class List<std::string, 2048>;
