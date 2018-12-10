#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <queue>
#include <cassert>
#include "avl.hpp"

using std::queue;

class avl::iterator {
    private:
        queue<int> items;
    public:
        void insert(int);
        bool has_next();
        int  next();
};

void avl::iterator::insert(int val) {
    items.push(val);
}

bool avl::iterator::has_next() {
    return !items.empty();
}

int avl::iterator::next() {
    assert(has_next());
    int next_item = items.front();
    items.pop();
    return next_item;
}

#endif