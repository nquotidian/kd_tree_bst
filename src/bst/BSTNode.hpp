#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iomanip>
#include <iostream>
using namespace std;

template <typename Data>

class BSTNode {
  public:
    BSTNode<Data>* left;
    BSTNode<Data>* right;
    BSTNode<Data>* parent;
    Data const data;  // the const Data in this node.

    /** Initialize BSTNode with data, no children and parent
     *  Parameter: d - the data to initialize BSTNode
     */
    BSTNode(const Data& d) : data(d) {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    /* Return successor of the current node
     * cases:
     *    1. Has a right child, go to the most left of right child tree
     *    2. Doesn't have a right child, go up
     *      if it's left child of current node, then the successor is the parent
     *      if it's not the left child, go up until it's left child
     *        or it's null, return nullptr
     */
    BSTNode<Data>* successor() {
        // The current node
        BSTNode<Data>* curr = nullptr;
        // find the successor
        if (this->right != nullptr) {
            curr = this->right;
            while (curr->left != nullptr) curr = curr->left;
            return curr;
        } else {
            curr = this;
            while (curr->parent != nullptr) {
                if (curr->parent->left == curr)
                    return curr->parent;
                else
                    curr = curr->parent;
            }
            return nullptr;
        }
    }
};

/** DO NOT CHANGE THIS METHOD
 *  Overload operator<< to print a BSTNode's fields to an ostream.
 */
template <typename Data>
ostream& operator<<(ostream& stm, const BSTNode<Data>& n) {
    stm << '[';
    stm << setw(10) << &n;                  // address of the BSTNode
    stm << "; p:" << setw(10) << n.parent;  // address of its parent
    stm << "; l:" << setw(10) << n.left;    // address of its left child
    stm << "; r:" << setw(10) << n.right;   // address of its right child
    stm << "; d:" << n.data;                // its data field
    stm << ']';
    return stm;
}

#endif  // BSTNODE_HPP
