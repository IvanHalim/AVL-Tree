#ifndef AVL_HPP
#define AVL_HPP

class avl {
    private:
        struct avl_node;
        avl_node* root;
    public:
        avl();
        void insert(int);
        void remove(int);
        bool isempty();
        bool contains(int);
        int height();
        int size();
        void print();
        ~avl();
};
#endif