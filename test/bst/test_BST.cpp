#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "BST.hpp"
#include "util.hpp"

using namespace std;
using namespace testing;

/* Empty BST test starts here */

TEST(BSTTests, EMPTY_TREE_HEIGHT_TEST) {
    BST<int> bst;
    ASSERT_EQ(bst.height(), -1);
}

TEST(BSTTests, EMPTY_TREE_TEST) {
    BST<int> bst;
    ASSERT_TRUE(bst.empty());
}

/* Small BST test starts here */

/**
 * A simple test fixture from which multiple tests
 * can be created. All fixture tests (denoted by the
 * TEST_F macro) can access the protected members of this
 * fixture. Its data is reset after every test.
 *
 * Builds the following BST:
 *         3
 *        / \
 *       1   4
 *      /     \
 *    -33     100
 */
class SmallBSTFixture : public ::testing::Test {
  protected:
    BST<int> bst;

  public:
    SmallBSTFixture() {
        // initialization code here
        vector<int> input{3, 4, 1, 100, -33};
        insertIntoBST(input, bst);
    }
    // code in SetUp() will execute just before the test ensues
    // void SetUp() {}
};

/* BST test starts here */

/**
 * Builds the following BST:
 *         3
 *        / \
 *       1   4
 *      / \
 *    -33  2
 */
class BSTFixture : public ::testing::Test {
  protected:
    BST<int> bst_2;

  public:
    BSTFixture() {
        // initialization code here
        vector<int> input{3, 4, 1, -33, 2};
        insertIntoBST(input, bst_2);
    }
    // code in SetUp() will execute just before the test ensues
    // void SetUp() {}
};

TEST_F(SmallBSTFixture, SMALL_SIZE_TEST) {
    // assert that the small BST has the correct size
    ASSERT_EQ(bst.size(), 5);
}

TEST_F(SmallBSTFixture, SMALL_INSERT_DUPLICATES_TEST) {
    // assert failed duplicate insertion
    ASSERT_FALSE(bst.insert(3));
}

// TODO: add more BST tests here
TEST_F(SmallBSTFixture, SMALL_HEIGHT_TEST) {
    // assert that the small BST has the correct height
    ASSERT_EQ(bst.height(), 2);
}

TEST_F(SmallBSTFixture, NON_EMPTY_TREE_TEST) {
    // assert that the small BST is not empty
    ASSERT_FALSE(bst.empty());
}

TEST_F(SmallBSTFixture, FIND_TEST) {
    // assert that the value found
    BSTIterator<int> ite = bst.find(100);
    ASSERT_EQ(*ite, 100);
}

TEST_F(SmallBSTFixture, FIND_TEST_2) {
    // assert that the value found
    BSTIterator<int> ite = bst.find(-33);
    ASSERT_EQ(*ite, -33);
}

TEST_F(SmallBSTFixture, BEGIN_TEST) {
    // assert that the begin value is correct
    BSTIterator<int> i = bst.begin();
    ASSERT_EQ(*i, -33);
}

TEST_F(SmallBSTFixture, END_TEST) {
    // assert that the end equal to iterator(nullptr)
    BSTIterator<int> ite = bst.end();
    BSTIterator<int> i(nullptr);
    ASSERT_EQ(ite, i);
}

TEST_F(SmallBSTFixture, ITERATOR_PP_TEST) {
    // expect that the ++ operation is valid
    BSTIterator<int> ite = bst.find(1);
    ++ite;
    EXPECT_EQ(*ite, 3);
}

TEST_F(BSTFixture, ITERATOR_PP_TEST_2) {
    // assert that the value found
    BSTIterator<int> ite = bst_2.find(2);
    ++ite;
    ASSERT_EQ(*ite, 3);
}

TEST_F(SmallBSTFixture, ITERATOR_EQ_TEST) {
    // expect that the iterators are equal
    BSTIterator<int> ite = bst.find(3);
    BSTIterator<int> i = bst.find(4);
    ++ite;
    bool eq = (ite == i) ? true : false;
    bool ne = (ite != i) ? true : false;
    EXPECT_TRUE(eq);
    EXPECT_FALSE(ne);
}

TEST_F(SmallBSTFixture, ITERATOR_NE_TEST) {
    // expect that the iterators are not equal
    BSTIterator<int> ite = bst.find(4);
    BSTIterator<int> i = bst.find(100);
    bool eq = (ite == i) ? true : false;
    EXPECT_FALSE(eq);
}

TEST_F(SmallBSTFixture, INORDER_TEST) {
    // assert that the size of vectors are equal
    // expect that the element of vectors are the same
    vector<int> x = bst.inorder();
    vector<int> y{-33, 1, 3, 4, 100};
    ASSERT_EQ((unsigned)x.size(), (unsigned)y.size());
    for (unsigned int i = 0; i < x.size(); i++) {
        EXPECT_EQ(x[i], y[i]);
    }
}