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

        void AddToHeap(int node, int weight) {

            // create a unique pointer pointing to a new heapElement
            std::shared_ptr newHeapElement = std::make_shared<heapElement>(node, weight);

            fringeHeap.push_back(newHeapElement);
            BottomUpHeapify();
            ++heapSize;
        }


        // !! both heapifies run in log(n) time
        void BottomUpHeapify() {

            int index = fringeHeap.size() + 1;
            while(fringeHeap.at(index)->weight < fringeHeap.at(index / 2)->weight) {

                std::shared_ptr placeholder = fringeHeap.at(index - 1);
                fringeHeap.at(index - 1) = fringeHeap.at((index / 2) - 1);
                fringeHeap.at((index / 2) - 1) = placeholder;
            }
        }

        void TopDownHeapify() {

            int index = 1;
            while(fringeHeap.at(index - 1)->weight > fringeHeap.at(index * 2)->weight || 
                fringeHeap.at(index - 1)->weight > fringeHeap.at((index * 2) + 1)->weight) {

                if(fringeHeap.at(index * 2)->weight > fringeHeap.at((index * 2) + 1)->weight) {

                    std::shared_ptr placeholder = fringeHeap.at(index - 1);
                    fringeHeap.at(index - 1) = fringeHeap.at((index * 2) + 1);
                    fringeHeap.at((index * 2) + 1) = placeholder;
                }
                else {

                    std::shared_ptr placeholder = fringeHeap.at(index - 1);
                    fringeHeap.at(index - 1) = fringeHeap.at(index * 2);
                    fringeHeap.at(index * 2) = placeholder;
                }
            }
        }

        std::shared_ptr<heapElement> DeleteMin() {

            std::shared_ptr min = fringeHeap.at(0);

            // implement pop_front method for vector
            for(int i = 1; i < fringeHeap.size() - 1; i++) {

                fringeHeap.at(i - 1) = fringeHeap.at(i);
            }

            fringeHeap.pop_back();

            // heapify to restore heap properties
            TopDownHeapify();
            --heapSize;

            return min;
        }
};
#endif