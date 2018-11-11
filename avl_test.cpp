#include <iostream>
#include "avl.hpp"

using std::cout;
using std::endl;

int main() {
    avl myAvl;
    cout << std::boolalpha << myAvl.isempty() << endl;
    myAvl.insert(48);
    myAvl.insert(32);
    myAvl.insert(40);
    myAvl.insert(8);
    myAvl.insert(64);
    myAvl.remove(32);
    myAvl.insert(4);
    cout << std::boolalpha << myAvl.isempty() << endl;
    cout << std::boolalpha << myAvl.contains(96) << endl;
    cout << std::boolalpha << myAvl.contains(32) << endl;
    myAvl.print();

    return 0;
}