#ifndef AVL_HPP
#define AVL_HPP

#include <queue>
#include <string>

using std::queue;
using std::string;

class avl {
    public:
        struct node;

        class iterator {
            private:
                queue<int> items;
            public:
                void insert(int val);
                bool has_next();
                int  next();
        };

    private:
        node*  root;
    public:
        avl();
        void        insert(int);
        void        remove(int);
        bool        isempty();
        bool        contains(int);
        bool        path_sum(int);
        int         height();
        int         size();
        void        print();
        iterator    iterator_create(string);
        ~avl();
};

#endif