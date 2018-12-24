#include <iostream>
#include "avl.hpp"

using std::cout;
using std::endl;
using std::boolalpha;

void display_iterator(avl::iterator it) {
    while (it.has_next()) {
        cout << it.next() << ' ';
    }
    cout << endl;
}

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
    cout << myAvl.size() << endl;
    cout << boolalpha << myAvl.path_sum(64) << endl;
    cout << boolalpha << myAvl.path_sum(96) << endl;

    avl::iterator in_order = myAvl.iterator_create("in-order");
    display_iterator(in_order);
    avl::iterator pre_order = myAvl.iterator_create("pre-order");
    display_iterator(pre_order);
    avl::iterator post_order = myAvl.iterator_create("post-order");
    display_iterator(post_order);
    avl::iterator level_order = myAvl.iterator_create("level-order");
    display_iterator(level_order);

    return 0;
}