#ifndef AVL_HPP
#define AVL_HPP

class avl {
    public:
        struct node;
    private:
        node* root;
    public:
        avl();
        void  insert(int);
        void  remove(int);
        bool  isempty();
        bool  contains(int);
        bool  path_sum(int);
        int   height();
        int   size();
        void  print();
        ~avl();
};
#endif