#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <ostream>
#include <stack>
#include <vector>

#ifndef HEAPELEMENT
#define HEAPELEMENT

class heapElement {

    public:

        int weight;
        int destinationNode;

        heapElement(int destinationNode, int weight) {

            this->weight = weight;
            this->destinationNode = destinationNode;
        }
};
#endif