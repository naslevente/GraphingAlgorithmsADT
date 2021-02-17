#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <ostream>
#include <stack>

#include <vector>
#include "DirectedGraph.hpp"

class GraphAdtDirected {

    private:

        uint graphSize;
        uint position = 0;
        std::unique_ptr<DirectedGraph> graph;
        std::unique_ptr<DirectedGraph> kernelDag;

        std::vector<int> low;
        std::stack<int> tarjansStack;

        // Template function
        void BeginOperation(void (GraphAdtDirected::*func) (int, int&), int startNode, int& count) {

            for(int i = 0; i < graph->vertices; i++) {

                if(graph->orderVector.at(i) == -1) {

                    (this->*func)(i, count);                  
                }
            }
        }

    public:

        // reset the count/order of the nodes
        void ResetOrderVector() {

            graph->orderVector.clear();
            graph->orderVector = std::vector<int>(graph->vertices, -1);

            position = 0;
        }

        GraphAdtDirected(size_t numVert) {

            graphSize = numVert;

            // Create the adjacency list representation of the graph
            graph = std::make_unique<DirectedGraph>(numVert);
            low = std::vector<int>(numVert);
        }

        ~GraphAdtDirected() {}

        // Getters and setters for the various member variables of the graph
        std::vector<std::vector<uint>> getAdjacencyMatrix() {

            return graph->adjMatrix;
        }

        std::vector<std::vector<uint>> getTransitiveClosure() {

            return graph->transitiveClosure;
        }

        std::vector<int> getTopologicalSort() {

            return graph->topological;
        }

        std::vector<int> getStrongComponents() {

            return graph->strongComponents;
        }

        std::vector<int> getReverseTopological() {

            return graph->reverseTopological;
        }

        void AddEdge(int firstNode, int secondNode) {

            /*
            if(AddToList(firstNode, secondNode) && AddToMatrix(firstNode, secondNode)) {

                return true;
            }
            else {

                return false;
            }
            */

            // adding edge to graph
            if(AddToList(firstNode, secondNode) && AddToMatrix(firstNode, secondNode)) {

                std::cout << "added edge from " << firstNode << " to " << secondNode << " to the graph" << std::endl;
            }
        }

        /* Series of functions that use the BeginOperation function 
        to recursively find the respectuive soolution */

        // Function to find the topological sorting of a DAG
        void StartTopological(int startNode) {

            int count = 0;
            BeginOperation(&GraphAdtDirected::Topological, startNode, count);
        }

        void StartReverseTopological(int startNode) {

            int count = 0;
            BeginOperation(&GraphAdtDirected::ReverseTopological, startNode, count);
        }

        void StartDagTransitiveClosure(int startNode) {

            int count = 0;
            BeginOperation(&GraphAdtDirected::ReverseTopological, startNode, count);

            for(int i = 0; i < graph->vertices; i++) {

                int startNode = graph->reverseTopological.at(i);
                DagTransitiveClosure(startNode);
            }
        }

        // Add edge from firstNode to secondNode to directed graph
        bool AddToList(int firstNode, int secondNode) {

            // add edge to the graph
            std::shared_ptr<link> copyPointer = graph->adjList.at(firstNode);
            while(!(copyPointer->next.get() == NULL)) {

                copyPointer = copyPointer.get()->next;
            }

            // add edge to the reverse graph
            std::shared_ptr<link> secondCopyPointer = graph->reverseAdjList.at(secondNode);
            while(!(secondCopyPointer->next.get() == NULL)) {

                secondCopyPointer = secondCopyPointer.get()->next;
            }

            //std::cout << "final link node at: " << secondCopyPointer->vert << std::endl;

            if(!(graph->AddLink(secondNode, copyPointer))) {

                std::cout << "Error: unable to create and add the link to adjacency" << std::endl;
                return false;
            }

            if(!(graph->AddLink(firstNode, secondCopyPointer))) {

                std::cout << "Error: unable to create and add the link to reverse adjacency" << std::endl;
                return false;
            }

            return true;
        }

        // Add edge from firstNode to secondNode including self cycles for adj matrix in a directed graph
        bool AddToMatrix(int firstNode, int secondNode) {

            // Assuming this edge has not already been added to the matrix and 
            // that the edge is being added to a directed graph
            graph->adjMatrix.at(firstNode).at(secondNode) = 1;
            graph->adjMatrix.at(firstNode).at(firstNode) = 1;

            return true;
        }

        // Equivalent to a dfs but using the reverse topological sorting of the graph (adj matrix)
        void DFSTopological(int node, int& count) {

            graph->orderVector.at(node) = position;
            ++position;

            graph->strongComponents.at(node) = count;
            for(int i = graph->vertices - 1; i >= 0; --i) {

                int secondNode = graph->reverseTopological.at(i);
                if(graph->adjMatrix.at(node).at(secondNode) == 1 && graph->orderVector.at(secondNode) == -1) {

                    DFSTopological(secondNode, count);
                }
            }
        }

        // DFS specifically made for tarjans algorithms for finding strong components
        void DFSTarjans(int node, int count, int componentCount) {

            graph->orderVector.at(node) = count;
            low.at(node) = count;
            int min = low.at(node);

            std::shared_ptr<link> newNode;

            tarjansStack.push(node);
            for(newNode = graph->adjList.at(node); node != NULL; newNode = newNode.get()->next) {

                if(graph->orderVector.at(newNode.get()->vert) == -1) {

                    count += 1;
                    DFSTarjans(newNode.get()->vert, count, componentCount);
                }

                if(low.at(newNode.get()->vert) < low.at(node)) {

                    low.at(node) = low.at(newNode.get()->vert);
                }
            }

            if(low.at(node) < min) {

                min = low.at(node);
            }
            else {

                while(!tarjansStack.empty()) {


                    graph->strongComponents.at(tarjansStack.top()) = componentCount;
                    tarjansStack.pop();
                }

                componentCount++;
            }
        }

        // function that finds the transitive closure for a directed cyclic graph
        void TransitiveClosure() {

            graph->setTransitiveClosure(graph->adjMatrix);
            for(int i = 0; i < graphSize; i++) {

                for(int s = 0; s < graphSize; s++) {

                    if(graph->transitiveClosure.at(s).at(i)) {

                        for(int t = 0; t < graphSize; t++) {

                            if(graph->transitiveClosure.at(i).at(t)) graph->transitiveClosure.at(s).at(t) = 1;
                        }
                    }
                }
            }
        }

        // Function to find the topological sorting of a DAG using its reverse
        void ReverseTopological(int startNode, int& count) {

            graph->orderVector.at(startNode) = position;
            position++;

            std::shared_ptr<link> nodePointer;
            nodePointer = graph->reverseAdjList.at(startNode);

            if(nodePointer.get()->next.get() == NULL) {

                std::cout << "pointing to null" << std::endl;
            }

            for(nodePointer = graph->reverseAdjList.at(startNode)->next; nodePointer != NULL; 
                nodePointer = nodePointer.get()->next) {

                if(graph->orderVector.at(nodePointer.get()->vert) == -1) {

                    ReverseTopological(nodePointer.get()->vert, count);
                }
            }

            graph->reverseTopological.at(count) = startNode;
            ++count;
        }

        // Recursively find a topological sorting
        void Topological(int node, int& count) {

            graph->orderVector.at(node) = position;
            position++;

            for(int i = 0; i < graph->vertices; i++) {

                if(graph->adjMatrix.at(i).at(node)) {

                    if(graph->orderVector.at(i) == -1) {

                        Topological(i, count);
                    }
                }
            }

            graph->topological.at(count) = node;
            count++;
        }

        void DagTransitiveClosure(std::unique_ptr<DirectedGraph> directedGraph, int node) {

            directedGraph->orderVector.at(node) = position;
            ++position;

            for(int i = 0; i < directedGraph->vertices; i++) {

                //int index = graph->reverseTopological.at(i);
                if(directedGraph->adjMatrix.at(node).at(i) != 0) {

                    directedGraph->dagTransitiveClosure.at(i).at(i) = 1;
                    if(directedGraph->orderVector.at(i) == -1) {

                        DagTransitiveClosure(i);
                    }

                    for(int p = 0; p < directedGraph->vertices; p++) {

                        if(directedGraph->adjMatrix.at(i).at(p) != 0) {

                            directedGraph->dagTransitiveClosure.at(i).at(p) = 1;
                        }
                    }
                }
            }
        }

        /*!! algorithms for computing string components of a graph

            --Kosarajus runs in time proprtional to V^2
            --tarjans runs in linear time
        !!*/

        // Strong component algorithms begin with node 0
        void Kosarajus() {

            int count = 0;
            for(int i = 0; i < graph->vertices; i++) {

                if(graph->orderVector.at(i) == -1) {

                    ReverseTopological(i, count);
                    //count++;
                }
            }

            std::cout << "finished the first dfs" << std::endl;

            ResetOrderVector();

            count = 0;
            for(int i = graph->vertices - 1; i >= 0; --i) {

                int node = graph->reverseTopological.at(i);
                if(graph->orderVector.at(node) == -1) {

                    DFSTopological(node, count);
                    ++count;
                }
            }

            std::cout << "finished the second dfs" << std::endl;
        }

        void Tarjans(int startNode) {

            std::shared_ptr<link> firstNode;
            uint count = 0;
            uint componentCount = 0;
            for(firstNode = graph->adjList.at(startNode); firstNode != NULL; firstNode = firstNode->next) {

                if(graph->orderVector.at(firstNode->vert) == -1) {

                    DFSTarjans(firstNode->vert, count, componentCount);
                }
            }
        }

        void FindKernelDag() {

            auto maxElement = max_element(std::begin(graph->strongComponents), std::end(graph->strongComponents));
            kernelDag = std::make_unique<DirectedGraph>(maxElement + 1);

            for(int i = 0; i < graph->vertices; i++) {

                std::shared_ptr<link> node;
                for(node = graph->adjList.at(i)->next; node != NULL; node = node->next) {

                    kernelDag->adjMatrix.at(graph-strongComponents.at(i)).at(graph->strongComponents.at(node->vert)) = 1;
                }
            }
        }        

        // strong component based transitive closure algorithm
        void SCTransClosure() {

            // first find the strong components of the graph using either 
            // tarjans or kosarajus
            Kosarajus();

            // find the kernel DAG using the strong components
            FindKernelDag();

            // find the transitive closure based on the kernel dag
            for(int i = 0; i < kernelDag->vertices; ++i) {

                if(kernelDag->orderVector.at(i) == -1) {

                    DagTransitiveClosure(kernelDag, i);
                }
            }
        }
};