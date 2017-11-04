#include <iostream>

#include "Navigation17.h"

int main() {
    Movement m;
    Navigation17 n(&m);

    std::cout << n.getCurrentStateInfo();
    n.goForward();
    std::cout << n.getCurrentStateInfo();



    return 0;
}
