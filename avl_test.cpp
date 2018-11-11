#include <iostream>
#include "avl.hpp"

int main() {
    avl myAvl;
    myAvl.insert(48);
    myAvl.insert(32);
    myAvl.insert(40);
    myAvl.insert(8);
    myAvl.insert(64);
    myAvl.remove(32);
    myAvl.insert(4);
    myAvl.print();

    return 0;
}