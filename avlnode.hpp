#ifndef AVLNODE_HPP
#define AVLNODE_HPP

struct avl_node {
    int val;
    avl_node* left;
    avl_node* right;
    int height;
};
#endif