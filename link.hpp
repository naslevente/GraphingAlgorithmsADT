#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>

#ifndef LINKHEADER
#define LINKHEADER

class link {

    public:

        int vert;
        std::shared_ptr<link> next;

        link(int vertNum) : vert(vertNum) {}
};
#endif