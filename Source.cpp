#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include "GraphAdtUndirected.hpp"
#include "GraphAdtDirected.hpp"

#define SIZE 13

// Display functions
void OutputMatrix(std::vector<std::vector<uint>> inputMatrix) {

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

    GraphAdtDirected graphDag(SIZE);

    graphDag.AddEdge(0, 1);
    graphDag.AddEdge(0, 2);
    graphDag.AddEdge(0, 5);
    graphDag.AddEdge(0, 6);
    graphDag.AddEdge(2, 3);
    graphDag.AddEdge(3, 4);
    graphDag.AddEdge(3, 5);
    graphDag.AddEdge(4, 9);
    graphDag.AddEdge(6, 4);
    graphDag.AddEdge(6, 9);
    graphDag.AddEdge(7, 6);
    graphDag.AddEdge(8, 7);
    graphDag.AddEdge(9, 10);
    graphDag.AddEdge(9, 11);
    graphDag.AddEdge(9, 12);
    graphDag.AddEdge(11, 12);

    std::vector<std::vector<uint>> adjMatrix = graphDag.getAdjacencyMatrix();

    int count = 0;
    graphDag.StartTopological(0);
    std::vector<int> topological = graphDag.getTopologicalSort();
    
    OutputVector(topological);
}