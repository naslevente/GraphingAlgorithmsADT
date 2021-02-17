/*
    GraphAdtDirected graphDag(SIZE);

    graphDag.AddEdge(0, 2);
    graphDag.AddEdge(0, 5);
    graphDag.AddEdge(1, 0);
    graphDag.AddEdge(2, 1);
    graphDag.AddEdge(3, 2);
    graphDag.AddEdge(3, 4);
    graphDag.AddEdge(4, 5);
    graphDag.AddEdge(5, 4);

    std::vector<std::vector<uint>> adjMatrix = graphDag.getAdjacencyMatrix();
    graphDag.TransitiveClosure();
    std::vector<std::vector<uint>> transitiveClosure = graphDag.getTransitiveClosure();
    
    OutputMatrix(transitiveClosure);
    */


    /*
    size_t SIZE = 8;
    GraphAdtUndirected graph(SIZE);

    graph.AddEdge(0, 2);
    graph.AddEdge(0, 7);
    graph.AddEdge(0, 5);

    graph.AddEdge(2, 6);
    graph.AddEdge(6, 4);
    graph.AddEdge(7, 1);
    graph.AddEdge(5, 3);

    graph.AddEdge(4, 7);
    graph.AddEdge(4, 3);
    graph.AddEdge(4, 5);

    graph.DepthFirstSearchList(0);

    // Function to handle the member function pointers 
        void CallFunction(void (GraphAdtDirected::*func) (int, int&), int startNode, int& count) {

            std::cout << "calling recursive function" << std::endl;
            return (this->*func)(startNode, count);
        }

    */