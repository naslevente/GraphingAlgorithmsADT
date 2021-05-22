#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <ostream>
#include <stack>
#include <queue>

#include <vector>
#include "WeightedGraph.hpp"
#include "GraphAdtInterface.hpp"
#include "weightedlink.hpp"
#include "heap.hpp"

class GraphAdtWeighted : GraphAdtInterface {

    private:

        int graphSize;
        int position = 0;
        std::unique_ptr<WeightedGraph> graph;
        std::vector<int> low;

    public:

        GraphAdtWeighted(size_t numVert) {

            graph = std::make_unique<WeightedGraph>(numVert);
            graphSize = numVert;
            low = std::vector<int>(numVert);
        }

        void AddEdge(int firstNode, int secondNode, int weight) {

            if(!AddToList(firstNode, secondNode, weight) || !AddToMatrix(firstNode, secondNode, weight)) {

                std::cout << "failed to add the edge to the graph" << std::endl;
            }
        }

        // Add edge from firstNode to secondNode to directed graph
        bool AddToList(int firstNode, int secondNode, int weight) {

            // add edge to the graph
            std::shared_ptr<weightedlink> copyPointer = graph->adjList.at(firstNode);
            while(!(copyPointer->next.get() == nullptr)) {

                copyPointer = copyPointer.get()->next;
            }

            //std::cout << "final link node at: " << secondCopyPointer->vert << std::endl;

            if(!(graph->AddLink(copyPointer, secondNode, weight))) {

                std::cout << "Error: unable to create and add the link to adjacency" << std::endl;
                return false;
            }

            return true;
        }

        // Add edge from firstNode to secondNode including self cycles for adj matrix in a directed graph
        bool AddToMatrix(int firstNode, int secondNode, int weight) {

            // Assuming this edge has not already been added to the matrix and 
            // that the edge is being added to a directed graph
            graph->adjMatrix.at(firstNode).at(secondNode) = weight;
            
            // removing self loops
            //graph->adjMatrix.at(firstNode).at(firstNode) = weight;

            return true;
        }

        // Getters and setters for the various member variables of the graph
        std::vector<std::vector<int>> getAdjacencyMatrix() {

            return graph->adjMatrix;
        }

        std::vector<int> getMst() {

            return graph->minSpanningTree;
        }

        /* !! st vector will hold the parent node of a tree node in the MST 
            fr vector will hold the closest tree node to a non tree node
            wt vector will hold the legnth of a parent link for a tree node and for a non tree node the distance to the MST !! */
        void GRAPHmstV() {

            std::unique_ptr<Graph> minSpanningTree = std::make_unique<Graph>(graphSize);

            std::vector<int> st = std::vector<int>(graphSize);
            std::vector<int> fr = std::vector<int>(graphSize);
            std::vector<int> wt = std::vector<int>(graphSize + 1);

            int v, w, min;
            for(v = 0; v < graphSize; v++) {

                st.at(v) = -1; fr.at(v) = v; wt.at(v) = graph->maxWeight;
            }

            st.at(0) = 0; wt.at(graphSize) = graph->maxWeight;
            for(min = 0; min != graphSize; ) {

                v = min; st.at(min) = fr.at(min);
                for(w = 0, min = graphSize; w < graphSize; w++) {

                    if(st.at(w) == -1) {

                        if((graph->adjMatrix.at(v).at(w) != 0) && graph->adjMatrix.at(v).at(w) 
                            < wt.at(w)) {

                            wt.at(w) = graph->adjMatrix.at(v).at(w);
                            fr.at(w) = v;
                        }

                        if(wt.at(w) < wt.at(min)) {

                            min = w;
                        }
                    }
                }
            }

            graph->minSpanningTree = st;
        }

        // PFS implementation of prim's algorithm, improves running time to ElgV
        // PFS implementation uses a heap for fringe management
        void PFSPrims() {

            std::vector<int> st = std::vector<int>(graphSize);
            std::vector<int> fr = std::vector<int>(graphSize);
            std::vector<int> wt = std::vector<int>(graphSize + 1);

            // keeps track of the nodes that have been visited
            std::queue<int>* countQueuePtr;
            std::queue<int> countQueue = std::queue<int>();
            countQueuePtr = &countQueue;

            int v, w, min;
            for(v = 0; v < graphSize; v++) {

                st.at(v) = -1; fr.at(v) = v; wt.at(v) = graph->maxWeight;
                countQueuePtr->push(v);
            }

            // create the "fringe" that will hold all non tree edges
            std::shared_ptr<heap> fringe = std::make_shared<heap>(0);
            int count = 0;

            // start with 0th node with a weight of negative one since it is the parent
            fringe->AddToHeap(-1, 0, -1);

            while(!countQueuePtr->empty()) {

                std::shared_ptr<heapElement> min  = fringe->DeleteMin();
                if(min->originNode == -1) {

                    st.at(min->destinationNode) = 0;
                    countQueuePtr->pop();
                }
                else {

                    st.at(min->destinationNode) = min->originNode;
                    countQueuePtr->pop();
                }

                for(int i = 0; i < graphSize; ++i) {

                    if(graph->adjMatrix.at(min->destinationNode).at(i) != 0 && st.at(i) == -1) {

                        fringe->AddToHeap(min->destinationNode, i, graph->adjMatrix.at(min->destinationNode).at(i));
                    }
                }
            }

            graph->minSpanningTree = st;
        }

        // !! Kruskals algorithm to computing the MST of a graph
        void Kruskals() {


        }
};