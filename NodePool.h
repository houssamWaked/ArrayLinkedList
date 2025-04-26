#ifndef NODEPOOL_H
#define NODEPOOL_H

#include <stdexcept>

template<typename ElementType, int NUM_NODES = 2048>
class NodePool {
public:
    static const int NULL_VALUE = -1;

    struct NodeType {
        ElementType data;
        int next;
    };

    NodePool();
    void initializePool();
    int newNode();
    void deleteNode(int idx);
    NodeType* data();
    const NodeType* data() const;
    int getFreeListHead() const;

private:
    NodeType pool[NUM_NODES];
    int freeListHead;
};

#endif
