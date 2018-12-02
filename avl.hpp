#ifndef AVL_HPP
#define AVL_HPP

struct avl_node;

class avl {
    private:
        avl_node* root;
    public:
        avl();
        void insert(const int&);
        void remove(const int&);
        bool isempty();
        bool contains(const int&);
        bool path_sum(const int&);
        int height();
        int size();
        void print();
        ~avl();
};
#endif