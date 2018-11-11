#ifndef AVL_HPP
#define AVL_HPP

#include "avlnode.hpp"

class avl
{
    private:
        avl_node* root;
    public:
        avl();
        void insert(int);
        void remove(int);
        bool isempty();
        bool contains(int);
        void print();
        ~avl();
};
#endif