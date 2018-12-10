#ifndef AVL_HPP
#define AVL_HPP

class avl {
    private:
        struct avl_node;
        avl_node* root;

        // Helper functions
        avl_node* _avl_node_create(int);
        int _avl_get_height(avl_node*);
        void _avl_update_height(avl_node*);
        avl_node* _avl_rotate_left(avl_node* n);
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