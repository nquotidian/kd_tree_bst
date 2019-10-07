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

    /** Destructor */
    virtual ~BST() {
        deleteAll(root);
        iheight = -1;
        isize = 0;
    }

    /** Insert a node in BST
     *  return false if the node already exists
     *  recursively or while loop
     *  virtual: member function defined on the base class
     */
    virtual bool insert(const Data& item) {
        BSTNode<Data>* node = new BSTNode<Data>(item);
        // If the tree is empty
        if (root == nullptr) {
            root = node;
            iheight++;
            isize++;
            return true;
        }
        BSTNode<Data>* curr = root;
        while ((item < curr->data) || (curr->data < item)) {
            if (item < curr->data) {
                if (curr->left == nullptr) {
                    curr->left = node;
                    iheight = height();
                    isize++;
                    return true;
                } else {
                    curr = curr->left;
                }
            } else if (curr->data < item) {
                if (curr->right == nullptr) {
                    curr->right = node;
                    iheight = height();
                    isize++;
                    return true;
                } else {
                    curr = curr->right;
                }
            }
        }
        free(node);
        return false;
    }

    /** Find a data item in BST */
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

    /** Return the size of BST */
    unsigned int size() const { return isize; }

    /** Return the size of BST */
    int height() const { return height_helper(root); }

    /** Return true if BST is empty */
    bool empty() const {
        if (root == nullptr)
            return true;
        else
            return false;
    }

    /** Return the first node of BST */
    iterator begin() const { return BST::iterator(first(root)); }

    /** Return an iterator pointing past the last item in the BST.
     */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** TODO
     * for debugging
     */
    vector<Data> inorder() const {
        vector<Data> vec(isize);
        inorder_helper(root, vec);
        return vec;
    }

  private:
    /** Find the first item of BST */
    static BSTNode<Data>* first(BSTNode<Data>* root) {
        BSTNode<Data>* curr = root;
        while (curr->left != nullptr) {
            curr = curr->left;
        }
        return curr;
    }

    /** Helper method for ~BST() */
    static void deleteAll(BSTNode<Data>* n) {
        /* Pseudocode:
           if current node is null: return;
           recursively delete left sub-tree
           recursively delete right sub-tree
           delete current node
        */
        if (n == nullptr) {
            return;
        } else {
            deleteAll(n->left);
            deleteAll(n->right);
            delete n;
        }
    }

    /** Helper method for inorder() */
    static void inorder_helper(BSTNode<Data>* n, vector<Data>& vec) {
        if (n == nullptr) {
            return;
        }
        inorder_helper(n->left, vec);
        vec.push_back(n->data);
        inorder_helper(n->right, vec);
    }

    /** Helper method for height() */
    static int height_helper(BSTNode<Data>* n) {
        if (n == nullptr) return -1;
        int left_height = height_helper(n->left);
        int right_height = height_helper(n->right);
        if (left_height > right_height)
            return left_height + 1;
        else
            return right_height + 1;
    }
};

#endif  // BST_HPP

// run the time command ./build/....
