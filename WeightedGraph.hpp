#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>
#include "weightedlink.hpp"

#ifndef WEIGHTEDHEADER
#define WEIGHTEDHEADER

class WeightedGraph {

    public:

        size_t vertices;
        uint maxWeight = 0;

        std::vector<std::shared_ptr<weightedlink>> adjList;

        std::vector<int> orderVector;
        std::vector<std::vector<uint>> adjMatrix;
        std::unique_ptr<Graph> minSpanningTree;

        WeightedGraph(size_t graphSize) {

            vertices = graphSize;
            orderVector = std::vector<int>(vertices, -1);

            adjMatrix = std::vector<std::vector<uint>>(vertices, std::vector<uint>(vertices));

            for(int i = 0; i < vertices; ++i) {

                std::shared_ptr<weightedlink> newLink = std::make_shared<weightedlink>(i);
                adjList.push_back(newLink);

                for(int k = 0; k < vertices; k++) {

                    adjMatrix.at(i).push_back(0);
                }
            }
        }

        ~WeightedGraph() {}

        bool AddLink(std::shared_ptr<weightedlink> node, uint nextNode, uint weight) {

            if(weight + 1 > maxWeight) {

                maxWeight = weight + 1;
            }

            std::shared_ptr<weightedlink> newLink = std::make_shared<weightedlink>(nextNode);

            node.get()->next = newLink;
            newLink.get()->weight = weight;

            return true;
        }
};

#endif