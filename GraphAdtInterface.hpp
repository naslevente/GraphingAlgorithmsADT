#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <ostream>
#include <stack>
#include <vector>

#ifndef INTERFACE
#define INTERFACE

class GraphAdtInterface {

    protected:

        int graphSize;
        int position = 0;

        std::vector<int> low;
};

#endif