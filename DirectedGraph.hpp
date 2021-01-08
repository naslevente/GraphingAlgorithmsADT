#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>
#include "Graph.hpp"

#ifndef DIRECTEDHEADER
#define DIRECTEDHEADER
class DirectedGraph: public Graph {

    public:

        std::vector<int> reverseTopological;
        std::vector<int> strongComponents;
        std::vector<std::vector<uint>> dagTransitiveClosure;
        std::vector<std::vector<uint>> transitiveClosure;
        std::vector<int> topological;

        DirectedGraph(size_t numVert) : Graph(numVert) {

            // Define the size for the order, reverseTopological and adjMatrix vector
            reverseTopological = std::vector<int>(vertices, -1);
            topological = std::vector<int>(vertices, -1);
            strongComponents = std::vector<int>(vertices, -1);
            transitiveClosure = std::vector<std::vector<uint>>(vertices, std::vector<uint>(vertices));
            dagTransitiveClosure = std::vector<std::vector<uint>>(vertices, std::vector<uint>(vertices));

            for(int i = 0; i < vertices; i++) {

                transitiveClosure.at(i).at(i) = 1;
                dagTransitiveClosure.at(i).at(i) = 1;
                adjMatrix.at(i).at(i) = 1;
            }
        }

        ~DirectedGraph() {}

        std::vector<int> getStrongComponents() {

            return strongComponents;
        }

        std::vector<int> getReverseTopological() {

            return reverseTopological;;
        }

        std::vector<std::vector<uint>> getTransClos() {

            return transitiveClosure;
        }

        void setTransitiveClosure(std::vector<std::vector<uint>> inputMatrix) {

            transitiveClosure = std::move(inputMatrix);
        }
};
#endif