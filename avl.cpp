#include <iostream>
#include "avl.hpp"

using std::cout;
using std::endl;

struct avl::avl_node {
    int val;
    avl_node* left;
    avl_node* right;
    int height;
};

avl::avl() {
    root = NULL;
}

bool avl::isempty() {
    return root == NULL;
}

/*
 * Helper function to generate a single AVL node containing a given value.
 */
avl::avl_node* avl::_avl_node_create(int val) {
    avl_node* n = new avl_node;
    n->val = val;
    n->left = n->right = NULL;
    n->height = 0;
    return n;
}

/*
 * Helper function to get a node's height, even if the node is NULL (in which
 * case the height is -1).
 */
int _avl_get_height(avl_node* n) {
    if (n == NULL) {
        return -1;
    }
    return n->height;
}

int avl::height() {

    // The height of the tree is simply the height of the subtree rooted at root
    return _avl_get_height(root);
}

/*
 * Helper function to update the height of a node, based on the height of
 * its children.
 */
void _avl_update_height(avl_node* n) {
    int lh = _avl_get_height(n->left);
    int rh = _avl_get_height(n->right);

    // Height is 1 more than the maximum child height.
    if (lh > rh) {
        n->height = lh + 1;
    } else {
        n->height = rh + 1;
    }
}

/*
 * This function performs a left rotation on the subtree rooted at a given
 * node.  The rotation is centered around the node's right child.  The new
 * subtree root (the rotation's center) is returned.
 */
avl::avl_node* _avl_rotate_left(avl_node* n) {
    avl_node* center = n->right;

    // The center's left child and n "trade places" in the tree.
    n->right = center->left;
    center->left = n;

    _avl_update_height(n);
    _avl_update_height(center);

    return center;
}

/*
 * This function performs a right rotation on the subtree rooted at a given
 * node.  The rotation is centered around the node's right child.  The new
 * subtree root (the rotation's center) is returned.
 */
avl::avl_node* _avl_rotate_right(avl_node* n) {
    avl_node* center = n->left;

    // The center's right child and n "trade places" in the tree.
    n->left = center->right;
    center->right = n;

    _avl_update_height(n);
    _avl_update_height(center);

    return center;
}

/*
 * Helper function to compute a node's balance factor, which is the signed
 * difference in heights between its right subtree and left subtree.  A
 * negative balance factor means the node is left-heavy, a positive balance
 * factor means the node is right-heavy, and a zero balance factor means the
 * node is height-balanced.
 */
int _avl_balance_factor(avl_node* n) {
    return _avl_get_height(n->right) - _avl_get_height(n->left);
}

avl::avl_node* _avl_balance(avl_node* n) {

    int bf = _avl_balance_factor(n);
    if (bf < -1) {

        /*
         * Here, n is height-imbalanced on the left.  We need a double rotation if
         * n’s left child is right-heavy.
         */
        if (_avl_balance_factor(n->left) > 0) {
            n->left = _avl_rotate_left(n->left);
        }
        return _avl_rotate_right(n);

    } else if (bf > 1) {

        /*
         * Here, n is height-imbalanced on the right.  We need a double rotation if
         * n’s right child is left-heavy.
         */
        if (_avl_balance_factor(n->right) < 0) {
            n->right = _avl_rotate_right(n->right);
        }
        return _avl_rotate_left(n);

    } else {

        // Just update the height if we didn’t rotate.
        _avl_update_height(n);
        return n;
    }
}

/*
 * Helper function to insert a given value into a subtree of a AVL rooted at
 * a given node.  Operates recursively by determining into which subtree (left
 * or right) under the given node the value should be inserted and performing
 * the insertion on that subtree.
 *
 * Returns the root of the given subtree, modified to contain a new node with
 * the specified value.
 */
avl::avl_node* _avl_subtree_insert(int val, avl_node* n) {

    if (n == NULL) {

        /*
         * If n is NULL, we know we've reached a place to insert val, so we
         * create a new node holding val and return it.
         */
        return _avl_node_create(val);

    } else if (val < n->val) {

        /*
         * If val is less than the value at n, we insert val in n's left subtree
         * (somewhere) and update n->left to point to the modified subtree (with
         * val inserted).
         */
        n->left = _avl_subtree_insert(val, n->left);

    } else {

        /*
         * If val is greater than or equal to the value at n, we insert val in n's
         * right subtree (somewhere) and update n->right to point to the modified
         * subtree (with val inserted).
         */
        n->right = _avl_subtree_insert(val, n->right);

    }

    /*
     * For the else if and else conditions, the subtree rooted at n has already
     * been modified (by setting n->left or n->right above), so we can just
     * return n here, after balancing n's subtree.
     */
    return _avl_balance(n);
}

void avl::insert(int val) {

    /*
     * We insert val by using our subtree insertion function starting with the
     * subtree rooted at root (i.e. the whole tree).
     */
    root = _avl_subtree_insert(val, root);
}

/*
 * Helper function to return the minimum value in a subtree of a AVL.
 */
int _avl_subtree_min_val(avl_node* n) {

    /*
     * The minimum value in any subtree is just the leftmost value.  Keep going
     * left till we get there.
     */
    while (n->left != NULL) {
        n = n->left;
    }
    return n->val;
}

/*
 * Helper function to remove a given value from a subtree of a AVL rooted at
 * a specified node.  Operates recursively by figuring out whether val is in
 * the left or the right subtree of the specified node and performing the
 * remove operation on that subtree.
 *
 * Returns the potentially new root of the given subtree, modified to have
 * the specified value removed.
 */
avl::avl_node* _avl_subtree_remove(int val, avl_node* n) {

    if (n == NULL) {

        /*
         * If n is NULL, that means we've reached a leaf node without finding
         * the value we wanted to remove.  The tree won't be modified.
         */
        return NULL;

    } else if (val < n->val) {

        /*
         * If val is less than n, remove val from n's left subtree and update
         * n->left to point to the modified subtree (with val removed).  Return
         * n, whose subtree itself has now been modified, after balancing that
         * subtree.
         */
        n->left = _avl_subtree_remove(val, n->left);
        return _avl_balance(n);

    } else if (val > n->val) {

        /*
         * If val is greater than n, remove val from n's right subtree and update
         * n->right to point to the modified subtree (with val removed).  Return
         * n, whose subtree itself has now been modified, after balancing that
         * subtree.
         */
        n->right = _avl_subtree_remove(val, n->right);
        return _avl_balance(n);

    } else {

        /*
         * If we've reached this point, we've found a node with value val.  We
         * need to remove this node from the tree, and the way we do that will
         * differ based on whether the node has 0, 1, or 2 children.
         */
        if (n->left != NULL && n->right != NULL) {

            /*
             * If n has 2 children, we replace the value at n with the value at n's
             * in-order successor node, which is the minimum value in n's right
             * subtree.  Then we recursively remove n's in-order successor node from
             * the tree (specifically from n's right subtree).  Balance n before
             * returning it
             */
            n->val = _avl_subtree_min_val(n->right);
            n->right = _avl_subtree_remove(n->val, n->right);
            return _avl_balance(n);

        } else if (n->left != NULL) {

            /*
             * If n has only a left child, we simply delete n by freeing it and
             * returning the left child node so that it becomes the new child of
             * n's parent via the recursion.  We don't need to balance the left
             * child before returning, since it should already be balanced.
             */
            avl_node* left_child = n->left;
            delete n;
            return left_child;

        } else if (n->right != NULL) {

            /*
             * If n has only a right child, we simply delete n by freeing it and
             * returning the right child node so that it becomes the new child of
             * n's parent via the recursion.  We don't need to balance the right
             * child before returning, since it should already be balanced.
             */
            avl_node* right_child = n->right;
            delete n;
            return right_child;

        } else {

            /*
             * Otherwise, n has no children, and we can simply free it and return
             * NULL so that n's parent will lose n as a child via the recursion.
             */
            delete n;
            return NULL;
        }
    }
}

void avl::remove(int val) {

    /*
     * We remove val by using our subtree removal function starting with the
     * subtree rooted at root (i.e. the whole tree).
     */
    root = _avl_subtree_remove(val, root);
}

bool avl::contains(int val) {

    // Iteratively search for val in t.
    avl_node* cur = root;
    while (cur != NULL) {

        if (val == cur->val) {

            // We found the value we're looking for in cur.
            return true;

        } else if (val < cur->val) {

            /*
             * The value we're looking for is less than the value at cur, so we
             * branch left.
             */
            cur = cur->left;

        } else {

            /*
             * The value we're looking for is greater than or equal to the value at
             * cur, so we branch right.
             */
            cur = cur->right;
        }
    }

    /*
     * If we make it to a leaf node (i.e. cur is NULL), we didn't find what we
     * were looking for.
     */
    return false;
}

/*
 * Helper function to return the number of nodes in a subtree of a AVL rooted at
 * a specified node.
 */
int _avl_subtree_size(avl_node* n) {

    // If n is null then the subtree has no node in it.
    if (n == NULL)
        return 0;

    /*
     * The number of nodes is the sum of the nodes in the left subtree and the nodes
     * in the right subtree, plus this node.
     */
    return 1 + _avl_subtree_size(n->left) + _avl_subtree_size(n->right);
}

int avl::size() {

    /*
     * We return the size of the tree by using our subtree size function starting with
     * the subtree rooted at root.
     */
    return _avl_subtree_size(root);
}

/*
 * Helper function to determine if a subtree of a AVL rooted at a specified node has
 * a path from the root to a leaf in which the node values sum to a specified value.
 * Operates recursively by searching through the left subtree and the right subtree.
 * If at least one of the child has a path which adds up to sum, then the subtree
 * has a path which adds up to sum.
 */
bool _avl_subtree_path_sum(int sum, avl_node* n) {

    if (n == NULL) {

        /*
         * If n is NULL, that means previously we've reached a leaf node without
         * finding a path that adds up to sum.
         */
        return false;

    } else if (n->left == NULL && n->right == NULL) {

        /*
         * If this node has no child, that means this is a leaf node.
         * See if the value of this node is equal to sum.
         */
        return n->val == sum;

    } else if (_avl_subtree_path_sum(sum - n->val, n->left)) {

        /*
         * Assuming the subtree has a path that adds up to sum, then
         * its child subtree should have a path that adds up to sum
         * minus the value of its parent node. Search the left subtree
         * if it has a path that adds up to sum - n->val.
         */
        return true;

    } else if (_avl_subtree_path_sum(sum - n->val, n->right)) {

        /*
         * Search the right subtree if it has a path that adds up to
         * sum - n->val.
         */
        return true;
    }

    /*
     * If we make it this far and we still haven't found a path that
     * adds up to sum then the subtree has no path that adds up to sum.
     */
    return false;
}

bool avl::path_sum(int sum) {

    /*
     * We determine if the AVL tree has a path that adds up to sum by
     * using our subtree path sum function starting with the subtree
     * rooted at root.
     */
    return _avl_subtree_path_sum(sum, root);
}

void _avl_subtree_print(avl_node* n, int level) {
    if (n == NULL) {
        return;
    }
    for (int i = 0; i < level; i++) {
        cout << "  ";
    }
    cout << n->val << endl;
    _avl_subtree_print(n->left, level + 1);
    _avl_subtree_print(n->right, level + 1);
}

void avl::print() {
    if (root == NULL) {
        cout << "EMPTY" << endl;
    } else {
        _avl_subtree_print(root, 0);
    }
}

avl::~avl() {
    while (!isempty()) {
        remove(root->val);
    }
}
