#include <iostream>
#include <cmath> /* islessequal */
#include "SDLL.h"

/******************** DEFINITIONS ********************/

/******************** MACROS ********************/


/******************** PROTOTYPES ********************/
bool validArguments(int dataType, Point_t& maxCoordinates);

/******************** CONSTRUCTOR ********************/
SDLL_Node::SDLL_Node(int dataType, Point_t& maxCoordinates,
    SDLL_Node* nextNode, SDLL_Node* prevNode) {
    this->type = INVALID;
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
            break;

        case SDLL_DT_FOOD:
            this->data.food = new Food(maxCoordinates);
            if (this->data.food == NULL) {
                std::cout 
                    << "Could not allocate memory for Food."
                    << std::endl;
                return;
            }

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
    this->dataType = INVALID;
    this->head = NULL;
    this->tail = NULL;

    if (validArguments(dataType, maxCoordinates) == false) { return; }
    
    this->head = new SDLL_Node(dataType, maxCoordinates);
    if (this->head == NULL) {
        std::cout << "Could not allocate memory for SDLL head." << std::endl;
        return;
    }
    this->tail = this->head;

    return;
}

/******************** PUBLIC METHODS ********************/
int SDLL_Node::getDataType(void) {
    return this->type;
}

const union SDLL_Node_DataType* SDLL_Node::getData(void) {
    return &(this->data);
}

const SDLL_Node* SDLL_Node::getNextNode(void) {
    return this->next;
}

const SDLL_Node* SDLL_Node::getPrevNode(void) {
    return this->prev;
}



const SDLL_Node* SDLL::getHead(void) {
    return this->head;
}

const SDLL_Node* SDLL::getTail(void) {
    return this->tail;
}

/******************** PRIVATE METHODS ********************/

/******************** STATIC FUNCTIONS ********************/
bool validArguments(int dataType, Point_t& maxCoordinates) {
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
