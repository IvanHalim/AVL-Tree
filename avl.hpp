#ifndef AVL_HPP
#define AVL_HPP

struct avl_node;

class avl {
    private:
        avl_node* root;
    public:
        avl();
        void insert(int);
        void remove(int);
        bool isempty();
        bool contains(int);
        bool path_sum(int);
        int height();
        int size();
        void print();
        ~avl();
};
#endif