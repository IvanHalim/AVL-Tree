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
        avl_node* _avl_rotate_left(avl_node*);
        avl_node* _avl_rotate_right(avl_node*);
        int _avl_balance_factor(avl_node*);
        avl_node* _avl_balance(avl_node*);
        avl_node* _avl_subtree_insert(int, avl_node*);
        int _avl_subtree_min_val(avl_node*);
        avl_node* _avl_subtree_remove(int, avl_node*);
        int _avl_subtree_size(avl_node*);
        bool _avl_subtree_path_sum(int, avl_node*);
        void _avl_subtree_print(avl_node*, int);
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