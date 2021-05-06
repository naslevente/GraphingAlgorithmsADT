#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <ostream>

#include <vector>
#include "DirectedGraph.hpp"
#include "GraphAdtInterface.hpp"

class GraphAdtUndirected : GraphAdtInterface {

    private:

        int graphSize;
        int position = 1;
        std::unique_ptr<Graph> graph;

    public:

        void ResetGraphTraversal() {

            for(int i = 0; i < graph->vertices; i++) {

                graph->orderVector.at(i) = -1;
            }
            position = 1;
        }

        GraphAdtUndirected(size_t numVert) {

            graphSize = numVert;

            // Create the graph for both the matrix and list representations
            graph = std::make_unique<Graph>(numVert);
        }

        ~GraphAdtUndirected() {}

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

                std::cout << "added " << firstNode << " and " << secondNode << " to the graph" << std::endl;
            }
        }

        // Add to graph fuinction for adj list for an undurected graph
        bool AddToList(int firstNode, int secondNode) {

            std::shared_ptr<link> copyPointer = graph->adjList.at(firstNode);
            while(!(copyPointer->next.get() == NULL)) {

                copyPointer = copyPointer.get()->next;
            }

            if(!(graph->AddLink(secondNode, copyPointer))) {

                std::cout << "Error: unable to create and add the link to adjacency list" << std::endl;
                return false;
            }

            copyPointer = graph->adjList.at(secondNode);
            while(!(copyPointer->next == NULL)) {

                copyPointer = copyPointer.get()->next;
            }

            if(!(graph->AddLink(firstNode, copyPointer))) {

                std::cout << "Error: unable to create and add the link to adjacency list" << std::endl;
                return false;
            }

            return true;
        }

        bool AddToMatrix(int firstNode, int secondNode) {

            // Assuming this edge has not already been added to the matrix and 
            // that the edge is being added to an undirected graph
            graph->adjMatrix.at(firstNode).at(secondNode) = 1;
            graph->adjMatrix.at(secondNode).at(firstNode) = 1;

            return true;
        }

        // Depth first search on adjacency list
        void DepthFirstSearchList(int node) {

            graph->orderVector.at(node) = position;
            position++;

            std::shared_ptr<link> nodePointer;
            for(nodePointer = graph->adjList.at(node)->next; nodePointer != NULL; nodePointer = nodePointer->next) {

                if(graph->orderVector.at(nodePointer->vert) == 0) {

                    std::cout << node << "-" << nodePointer->vert << " Tree" << std::endl;
                    DepthFirstSearchList(nodePointer->vert);
                }
                else {

                    std::cout << node << "-" << nodePointer->vert << " Back" << std::endl;
                }
            }
        }

        // Depth first search on adjacency matrix
        void DepthFirstSearchMatrix(int node) {

            graph->orderVector.at(node) = position++;
            position++;

            for(int i = 0; i < graph->adjList.size(); i++) {

                if(graph->orderVector.at(i) == -1 && graph->adjMatrix.at(node).at(i) == 1) {

                    std::cout << node << "-" << i << " Tree" << std::endl;
                    DepthFirstSearchMatrix(i);
                }
                else {

                    std::cout << node << "-" << i << " Back" << std::endl;
                }
            }
        }
};