#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <ostream>
#include <stack>
#include <vector>
#include "heapElement.hpp"

#ifndef HEAPHEADER
#define HEAPHEADER

class heap {

    public:

        std::vector<std::shared_ptr<heapElement>> fringeHeap;
        int heapSize;

        heap(int heapSize) {

            fringeHeap = std::vector<std::shared_ptr<heapElement>>(heapSize);
            this->heapSize = heapSize;
        }

        void AddToHeap(int node, int destinationNode, int weight) {

            // create a unique pointer pointing to a new heapElement
            std::shared_ptr<heapElement> newHeapElement = std::make_shared<heapElement>(destinationNode, node, weight);

            fringeHeap.push_back(newHeapElement);
            BottomUpHeapify();
            ++heapSize;
        }

        std::vector<std::shared_ptr<heapElement>> getHeap() {

            return fringeHeap;
        }

        // !! both heapifies run in log(n) time
        void BottomUpHeapify() {

            int index = fringeHeap.size() - 1;
            if(index != 0) {

                while(index != 0 && fringeHeap.at(index)->weight < fringeHeap.at(((index + 1) / 2) - 1)->weight) {

                    std::shared_ptr<heapElement> placeholder = fringeHeap.at(index);
                    fringeHeap.at(index) = fringeHeap.at(((index + 1) / 2) - 1);
                    fringeHeap.at(((index + 1) / 2) - 1) = placeholder;

                    index = ((index + 1) / 2) - 1;
                }
            }
        }

        void TopDownHeapify() {

            if(heapSize != 0) {

                int index = 0;
                while(fringeHeap.at(index)->weight > fringeHeap.at(((index + 1) * 2) - 1)->weight || 
                    fringeHeap.at(index)->weight > fringeHeap.at((index + 1) * 2)->weight) {

                    if(fringeHeap.at(((index + 1) * 2) - 1)->weight > fringeHeap.at((index + 1) * 2)->weight) {

                        std::shared_ptr<heapElement> placeholder = fringeHeap.at(index);
                        fringeHeap.at(index) = fringeHeap.at((((index + 1) * 2) - 1) + 1);
                        fringeHeap.at((index + 1) * 2) = placeholder;
                    }
                    else {

                        std::shared_ptr<heapElement> placeholder = fringeHeap.at(index);
                        fringeHeap.at(index) = fringeHeap.at(((index + 1) * 2) - 1);
                        fringeHeap.at(((index + 1) * 2) - 1) = placeholder;
                    }
                }
            }
        }

        std::shared_ptr<heapElement> DeleteMin() {

            std::shared_ptr<heapElement> min = fringeHeap.at(0);

            // implement pop_front method for vector
            for(int i = 1; i < fringeHeap.size() - 1; i++) {

                fringeHeap.at(i - 1) = fringeHeap.at(i);
            }

            fringeHeap.pop_back();

            // heapify to restore heap properties
            --heapSize;
            TopDownHeapify();

            return min;
        }
};
#endif