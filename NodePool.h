/*-- NodePool.h ------------------------------------------------------------

  This header file defines the NodePool class for managing a pool of nodes.
  Basic operations are:
     Constructor:        Initializes the node pool.
     initializePool:     Initializes the free list and nodes.
     newNode:            Allocates a new node from the pool.
     deleteNode:         Recycles a node back into the free list.
     data:               Accessor to the node pool (mutable).
     data (const):       Accessor to the node pool (immutable).
     getFreeListHead:    Retrieves the index of the first free node.
-------------------------------------------------------------------------*/

#ifndef NODEPOOL_H
#define NODEPOOL_H
using namespace std;

#include <stdexcept>  // For exception handling

template<typename ElementType, int NUM_NODES = 2048>
class NodePool {
public:
    static const int NULL_VALUE = -1;  // Sentinel value indicating end of list

    // NodeType stores the data and a pointer to the next node in the pool
    struct NodeType {
        ElementType data;  // Data to be stored in the node
        int next;          // Index of the next free node in the pool
    };

    /***** Function Members ******/

    /***** Constructor *****/
    NodePool();
    /*----------------------------------------------------------------------
      Constructor to initialize the node pool and set up the free list.
      Precondition:  None
      Postcondition: A NodePool object has been created, and the pool
                     is initialized with free nodes.
    ----------------------------------------------------------------------*/

    /***** initializePool *****/
    void initializePool();
    /*----------------------------------------------------------------------
      Initializes the free list by linking all nodes together.
      Precondition:  None
      Postcondition: The node pool has been initialized, and freeListHead
                     points to the first free node.
    ----------------------------------------------------------------------*/

    /***** newNode *****/
    int newNode();
    /*----------------------------------------------------------------------
      Allocates a new node from the pool.
      Precondition:  There must be at least one free node in the pool.
      Postcondition: A new node has been allocated and removed from the free list.
                     Returns the index of the newly allocated node.
    ----------------------------------------------------------------------*/

    /***** deleteNode *****/
    void deleteNode(int idx);
    /*----------------------------------------------------------------------
      Recycles a node back into the pool and returns it to the free list.
      Precondition:  The index must be valid (0 <= idx < NUM_NODES).
      Postcondition: The node at the given index has been returned to the free list.
    ----------------------------------------------------------------------*/

    /***** data (mutable) *****/
    NodeType* data();
    /*----------------------------------------------------------------------
      Provides access to the node pool.
      Precondition:  None
      Postcondition: Returns a pointer to the array of nodes, allowing modification.
    ----------------------------------------------------------------------*/

    /***** data (immutable) *****/
    const NodeType* data() const;
    /*----------------------------------------------------------------------
      Provides access to the node pool (read-only).
      Precondition:  None
      Postcondition: Returns a pointer to the array of nodes, but access to
                     data is read-only.
    ----------------------------------------------------------------------*/

    /***** getFreeListHead *****/
    int getFreeListHead() const;
    /*----------------------------------------------------------------------
      Retrieves the index of the first free node in the pool.
      Precondition:  None
      Postcondition: Returns the index of the first free node (or NULL_VALUE if none).
    ----------------------------------------------------------------------*/

private:
    NodeType pool[NUM_NODES];   // Array of nodes in the pool
    int freeListHead;           // Index of the first free node in the pool

};  //--- end of NodePool class

/* IMPLEMENTATION STARTS HERE */

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
        throw overflow_error("NodePool: out of free nodes");
    int idx = freeListHead;
    freeListHead = pool[idx].next;
    pool[idx].next = NULL_VALUE;
    return idx;
}

template<typename ElementType, int NUM_NODES>
void NodePool<ElementType, NUM_NODES>::deleteNode(int idx) {
    if (idx < 0 || idx >= NUM_NODES)
        throw out_of_range("NodePool: deleteNode index out of range");
    pool[idx].next = freeListHead;
    freeListHead = idx;
}

template<typename ElementType, int NUM_NODES>
typename NodePool<ElementType, NUM_NODES>::NodeType* NodePool<ElementType, NUM_NODES>::data() {
    return pool;
}

template<typename ElementType, int NUM_NODES>
const typename NodePool<ElementType, NUM_NODES>::NodeType* NodePool<ElementType, NUM_NODES>::data() const {
    return pool;
}

template<typename ElementType, int NUM_NODES>
int NodePool<ElementType, NUM_NODES>::getFreeListHead() const {
    return freeListHead;
}

#endif // NODEPOOL_H
