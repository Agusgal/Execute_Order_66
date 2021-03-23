#ifndef SDLL_H
#define SDLL_H  1

#include "Coordinates.h"
#include "Blob.h"
#include "Food.h"

enum dataTypes {
    SDLL_DT_INVALID = -1,
    SDLL_DT_BLOB = 0,
    SDLL_DT_FOOD,
    NDATATYPES
};

union SDLL_Node_DataType {
    Blob* blob;
    Food* food;
};

class SDLL_Node {
public:
    /*
     * Create a node. Call this only from SDLL class!
     * 
     * next: Pointer to next node (NULL if non existing).
     * prev: Pointer to previous node (NULL if non existing).
     * The last two parameters can be used to create a node in any part
     * of the list.
     */
    SDLL_Node(int dataType, Point_t& maxCoordinates, 
        SDLL_Node* prev = NULL, SDLL_Node* next = NULL);

    int getDataType(void);
    union SDLL_Node_DataType* getData(void);
    SDLL_Node* getNextNode(void);
    SDLL_Node* getPrevNode(void);

    void setNextNode(SDLL_Node* node);
    void setPrevNode(SDLL_Node* node);

    bool destroy(void);
private:
    int type;
    union SDLL_Node_DataType data;

    SDLL_Node* next;
    SDLL_Node* prev;
};

class SDLL {
public:
    /*
     * Create a Simple Doubly Linked List.
     *
     * Needs data of type dataTypes and a Point_t of maximum
     * coordinates for the data instance constructor.
     */
    SDLL(int dataType, Point_t& maxCoordinates);


    // This functions return a pointer to created node.
    SDLL_Node* append(void); // New node after tail.
    SDLL_Node* insertAfter(SDLL_Node* node); // Create a new node after _node_.
    SDLL_Node* insertBefore(SDLL_Node* node); // Create a new node before _node_.

    // This functions return true on success and false on failure.
    bool destroy(void); // Destroy all nodes, head included.
    bool pop(void); // Remove current tail unless the list has only one element.
    bool remove(SDLL_Node* node); // Remove _node_ from list.

    SDLL_Node* getHead(void);
    SDLL_Node* getTail(void);

private:
    // Only enabled when destroying.
    // Allows remove() to destroy the list's head if it's 
    // the only node.
    bool removeHead; 

    int dataType;
    Point_t maximumCoordinates;

    SDLL_Node* head;
    SDLL_Node* tail; // To pop and append faster :)
};

#endif /* ! SDLL_H */
