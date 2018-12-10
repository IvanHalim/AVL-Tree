#ifndef AVL_HPP
#define AVL_HPP

#include <queue>
#include <cassert>
#include "iterator.hpp"

using std::queue;

class avl {
    public:
        struct node;
        class  iterator;
    private:
        node* root;
    public:
        avl();
        void        insert(int);
        void        remove(int);
        bool        isempty();
        bool        contains(int);
        bool        path_sum(int);
        int         height();
        int         size();
        void        print();
        iterator    iterator_create();
        ~avl();
};

#endif