#ifndef SDLL_H
#define SDLL_H  1

#include "Coordinates.h"
#include "Blob.h"
#include "Food.h"

enum dataTypes {
    INVALID = -1,
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
        SDLL_Node* next = NULL, SDLL_Node* prev = NULL);

    int getDataType(void);
    const union SDLL_Node_DataType* getData(void);
    const SDLL_Node* getNextNode(void);
    const SDLL_Node* getPrevNode(void);

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


    // This functions return true on success and false on failure.
    bool append(void); // New node after tail.
    bool destroy(void); // Destroy all nodes.
    bool insertAfter(SDLL_Node& node); // Create a new node after _node_.
    bool insertBefore(SDLL_Node& node); // Create a new node before _node_.
    bool pop(void); // Remove current tail.
    bool remove(SDLL_Node& node); // Remove _node_ from list.

    const SDLL_Node* getHead(void);
    const SDLL_Node* getTail(void);

private:
    int dataType;

    SDLL_Node* head;
    SDLL_Node* tail; // To pop and append faster :)
};

#endif /* ! SDLL_H */
