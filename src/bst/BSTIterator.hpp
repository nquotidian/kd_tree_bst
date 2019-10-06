#ifndef BSTITERATOR_HPP
#define BSTITERATOR_HPP
#include <iterator>
#include <list>
#include "BSTNode.hpp"
using namespace std;

template <typename Data>
class BSTIterator : public iterator<input_iterator_tag, Data> {
  private:
    BSTNode<Data>* curr;

  public:
    /** Constructor that initialize the current BSTNode
     *  in this BSTIterator.
     */
    BSTIterator(BSTNode<Data>* curr) : curr(curr) {}

    /** Dereference operator. */
    Data operator*() const { return curr->data; }

    /** Pre-increment operator. */
    BSTIterator<Data>& operator++() {
        curr = curr->successor();
        return *this;
    }

    /** Post-increment operator. */
    BSTIterator<Data> operator++(int) {
        BSTIterator before = BSTIterator(curr);
        ++(*this);
        return before;
    }

    /* Compare two iterators
     * true: if two iterators both hold a pointer to the same BSTNode
     * false: not the same pointer
     */
    bool operator==(BSTIterator<Data> const& other) const {
        if (this->curr == other.curr)
            return true;
        else
            return false;
    }

    /* Compare two iterators */
    bool operator!=(BSTIterator<Data> const& other) const {
        if (this->curr != other.curr)
            return true;
        else
            return false;
    }
};

#endif  // BSTITERATOR_HPP
