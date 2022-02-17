#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>
#include <deque>
#include "weightedlink.hpp"

#ifndef WEIGHTEDHEADER
#define WEIGHTEDHEADER

class WeightedGraph {

    public:

        size_t vertices;
        int maxWeight = 0;
        std::deque<int> mstCompletion;

        std::vector<std::shared_ptr<weightedlink>> adjList;

        std::vector<int> orderVector;
        std::vector<std::vector<int>> adjMatrix;
        std::vector<int> minSpanningTree;

        // for any msts being calculated with weighted graph object
        std::vector<int> unionFind;
        std::vector<int> parentSize;
        int mstTracker;

        WeightedGraph(size_t graphSize) {

            vertices = graphSize;
            orderVector = std::vector<int>(vertices, -1);
            parentSize = std::vector<int>(graphSize, 1);

            mstTracker = graphSize;

            adjMatrix = std::vector<std::vector<int>>(vertices, std::vector<int>(vertices));

            for(int i = 0; i < vertices; ++i) {

                std::shared_ptr<weightedlink> newLink = std::make_shared<weightedlink>(i);
                adjList.push_back(newLink);

                unionFind.push_back(i);

                mstCompletion.push_back(i);

                for(int k = 0; k < vertices; ++k) {

                    adjMatrix.at(i).at(k) = 0;
                }
            }
        }

        ~WeightedGraph() {}

        bool AddLink(std::shared_ptr<weightedlink> node, int nextNode, int weight) {

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