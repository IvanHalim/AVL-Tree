#ifndef AVL_HPP
#define AVL_HPP

class avl {
    private:
        struct avl_node;
        avl_node* root;

        // Helper functions
        avl_node* _avl_node_create();
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