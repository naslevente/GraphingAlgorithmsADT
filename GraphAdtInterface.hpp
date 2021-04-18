#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <ostream>
#include <stack>
#include <vector>

#ifndef INTERFACE
#define INTERFACE

class GraphAdtInterface {

    protected:

        uint graphSize;
        uint position = 0;

        std::vector<int> low;

    public:

        virtual bool AddToList(int, int) = 0;
        virtual bool AddToMatrix(int, int) = 0;

        void AddEdge(int firstNode, int secondNode) {

            if(!AddToList(firstNode, secondNode) || !AddToMatrix(firstNode, secondNode)) {

                std::cout << "failed to add the edge to the graph" << std::endl;
            }
        }
};

#endif