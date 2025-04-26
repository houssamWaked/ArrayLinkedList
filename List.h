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
     printList:          Prints list contents to std::cout.
     operator<<:         Prints list contents to any std::ostream.
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

    /***** Function Members ******/

    /***** Constructor *****/
    List();
    /*----------------------------------------------------------------------
      Constructor for the List class.
      Precondition:  None
      Postcondition: A new empty List object has been created (head is NULL_VALUE).
    ----------------------------------------------------------------------*/

    /***** Copy Constructor *****/
    List(const List& other);
    /*----------------------------------------------------------------------
      Creates a new list as a copy of another list.
      Precondition:  other is a valid List object.
      Postcondition: A new List object is created with the same elements as other.
    ----------------------------------------------------------------------*/

    /***** Assignment Operator *****/
    List& operator=(const List& other);
    /*----------------------------------------------------------------------
      Assigns the contents of another list to this list.
      Precondition:  other is a valid List object.
      Postcondition: This list contains the same elements as other.
                     Returns a reference to this list.
    ----------------------------------------------------------------------*/

    /***** Destructor *****/
    ~List();
    /*----------------------------------------------------------------------
      Destroys the list and releases all allocated nodes.
      Precondition:  None
      Postcondition: All nodes have been returned to the pool.
    ----------------------------------------------------------------------*/

    /***** isEmpty *****/
    bool isEmpty() const;
    /*----------------------------------------------------------------------
      Checks if the list is empty.
      Precondition:  None
      Postcondition: Returns true if the list is empty, false otherwise.
    ----------------------------------------------------------------------*/

    /***** traverse *****/
    void traverse(const function<void(const T&)>& visit) const;
    /*----------------------------------------------------------------------
      Applies a function to each element in the list.
      Precondition:  visit is a valid function object.
      Postcondition: visit has been applied to each element in order.
    ----------------------------------------------------------------------*/

    /***** size *****/
    int size() const;
    /*----------------------------------------------------------------------
      Returns the number of elements in the list.
      Precondition:  None
      Postcondition: Returns the count of elements in the list.
    ----------------------------------------------------------------------*/

    /***** find *****/
    int find(const T& item) const;
    /*----------------------------------------------------------------------
      Searches for an item in the list.
      Precondition:  None
      Postcondition: Returns the index of the item if found, NULL_VALUE otherwise.
    ----------------------------------------------------------------------*/

    /***** clear *****/
    void clear();
    /*----------------------------------------------------------------------
      Removes all elements from the list.
      Precondition:  None
      Postcondition: The list is empty (head is NULL_VALUE).
    ----------------------------------------------------------------------*/

    /***** insertFront *****/
    void insertFront(const T& item);
    /*----------------------------------------------------------------------
      Inserts an item at the front of the list.
      Precondition:  None
      Postcondition: The item is the new first element of the list.
    ----------------------------------------------------------------------*/

    /***** deleteFront *****/
    void deleteFront();
    /*----------------------------------------------------------------------
      Removes the first element from the list.
      Precondition:  The list is not empty.
      Postcondition: The first element is removed from the list.
      Throws:        underflow_error if list is empty.
    ----------------------------------------------------------------------*/

    /***** insertAfter *****/
    void insertAfter(int pos, const T& item);
    /*----------------------------------------------------------------------
      Inserts an item after a specified position.
      Precondition:  pos is a valid index in the list.
      Postcondition: The item is inserted after the specified position.
      Throws:        out_of_range if pos is invalid.
    ----------------------------------------------------------------------*/

    /***** deleteAfter *****/
    void deleteAfter(int pos);
    /*----------------------------------------------------------------------
      Removes the item after a specified position.
      Precondition:  pos is a valid index with a successor.
      Postcondition: The item after pos is removed from the list.
      Throws:        out_of_range if pos is invalid or has no successor.
    ----------------------------------------------------------------------*/

    /***** insertSorted *****/
    void insertSorted(const T& item);
    /*----------------------------------------------------------------------
      Inserts an item in sorted order (ascending).
      Precondition:  Type T supports operator<.
      Postcondition: The item is inserted in the correct sorted position.
    ----------------------------------------------------------------------*/

    /***** remove *****/
    bool remove(const T& item);
    /*----------------------------------------------------------------------
      Removes the first occurrence of an item from the list.
      Precondition:  None
      Postcondition: Returns true if item was found and removed, false otherwise.
    ----------------------------------------------------------------------*/

    /***** getFreeListHead *****/
    int getFreeListHead() const;
    /*----------------------------------------------------------------------
      Returns the index of the first available node in the pool.
      Precondition:  None
      Postcondition: Returns the free list head index or NULL_VALUE if empty.
    ----------------------------------------------------------------------*/

    /***** printList *****/
    void printList() const;
    /*----------------------------------------------------------------------
      Prints the list contents to standard output.
      Precondition:  None
      Postcondition: List elements and free list head are printed to cout.
    ----------------------------------------------------------------------*/

private:
    /***** insertBack *****/
    void insertBack(const T& item);
    /*----------------------------------------------------------------------
      Helper function to insert an item at the end of the list.
      Precondition:  None
      Postcondition: The item is added as the last element of the list.
    ----------------------------------------------------------------------*/

    NodePool<T, NUM_NODES> pool;  // Node pool for memory management
    int head;                     // Index of the first node in the list
};

// (Implementation remains exactly the same as in your original file)

#endif // LIST_H