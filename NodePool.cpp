#include "NodePool.h"
#include <stdexcept>
#include <string>

template<typename ElementType, int NUM_NODES>
NodePool<ElementType, NUM_NODES>::NodePool() {
    initializePool();
}

template<typename ElementType, int NUM_NODES>
void NodePool<ElementType, NUM_NODES>::initializePool() {
    for (int i = 0; i < NUM_NODES - 1; ++i) {
        pool[i].next = i + 1;
    }
    pool[NUM_NODES - 1].next = NULL_VALUE;
    freeListHead = 0;
}

template<typename ElementType, int NUM_NODES>
int NodePool<ElementType, NUM_NODES>::newNode() {
    if (freeListHead == NULL_VALUE)
        throw std::overflow_error("NodePool: out of free nodes");
    int idx = freeListHead;
    freeListHead = pool[idx].next;
    pool[idx].next = NULL_VALUE;
    return idx;
}

template<typename ElementType, int NUM_NODES>
void NodePool<ElementType, NUM_NODES>::deleteNode(int idx) {
    if (idx < 0 || idx >= NUM_NODES)
        throw std::out_of_range("NodePool: deleteNode index out of range");
    pool[idx].next = freeListHead;
    freeListHead = idx;
}

template<typename ElementType, int NUM_NODES>
typename NodePool<ElementType, NUM_NODES>::NodeType*
NodePool<ElementType, NUM_NODES>::data() {
    return pool;
}

template<typename ElementType, int NUM_NODES>
const typename NodePool<ElementType, NUM_NODES>::NodeType*
NodePool<ElementType, NUM_NODES>::data() const {
    return pool;
}

template<typename ElementType, int NUM_NODES>
int NodePool<ElementType, NUM_NODES>::getFreeListHead() const {
    return freeListHead;
}


template class NodePool<std::string, 2048>;
