#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <ostream>

#include <vector>
#include "DirectedGraph.hpp"

class GraphAdtDirected {

    private:

        uint graphSize;
        uint position = 1;
        std::unique_ptr<DirectedGraph> graph;

    public:

        GraphAdtDirected(size_t numVert) {

            graphSize = numVert;

            // Create the adjacency list representation of the graph
            graph = std::make_unique<DirectedGraph>(numVert);
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

        void AddEdge(int firstNode, int secondNode) {

            /*
            if(AddToList(firstNode, secondNode) && AddToMatrix(firstNode, secondNode)) {

                return true;
            }
            else {

                return false;
            }
            */

            if(AddToList(firstNode, secondNode) && AddToMatrix(firstNode, secondNode)) {

                std::cout << "Added " << firstNode << " and " << secondNode << " to the graph" << std::endl;
            }
        }

        // Add edge from firstNode to secondNode to directed graph
        bool AddToList(int firstNode, int secondNode) {

            std::shared_ptr<link> copyPointer = graph->adjList.at(firstNode);
            while(!(copyPointer->next.get() == NULL)) {

                copyPointer = copyPointer.get()->next;
            }

            if(!(graph->AddLink(secondNode, copyPointer))) {

                std::cout << "Error: unable to create and add the link to adjacency list" << std::endl;
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

        // Equivalent to a dfs but using the topological sorting of the graph (adj matrix)
        void DFSTopological(int node, int& count) {

            graph->reverseTopological.at(node) = position;

            graph->strongComponents.at(node) = count;
            for(int i = 0; i < graph->vertices; i++) {

                if(graph->adjMatrix.at(node).at(i) == 1 && graph->reverseTopological.at(i) == -1) {

                    DFSTopological(i, count);
                }
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

        // Function to find the reverse topological sorting of a DAG
        void ReverseTopological(int startNode, int& count) {

            graph->orderVector.at(startNode) = position;
            position++;

            std::shared_ptr<link> nodePointer;
            for(nodePointer = graph->adjList.at(startNode)->next; nodePointer != NULL; 
                nodePointer = nodePointer->next) {

                if(graph->orderVector.at(nodePointer->vert) == -1) {

                    ReverseTopological(nodePointer->vert, count);
                }

                graph->reverseTopological.at(count) = nodePointer->vert;
                count++;
            }
        }

        // Function to find the topological sorting of a DAG
        void Topological(int startNode) {

            int count = 0;
            for(int i = 0; i < graph->vertices; i++) {

                if(graph->orderVector.at(i) == -1) {

                    std::cout << "Entered the recursion" << std::endl;
                    RecursiveTopological(i, count);
                }
            }
        }

        // Recursively find a topological sorting
        void RecursiveTopological(int node, int& count) {

            graph->orderVector.at(node) = position;
            position++;

            for(int i = 0; i < graph->vertices; i++) {

                if(graph->adjMatrix.at(i).at(node)) {

                    if(graph->orderVector.at(i) == -1) {

                        RecursiveTopological(i, count);
                    }
                }
            }

            graph->topological.at(count) = node;
            count++;
        }

        void DAGTransClosure(int node) {

            for(int i = 0; i < graph->vertices; i++) {

                int index = graph->reverseTopological.at(i);
                if(graph->adjMatrix.at(node).at(index) != 0) {

                    graph->dagTransitiveClosure.at(i).at(index) = 1;
                    if(graph->orderVector.at(index) == -1) {

                        DAGTransClosure(index);
                    }

                    for(int p = 0; p < graph->vertices; p++) {

                        if(graph->adjMatrix.at(index).at(p) != 0) {

                            graph->dagTransitiveClosure.at(i).at(p) = 1;
                        }
                    }
                }
            }
        }

        void DagTransitiveClosure() {

            int count = 0;
            // Loop through each vertex to find the reverse topological sort
            for(int i = 0; i < graph->vertices; i++) {

                if(graph->orderVector.at(i) == -1) {

                    ReverseTopological(i, count);
                }
            }

            for(int i = 0; i < graph->vertices; i++) {

                int startNode = graph->reverseTopological.at(i);
                DAGTransClosure(startNode);
            }
        }

        void StrongComponent(int startNode) {

            int count = 0;
            for(int i = 0; i < graph->vertices; i++) {

                if(graph->orderVector.at(i) == -1) {

                    DFSTopological(i, count);
                    count++;
                }
            }
        }
};