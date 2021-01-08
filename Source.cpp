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

    /*
    size_t SIZE = 8;
    GraphAdtUndirected graph(SIZE);

    graph.AddEdge(0, 2);
    graph.AddEdge(0, 7);
    graph.AddEdge(0, 5);

    graph.AddEdge(2, 6);
    graph.AddEdge(6, 4);
    graph.AddEdge(7, 1);
    graph.AddEdge(5, 3);

    graph.AddEdge(4, 7);
    graph.AddEdge(4, 3);
    graph.AddEdge(4, 5);

    graph.DepthFirstSearchList(0);
    */

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
    graphDag.Topological(0);
    std::vector<int> topological = graphDag.getTopologicalSort();
    
    OutputVector(topological);

    /*
    GraphAdtDirected graphDag(SIZE);

    graphDag.AddEdge(0, 2);
    graphDag.AddEdge(0, 5);
    graphDag.AddEdge(1, 0);
    graphDag.AddEdge(2, 1);
    graphDag.AddEdge(3, 2);
    graphDag.AddEdge(3, 4);
    graphDag.AddEdge(4, 5);
    graphDag.AddEdge(5, 4);

    std::vector<std::vector<uint>> adjMatrix = graphDag.getAdjacencyMatrix();
    graphDag.TransitiveClosure();
    std::vector<std::vector<uint>> transitiveClosure = graphDag.getTransitiveClosure();
    
    OutputMatrix(transitiveClosure);
    */
}