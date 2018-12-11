#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <queue>
#include <cassert>
#include "avl.hpp"

using std::queue;

class iterator {
    private:
        queue<int> items;
    public:
        void insert(int);
        bool has_next();
        int  next();
};

void iterator::insert(int val) {
    items.push(val);
}

bool iterator::has_next() {
    return !items.empty();
}

int iterator::next() {
    assert(has_next());
    int next_item = items.front();
    items.pop();
    return next_item;
}

#endif