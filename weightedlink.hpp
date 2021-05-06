#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>
#include "link.hpp"

#ifndef WEIGHTEDLINK
#define WEIGHTEDLINK

class weightedlink {

    public:

        int weight;
        int vert;
        std::shared_ptr<weightedlink> next;

        weightedlink(int vertNum) : vert(vertNum) {}
};

#endif