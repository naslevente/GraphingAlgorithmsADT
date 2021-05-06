#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>
#include "link.hpp"

#ifndef GRAPHHEADER
#define GRAPHHEADER

class Graph {

    public:

        std::vector<std::shared_ptr<link>> adjList;
        std::vector<std::shared_ptr<link>> reverseAdjList;

        // count/order of the nodes from a dfs
        std::vector<int> orderVector;
        std::vector<std::vector<int>> adjMatrix;
        // size of the matrix
        size_t vertices;

        Graph(size_t numVert) {

            vertices = numVert;

            // Define the size for the order and adjMatrix vector
            orderVector = std::vector<int>(vertices, -1);
            adjMatrix = std::vector<std::vector<int>>(vertices, std::vector<int>(vertices));

            for(int i = 0; i < vertices; i++) {

                std::shared_ptr<link> newLink = std::make_shared<link>(i);
                std::shared_ptr<link> newReverseLink = std::make_shared<link>(i);

                adjList.push_back(newLink);
                reverseAdjList.push_back(newReverseLink);

                for(int k = 0; k < vertices; k++) {

                    adjMatrix.at(i).push_back(0);
                }
            }
        }
        ~Graph() {}

        bool AddLink(int vert, std::shared_ptr<link> node) {

            node.get()->next = std::make_shared<link>(vert);

            return true;
        }
};
#endif