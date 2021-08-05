#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include "heap.hpp"
#include "heapElement.hpp"
#include "GraphAdtUndirected.hpp"
#include "GraphAdtDirected.hpp"
#include "GraphAdtWeighted.hpp"

#define SIZE 8

// Display functions
void OutputMatrix(std::vector<std::vector<int>> inputMatrix) {

    for(int i = 0; i < SIZE; i++) {

        for(int k = 0; k < SIZE; k++) {

            std::cout << inputMatrix.at(i).at(k);
        }
        
        std::cout << "\n";
    }
}

void OutputVector(std::vector<int> inputVector) {

    for(int i = 0; i < SIZE; i++) {

        std::cout << inputVector.at(i) << " ";
    }

    std::cout << "\n";
}

int main() {

    GraphAdtWeighted *graphDag = new GraphAdtWeighted(SIZE);

    graphDag->AddEdge(0, 2, 7);
    graphDag->AddEdge(0, 7, 8);
    graphDag->AddEdge(0, 6, 15);
    graphDag->AddEdge(0, 1, 9);
    graphDag->AddEdge(0, 5, 17);
    graphDag->AddEdge(7, 1, 5);
    graphDag->AddEdge(7, 6, 6);
    graphDag->AddEdge(7, 4, 12);
    graphDag->AddEdge(4, 3, 10);
    graphDag->AddEdge(4, 5, 11);
    graphDag->AddEdge(3, 5, 3);
    graphDag->AddEdge(6, 4, 15);

    std::vector<int> unionFind = graphDag->getUnionFind();
    OutputVector(unionFind);

    graphDag->Kruskals();

    /*
    // test the heap structure
    std::shared_ptr<heap> heapStructure = std::make_shared<heap>(0);
    heapStructure->AddToHeap(0, 2, 3);
    heapStructure->AddToHeap(0, 7, 5);
    heapStructure->AddToHeap(0, 6, 15);
    heapStructure->AddToHeap(0, 1, 16);
    heapStructure->AddToHeap(0, 5, 17);
    heapStructure->AddToHeap(7, 1, 6);
    heapStructure->AddToHeap(7, 6, 7);
    heapStructure->AddToHeap(7, 4, 8);
    heapStructure->AddToHeap(4, 3, 9);
    heapStructure->AddToHeap(4, 5, 11);
    heapStructure->AddToHeap(3, 5, 10);
    heapStructure->AddToHeap(6, 4, 12);

    std::vector<std::shared_ptr<heapElement>> fringeHeap = heapStructure->getHeap();
    for(int i = 0; i < fringeHeap->size(); ++i) {

        std::cout << fringeHeap->at(i)->weight << std::endl;
    }
    */

    /*
    graphDag->Kruskals();
    std::vector<std::vector<int>> mst = graphDag->getMstMatrix();

    for(int i = 0; i < mst->size(); ++i) {

        for(int j = 0; j < mst->at(0)->size(); ++j) {

            std::cout << mst->at(i)->at(j) << " ";
        }

        std::cout << "\n";
    }
    */

    /*
    //graphDag->StartTopological(0);
    //std::vector<int> topological = graphDag->Kosarajus(0);
    graphDag->Kosarajus();
    std::vector<int> strongComponents = graphDag->getStrongComponents();
    std::vector<int> reverseTopological = graphDag->getReverseTopological();

    // ! make sure to reset the order vector and the position variable after using a property !
    graphDag->ResetOrderVector();

    OutputVector(strongComponents);

    //GraphAdtWeighted weightedgraph(8);

    //weightedgraph->AddEdge(0, 1, )
    */
}