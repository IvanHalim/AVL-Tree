#include <iostream>
#include "avl.hpp"

using std::cout;
using std::endl;

int main() {
    avl myAvl;
    myAvl.insert(96);
    myAvl.insert(16);
    myAvl.insert(48);
    myAvl.insert(32);
    myAvl.insert(40);
    myAvl.insert(8);
    myAvl.insert(64);
    myAvl.remove(32);
    myAvl.insert(4);
    myAvl.print();
    cout << myAvl.height() << endl;

    return 0;
}