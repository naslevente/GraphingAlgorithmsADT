#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <ostream>
#include <stack>
#include <queue>
#include <time.h>

#include <vector>
#include "WeightedGraph.hpp"
#include "GraphAdtInterface.hpp"
#include "weightedlink.hpp"
#include "heap.hpp"

typedef heapElement* ElementPointer;

class GraphAdtWeighted : GraphAdtInterface {

    private:

        int graphSize;
        int position = 0;
        std::unique_ptr<WeightedGraph> graph;
        std::unique_ptr<WeightedGraph> minSpanningTree;
        std::vector<int> low;
        std::vector<ElementPointer> weights;

    public:

        GraphAdtWeighted(size_t numVert) {

            graph = std::make_unique<WeightedGraph>(numVert);
            minSpanningTree = std::make_unique<WeightedGraph>(numVert);
            graphSize = numVert;
            low = std::vector<int>(numVert);

            // set the seed for random to time
            srand(time(0));
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
            graph->adjMatrix.at(secondNode).at(firstNode) = weight;

            // add weight to weights vector
            //heapElement newElement = heapElement(secondNode, firstNode, weight);
            ElementPointer newElementPointer = new heapElement(secondNode, firstNode, weight);
            weights.push_back(newElementPointer);

            return true;
        }

        // update union find method each time new connection is made between two nodes
        void UpdateUnionFind(int firstNode, int secondNode) {

            int i, j;
            for(i = firstNode; i != graph->unionFind.at(i); i = graph->unionFind.at(i));
            for(j = secondNode; j != graph->unionFind.at(j); j = graph->unionFind.at(j));

            if(i != j) {

                if(graph->parentSize.at(i) < graph->parentSize.at(j)) {

                    for(int k = 0; k < graph->unionFind.size(); ++k) {

                        // update each node whose parent is i
                        if(graph->unionFind.at(k) == i || graph->unionFind.at(k) == j) {

                            graph->unionFind.at(k) = j;

                            // update parent size
                            graph->parentSize.at(k) = graph->parentSize.at(j) + graph->parentSize.at(i);
                        }   
                    }
                }
                else {

                    for(int k = 0; k < graph->unionFind.size(); ++k) {

                        // update each node whose parent is j
                        if(graph->unionFind.at(k) == i || graph->unionFind.at(k) == j) {

                            graph->unionFind.at(k) = i;
                            graph->parentSize.at(k) = graph->parentSize.at(j) + graph->parentSize.at(i);
                        }
                    }
                }
            }

            graph->mstCompletion.pop();
        }

        // union find operation (returns parent of input node)
        int UnionFind(int node) {

            int i;
            for(i = node; i != graph->unionFind.at(i); i = graph->unionFind.at(i));

            return i;
        }

        // add edge to mst
        void AddToMST(ElementPointer currentElement) {

            if(!UnionCycle(currentElement)) {

                minSpanningTree->adjMatrix.at(currentElement->originNode).at(currentElement->destinationNode) 
                    = currentElement->weight;
                minSpanningTree->adjMatrix.at(currentElement->destinationNode).at(currentElement->originNode) 
                    = currentElement->weight;
                std::cout << "added to the mst" << std::endl;

                // update union find
                UpdateUnionFind(currentElement->originNode, currentElement->destinationNode);
            }
        }

        // Getters and setters for the various member variables of the graph
        std::vector<std::vector<int>> getAdjacencyMatrix() {

            return graph->adjMatrix;
        }

        std::vector<int> getMst() {

            return graph->minSpanningTree;
        }

        std::vector<std::vector<int>> getMstMatrix() {

            return minSpanningTree->adjMatrix;
        }

        std::vector<int> getUnionFind() {

            return graph->unionFind;
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

            int v, w, min;
            for(v = 0; v < graphSize; v++) {

                st.at(v) = -1; fr.at(v) = v; wt.at(v) = graph->maxWeight;
            }

            // create the "fringe" that will hold all non tree edges
            heap *fringe = new heap(0);
            int count = 0;

            // start with 0th node with a weight of negative one since it is the parent
            fringe->AddToHeap(-1, 0, -1);

            // each step requires lgV + MlgV where M * number of steps is E (the number of edges)
            while(fringe->heapSize != 0) {

                std::shared_ptr<heapElement> min  = fringe->DeleteMin();
                st.at(min->destinationNode) = fr.at(min->destinationNode);
                if(min->originNode == -1) {

                    st.at(min->destinationNode) = 0;
                }
                else {

                    st.at(min->destinationNode) = min->originNode;
                }

                // TODO: finish writing FindAndUpdateHeapElement in heap class
                // runs E times total for adjacency list represenation
                for(int i = 0; i < graphSize; ++i) {

                    if(graph->adjMatrix.at(min->destinationNode).at(i) != 0 && st.at(i) == -1) {

                        fringe->AddToHeap(min->destinationNode, i, graph->adjMatrix.at(min->destinationNode).at(i));
                        fr.at(i) = min->destinationNode;
                        wt.at(i) = graph->adjMatrix.at(min->destinationNode).at(i);
                    }
                    else if(graph->adjMatrix.at(min->destinationNode).at(i) < wt.at(i)) {

                        wt.at(i) = graph->adjMatrix.at(min->destinationNode).at(i);
                        fr.at(i) = min->destinationNode;
                        fringe->FindAndUpdateHeapElement(i, graph->adjMatrix.at(min->destinationNode).at(i));
                    }
                }
            }

            graph->minSpanningTree = st;

            delete fringe;
        }

        // !! necessary functions for kruskals algorithm

        // union-find algorithm to solve connectivity problem
        bool UnionCycle(ElementPointer inputEdge) {

            int firstNode = inputEdge->originNode;
            int secondNode = inputEdge->destinationNode;

            int i, j;

            for(i = firstNode; i != graph->unionFind.at(i); i = graph->unionFind.at(i));
            for(j = secondNode; j != graph->unionFind.at(j); j = graph->unionFind.at(j));

            if(i == j) {

                return true;
            }
            else {

                return false;
            }
        }

        // sort the weights of the graph
        void SortWeights() {

            std::vector<ElementPointer> newWeights = std::vector<ElementPointer>();
            for(int i = 0; i < weights.size(); ++i) {

                ElementPointer currentPointer = weights.at(i);

                int index = 0;
                for(int k = 0; k < newWeights.size(); ++k) {

                    if(!(currentPointer->weight > newWeights.at(k)->weight)) {

                        index = k;
                        break;
                    }
                    else {

                        index = k + 1;
                    }
                }

                auto iterator = newWeights.begin();
                newWeights.insert((iterator + index), 1, currentPointer);
            }

            weights = newWeights;
        }

        // quicksort implementation for modified kruskals algorithm
        // at each recursive call, edges less than the partition are checked and
        // added to MST. After each recursive call, there's a check to see if
        // v-1 edges have been added to the mst
        void QuickSort(int startIndex, int endIndex) {

            if(endIndex - startIndex == 1) { // reached end of recursive call

                // check to see if start index or end index weight is larger
                ElementPointer currentElementAtStart = weights.at(startIndex);
                ElementPointer currentElementAtEnd = weights.at(endIndex);
                if(currentElementAtStart->weight > currentElementAtEnd->weight) {

                    // add only the lesser edge
                    // TODO: add check if MST is complete (if not, add other edge too)
                    AddToMST(currentElementAtEnd);
                }
                else {

                    AddToMST(currentElementAtStart);
                }

                return;
            }

            // pick an efficient partition
            int partitionIndex = (startIndex + endIndex) / 2;
            ElementPointer partitionElement = weights.at(partitionIndex);

            // create vector for the sorted weights
            std::vector<int> sortedVector = std::vector<int>(0, weights.size());

            int rightIndex = endIndex;
            int leftIndex = 0;

            // place weights into correct position
            for(int i = 0; i < endIndex; ++i) {

                ElementPointer currentElement = weights.at(i);

                // TODO: make case for equal weight
                if(currentElement->weight < partitionElement->weight) {

                    sortedVector.at(leftIndex) = currentElement->weight;
                }
                else {

                    sortedVector.at(rightIndex) = currentElement->weight;
                }

                delete currentElement;
            }

            // delete pointers and move contents of sortedVector to weights
            delete partitionElement;
            // TODO: replace non-sorted parts of the original vector with newly sorted parts
            //weights = std::move(sortedVector);

            // initiate next recursive calls
            int newPartitionIndex = partitionIndex / 2;
            QuickSort(0, newPartitionIndex);
            QuickSort(newPartitionIndex, partitionIndex);
        }

        bool DepthFirstSearchMatrix(int node, int destinationNode, std::vector<int> tracker) {

            tracker.at(node) = -1;

            bool isCycle = false;
            for(int i = 0; i < graphSize; ++i) {

                //if(minSpanningTree->adjMatrix.at(node).at(i) != 0 || minSpanningTree->adjMatrix.at(i).at(node) != 0) {
                if(minSpanningTree->adjMatrix.at(node).at(i) != 0 && tracker.at(i) != -1) {

                    if(i == destinationNode) {

                        return true;
                    }
                    else {

                        isCycle = DepthFirstSearchMatrix(i, destinationNode, tracker);
                    }
                }

                if(isCycle) {

                    return true;
                }
            }

            if(isCycle) {

                return true;
            }
            else {

                return false;
            }
        }

        // !! Kruskals algorithm for computing the MST of a graph (adj matrix representation) !!
        // if uinion-find with halving is used to find the connectivity between two vertices in the mst
        // sorting dominates the running time, making the total running at best E log E
        void Kruskals() {

            for(int i = 0; i < graph->adjMatrix.size(); ++i) {

                for(int j = 0; j < graph->adjMatrix.at(0).size(); ++j) {

                    std::cout << graph->adjMatrix.at(i).at(j) << " ";
                }

                std::cout << "\n";
            }

            // reset vector based array
            graph->orderVector = std::vector<int>(graph->vertices, -1);

            // sort weights with whatever sorting algorithm
            SortWeights();

            for(int i = 0; i < weights.size(); ++i) {

                ElementPointer currentElement = weights.at(i);
                std::cout << "origin node of current edge: " << currentElement->originNode << std::endl;
                std::cout << "destination node of current edge: " << currentElement->destinationNode << std::endl;
                std::cout << "weight of current edge: " << currentElement->weight << std::endl;

                if(!UnionCycle(currentElement)) {

                    minSpanningTree->adjMatrix.at(currentElement->originNode).at(currentElement->destinationNode) 
                        = currentElement->weight;
                    minSpanningTree->adjMatrix.at(currentElement->destinationNode).at(currentElement->originNode) 
                        = currentElement->weight;
                    std::cout << "added to the mst" << std::endl;

                    // update union find
                    UpdateUnionFind(currentElement->originNode, currentElement->destinationNode);
                }
            }
        }

        // Boruvka's MST algorithm
        void Boruvkas() {

            /*
            algorithm in a nutshell:
                1. maintain vertex-indexed array that holds information about nearest mst subtree neighbor
                2. scan through each edge, if it connects two vertices in same tree (their union ids are the same) discard that edge
                3. Otherwise, check the nearest-neighbor distances/weights and update them in vertex-indexed array if necessary
                4. from vertex-indexed array perform union operations on all edges that connect vertices with nearest neighbor
            */

            /* algorithm runs in in O(E lg V log * E)
            proof: at each stage, number of substrees is atleast halved (log V iterations). Each iteration contains E union find operations
            is less than E log * E which is essentially linear
        }
};