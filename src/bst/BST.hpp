#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include <vector>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;

template <typename Data>
class BST {
  protected:
    // pointer to the root of this BST, or 0 if the BST is empty
    BSTNode<Data>* root;

    // number of Data items stored in this BST.
    unsigned int isize;

    // height of this BST.
    int iheight;

  public:
    /** Define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /** Default constructor.
     *  Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(-1) {}

    /** TODO */
    virtual ~BST() { deleteAll(root); }

    /** TODO
     * recursively or while loop
     * virtual: member function defined on the base class
     */
    virtual bool insert(const Data& item) {
        BSTNode<Data> i_node(item);
        // If the tree is empty
        if (root == nullptr) {
            root = &i_node;
            isize++;
            iheight++;
            return true;
        }
        BSTNode<Data>* curr = root;
        while ((item < curr->data) || (curr->data < item)) {
            if (item < curr->data) {
                if (curr->left == nullptr) {
                    curr->left = &i_node;
                    iheight++;
                    isize++;
                    return true;
                } else {
                    curr = curr->left;
                }
            } else if (curr->data < item) {
                if (curr->right == nullptr) {
                    curr->right = &i_node;
                    iheight++;
                    isize++;
                    return true;
                } else {
                    curr = curr->right;
                }
            }
        }
        return false;
    }

    /** TODO */
    virtual iterator find(const Data& item) const {
        BSTNode<Data>* curr = root;
        while ((item < curr->data) || (curr->data < item)) {
            if (item < curr->data) {
                curr = curr->left;
            } else if (curr->data < item) {
                curr = curr->right;
            } else if (curr == nullptr) {
                return nullptr;
            } else {
                return curr;
            }
        }
    }

    /** TODO */
    unsigned int size() const { return isize; }

    /** TODO */
    int height() const { return iheight; }

    /** TODO */
    bool empty() const { return false; }

    /** TODO */
    iterator begin() const { return BST::iterator(first(root)); }

    /** Return an iterator pointing past the last item in the BST.
     */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** TODO
     * for debugging
     */
    vector<Data> inorder() const {}

  private:
    /** TODO */
    static BSTNode<Data>* first(BSTNode<Data>* root) { return 0; }

    /** TODO */
    static void deleteAll(BSTNode<Data>* n) {
        /* Pseudocode:
           if current node is null: return;
           recursively delete left sub-tree
           recursively delete right sub-tree
           delete current node
        */
    }
};

#endif  // BST_HPP

// run the time command ./build/....
