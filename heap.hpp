#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <ostream>
#include <stack>
#include <vector>

#ifndef HEAPHEADER
#define HEAPHEADER
class heap {

    public:

        heap(uint headVert, size_t graphSize) {

            head = std::make_shared<link>(headVert);
        }

        void addToHeap(uint vert) {

            
        }

        uint deleteMin() {

            return 1;
        }
};