#include <iostream>
#include <cmath> /* islessequal */
#include "SDLL.h"

/******************** DEFINITIONS ********************/

/******************** MACROS ********************/


/******************** PROTOTYPES ********************/
static bool validArguments(int dataType, Point_t& maxCoordinates);

/******************** CONSTRUCTOR ********************/
SDLL_Node::SDLL_Node(int dataType, Point_t& maxCoordinates,
    SDLL_Node* prevNode, SDLL_Node* nextNode) {
    this->type = SDLL_DT_INVALID;
    this->data = { 0 };
    this->next = NULL;
    this->prev = NULL;

    if (validArguments(dataType, maxCoordinates) == false) { return; }

    switch (dataType) {
        case SDLL_DT_BLOB:
            this->data.blob = new Blob(maxCoordinates);
            if (this->data.blob == NULL) {
                std::cout 
                    << "Could not allocate memory for Blob."
                    << std::endl;
                return;
            }
            this->type = SDLL_DT_BLOB;
            break;

        case SDLL_DT_FOOD:
            this->data.food = new Food(maxCoordinates);
            if (this->data.food == NULL) {
                std::cout 
                    << "Could not allocate memory for Food."
                    << std::endl;
                return;
            }
            this->type = SDLL_DT_FOOD;

            break;

        default:
            return;
            break;
    }

    this->next = nextNode;
    this->prev = prevNode;

    return;
}

SDLL::SDLL(int dataType, Point_t& maxCoordinates) {
    this->removeHead = false;
    this->dataType = SDLL_DT_INVALID;
    this->maximumCoordinates = { 0 };
    this->head = NULL;
    this->tail = NULL;

    if (validArguments(dataType, maxCoordinates) == false) { return; }
    
    this->head = new SDLL_Node(dataType, maxCoordinates);
    if (this->head == NULL) {
        std::cout << "Could not allocate memory for SDLL head." << std::endl;
        return;
    }
    this->tail = this->head;

    this->dataType = dataType;
    this->maximumCoordinates.x = maxCoordinates.x;
    this->maximumCoordinates.y = maxCoordinates.y;

    return;
}

/******************** PUBLIC METHODS ********************/
int SDLL_Node::getDataType(void) {
    return this->type;
}

union SDLL_Node_DataType* SDLL_Node::getData(void) {
    return &(this->data);
}

SDLL_Node* SDLL_Node::getNextNode(void) {
    return this->next;
}

SDLL_Node* SDLL_Node::getPrevNode(void) {
    return this->prev;
}

void SDLL_Node::setNextNode(SDLL_Node* node) {
    this->next = node;
    return;
}

void SDLL_Node::setPrevNode(SDLL_Node* node) {
    this->prev = node;
    return;
}

bool SDLL_Node::destroy(void) {
    switch (this->type) {
        case SDLL_DT_BLOB:
            this->data.blob->die();
            delete this->data.blob;
            break;

        case SDLL_DT_FOOD:
            this->data.food->destroy();
            delete this->data.food;
            break;

        default:
            return false;
            break;
    }

    this->next = NULL;
    this->prev = NULL;

    return true;
}

SDLL_Node* SDLL::append(void) {
    return this->insertAfter(this->tail);
}

SDLL_Node* SDLL::insertAfter(SDLL_Node* node) {
    if (node == NULL) {
        std::cout << "Recieved NULL pointer." << std::endl;
        return NULL;
    }

    SDLL_Node* newNode = new SDLL_Node(
                                    this->dataType, this->maximumCoordinates,
                                    node, node->getNextNode());
    if (newNode == NULL) {
        std::cout << "Could not allocate memory for SDLL node." << std::endl;
        return NULL;
    }

    // NODE --> NEWNODE --> NODE_EX_NEW
    if (node->getNextNode() == NULL && node == this->tail) {
        this->tail = newNode;
    }
    else {
        // Get NODE_EX_NEW and set _prev_ as NEWNODE
        node->getNextNode()->setPrevNode(newNode);
    }
    // Get NODE and set _next_ as NEWNODE
    node->setNextNode(newNode);
    
    return newNode;
}

SDLL_Node* SDLL::insertBefore(SDLL_Node* node) {
    if (node == NULL) {
        std::cout << "Recieved NULL pointer." << std::endl;
        return NULL;
    }

    SDLL_Node* newNode = new SDLL_Node(
                                    this->dataType, this->maximumCoordinates,
                                    node->getPrevNode(), node);
    if (newNode == NULL) {
        std::cout << "Could not allocate memory for SDLL node." << std::endl;
        return NULL;
    }

    
    // NODE_EX_PREV --> NEWNODE --> NODE
    if (node->getPrevNode() == NULL && node == this->head) {
        this->head = newNode;
    }
    else {
        // Get NODE_EX_PREV and set _next_ as NEWNODE
        node->getPrevNode()->setNextNode(newNode);
    }
    // Get NODE and set _prev_ as NEWNODE
    node->setPrevNode(newNode);

    return newNode;
}

bool SDLL::destroy(void) {
    bool noErrorPoping = true;

    while (this->head != this->tail) {
        noErrorPoping = this->pop();
        
        if (noErrorPoping == false)
        {
            break;
        }
    }

    this->removeHead = true;
    noErrorPoping = this->remove(this->head);
    if (noErrorPoping == true) {
        this->removeHead = false;
        this->dataType = SDLL_DT_INVALID;
        this->maximumCoordinates.x = 0;
        this->maximumCoordinates.y = 0;
        this->head = NULL;
        this->tail = NULL;
    }

    return noErrorPoping;
}

bool SDLL::pop(void) {
    if (this->head == this->tail) { return false; }
    return this->remove(this->tail);
}

bool SDLL::remove(SDLL_Node* node) {
    if (node == NULL) {
        std::cout << "Recieved NULL pointer." << std::endl;
        return false;
    }
    else if  (this->head == this->tail && node == this->head && removeHead == false) {
        std::cout 
            << "Head in a single node element cannot be removed without destroying the list."
            << std::endl;
        return false;
    }
    
    if (removeHead == false) {
        // Remove pointers to this node from list
        SDLL_Node* currentPrev = node->getPrevNode();
        SDLL_Node* currentNext = node->getNextNode();

        if (currentPrev != NULL) {
            currentPrev->setNextNode(node->getNextNode());
        }
        else {
            this->head = currentNext; // Prev was NULL --> we're removing head
        }


        if (currentNext != NULL) {
            currentNext->setPrevNode(node->getPrevNode());
        }
        else {
            this->tail = currentPrev; // Next was NULL --> we're removing tail
        }
    }

    // Destroy node
    if (node->destroy() == true) {
        delete node;
    }
    else {
        // Something failde. Restore pointers
        node->getPrevNode()->setNextNode(node);
        node->getNextNode()->setPrevNode(node);
        return false;
    }

    return true;
}

SDLL_Node* SDLL::getHead(void) {
    return this->head;
}

SDLL_Node* SDLL::getTail(void) {
    return this->tail;
}

/******************** PRIVATE METHODS ********************/

/******************** STATIC FUNCTIONS ********************/
static bool validArguments(int dataType, Point_t& maxCoordinates) {
    if (islessequal(maxCoordinates.x, 0.0) || islessequal(maxCoordinates.y, 0.0)) {
        std::cout << "Maximum coordinates must be greater than zero." << std::endl;
        return false;
    }
    else if (dataType != SDLL_DT_BLOB && dataType != SDLL_DT_FOOD) {
        std::cout << "Invalid data type for SDLL." << std::endl;
        return false;
    }
    return true;
}
