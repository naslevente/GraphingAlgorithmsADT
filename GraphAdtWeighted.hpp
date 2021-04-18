#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <ostream>
#include <stack>

#include <vector>
#include "WeightedGraph.hpp"
#include "GraphAdtInterface.hpp"
#include "weightedlink.hpp"
#include "heap.hpp"

class GraphAdtWeighted : GraphAdtInterface {

    private:

        uint graphSize;
        uint position = 0;
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
        bool AddToList(int firstNode, int secondNode, uint weight) {

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
        bool AddToMatrix(int firstNode, int secondNode, uint weight) {

            // Assuming this edge has not already been added to the matrix and 
            // that the edge is being added to a directed graph
            graph->adjMatrix.at(firstNode).at(secondNode) = weight;
            graph->adjMatrix.at(firstNode).at(firstNode) = weight;

            return true;
        }

        // Getters and setters for the various member variables of the graph
        std::vector<std::vector<uint>> getAdjacencyMatrix() {

            return graph->adjMatrix;
        }

        // algorithms to find the mst of a graph
        void Prims() {

            std::vector<int> min = std::vector<int>(graphSize);
            std::vector<int> mst = std::vector<int>(graphSize);

            for(int i = 0; i < graphSize; i++) {

                min.at(i) = graph->maxWeight;
                mst.at(i) = -1;
            }

            for(int i = 0; i != graphSize - 1; ) {

                if(mst.at(i) == -1) {

                    for(int x = 0; x < graphSize; x++) {

                        if(mst.at(x) == -1) {

                            if(graph->adjMatrix.at(i).at(x) < min.at(i)) {

                                min.at(i) = graph->adjMatrix.at(i).at(x);
                                mst.at(i) = x;
                            }
                        }
                    }

                    i = mst.at(i);
                }
            }
        }

        /* !! st vector will hold the parent node of a tree node in the MST 
            fr vector will hold the closest tree node to a non tree node
            wt vector will hold the legnth of a parent link for a tree node and for a non tree node the distance to the MST !! */
        void GRAPHmstV() {

            std::unique_ptr<Graph> minSpanningTree = std::make_unique<Graph>(graphSize)

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

                        if(graph->adjMatrix.at(v).at(w) < wt.at(w)) {

                            wt.at(w) = graph->adjMatrix.at(v).at(w);
                            fr.at(w) = v;
                        }

                        if(wt.at(w) < wt.at(min)) {

                            min = w;
                        }
                    }
                }

                minSpanningTree->AddLink(st.at(min), min);
            }

            graph->minSpanningTree = std::move(minSpanningTree);
        }

        // PFS implementation of prim's algorithm, improves running time to ElgV
        // PFS implementation uses a heap for priority-queue implementation
        void PFSPrims() {

            std::unique_ptr<Graph> minSpanningTree = std::make_unique<Graph>(graphSize)

            std::vector<int> st = std::vector<int>(graphSize);
            std::vector<int> fr = std::vector<int>(graphSize);
            std::vector<int> wt = std::vector<int>(graphSize + 1);

            int v, w, min;
            for(v = 0; v < graphSize; v++) {

                st.at(v) = -1; fr.at(v) = v; wt.at(v) = graph->maxWeight;
            }

            // create the "fringe" that will hold all non tree edges
            std::shared_ptr<heap> fringe;
            int count = 0;

            int node = 0;
            while(count != graph->vertices) {

                std::unique_ptr<link> copyPointer = graph->adjList.at(node);
                while(copyPointer != nullptr) {

                    copyPointer = copyPointer->next;
                    fringe->addToHeap(copyPointer->vert);
                }

                uint min = fringe->deleteMin();
                minSpanningTree-AddLink(node, min);
                node = min;
            }

            /*
            st.at(0) = 0; wt.at(graphSize) = graph->maxWeight;
            for(min = 0; min != graphSize; ) {

                v = min; st.at(min) = fr.at(min);
                for(w = 0, min = graphSize; w < graphSize; w++) {

                    if(st.at(w) == -1) {

                        if(graph->adjMatrix.at(v).at(w) < wt.at(w)) {

                            wt.at(w) = graph->adjMatrix.at(v).at(w);
                            fr.at(w) = v;
                        }

                        if(wt.at(w) < wt.at(min)) {

                            min = w;
                        }
                    }
                }

                minSpanningTree->AddLink(st.at(min), min);
            }
            */

            graph->minSpanningTree = std::move(minSpanningTree);
        }
};