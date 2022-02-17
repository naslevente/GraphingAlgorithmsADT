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

        std::vector<std::shared_ptr<heapElement>> getHeap() const {

            return fringeHeap;
        }

        // !! both heapifies run in log(n) time
        void BottomUpHeapify() {

            int index = fringeHeap.size() - 1;
            if(index != 0) {

                while(index != 0 && fringeHeap.at(index)->weight < fringeHeap.at(index / 2)->weight) {

                    std::shared_ptr<heapElement> placeholder = fringeHeap.at(index);
                    fringeHeap.at(index) = std::move(fringeHeap.at(index / 2));
                    fringeHeap.at(index / 2) = std::move(placeholder);

                    index /= 2;
                }
            }
        }

        void TopDownHeapify() {

            if(heapSize != 0) {

                int index = 0;
                while(fringeHeap.at(index)->weight > fringeHeap.at(((index + 1) * 2) - 1)->weight) {

                    std::shared_ptr<heapElement> placeholder = std::move(fringeHeap.at(index));
                    fringeHeap.at(index) = std::move(fringeHeap.at(((index + 1) * 2) - 1));

                    if(placeholder->weight > fringeHeap.at((index + 1) * 2)) {

                        fringeHeap.at(((index + 1) * 2) - 1) = std::move(fringeHeap.at((index + 1) * 2));
                        fringeHeap.at((index + 1) * 2) = std::move(placeholder);
                    }
                    else {

                        fringeHeap.at(((index + 1) * 2) - 1) = std::move(placeholder);
                    }
                }
            }
        }

        // TODO: find a way to reduce time complexity to logN
        // TODO: fix indexation (index / 2 gives parent, index * 2 / index * 2 + 1 gives left and right child)
        void FindAndUpdateHeapElement(int destinationNode, int newWeight) {

            int index = -1;
            bool isGreater = false;
            for(int i = 0; i < fringeHeap.size(); ++i) {

                if(fringeHeap.at(i)->destinationNode == destinationNode) {

                    index = i;
                    if(fringeHeap.at(i)->weight < newWeight) {

                        isGreater = true;
                    }

                    fringeHeap.at(i)->weight = newWeight;
                }
            }

            if(index) {

                if(isGreater) {

                    while(fringeHeap.at(index * 2)->weight < fringeHeap.at(index)->weight || 
                        fringeHeap.at((index * 2) + 1)->weight < fringeHeap.at(index)->weight) {

                            if(fringeHeap.at((index / 2) + 1)->weight < fringeHeap.at(index)) {

                                std::shared_ptr<heapElement> placeholder = std::move(fringeHeap.at(index));
                                fringeHeap.at(index) = std::move(fringeHeap.at(((index / 2) + 1)));
                                fringeHeap.at((index / 2) + 1) = std::move(placeholder);
                            }
                            else {

                                std::shared_ptr<heapElement> placeholder = std::move(fringeHeap.at(index));
                                fringeHeap.at(index) = std::move(fringeHeap.at((index / 2));
                                fringeHeap.at(index / 2) = std::move(placeholder);
                            }
                        }
                }
                else {

                    while(fringeHeap.at(index) < fringeHeap.at(index / 2)) {

                        std::shared_ptr<heapElement> placeholder = fringeHeap.at(index);
                        fringeHeap.at(index) = std::move(fringeHeapat(index / 2));
                        fringeHeap.at(index / 2) = std::move(placeholder);
                    }
                }
            }
            else {

                std::cout << "unable to find heap element in heap" << "\n";
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