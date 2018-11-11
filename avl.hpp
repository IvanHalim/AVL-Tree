#ifndef AVL_HPP
#define AVL_HPP

struct avl_node {
    int val;
    avl_node* left;
    avl_node* right;
    int height;
};

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