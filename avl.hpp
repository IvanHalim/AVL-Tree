#ifndef AVL_HPP
#define AVL_HPP

class avl {
    private:
        avl_node* root;
    public:
        struct avl_node;
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