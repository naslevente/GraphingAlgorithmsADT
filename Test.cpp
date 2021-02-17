#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <ostream>

int main() {

    int something = 5;
    int somethingelse = std::move(something);

    std::cout << "Something: " << something << std::endl;
    std::cout << "Somethingelse: " << somethingelse << std::endl;

    somethingelse = 7;

    std::cout << "Something: " << something << std::endl;
    std::cout << "Somethingelse: " << somethingelse << std::endl;
}
