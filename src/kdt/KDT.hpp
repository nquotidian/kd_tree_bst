#ifndef KDT_HPP
#define KDT_HPP

#include <math.h>     // pow, abs
#include <algorithm>  // sort, max, min
#include <limits>     // numeric_limits<type>::max()
#include <vector>     // vector<typename>
#include "Point.hpp"

using namespace std;

class KDT {
  private:
    /** Inner class which defines a KD tree node */
    class KDNode {
      public:
        KDNode* left;
        KDNode* right;
        Point point;

        KDNode(Point point) : point(point) {}
    };

    // root of KD tree
    KDNode* root;

    // number of dimension of data points
    unsigned int numDim;

    // smallest squared distance to query point so far
    double threshold;

    unsigned int isize;
    int iheight;

    // current nearest neighbor
    Point nearestNeighbor;

    // Extra Credit: smallest bounding box containing all points
    vector<pair<double, double>> boundingBox;

    // Extra Credit: result container
    // (Set during searching, and clear before another search)
    vector<Point> pointsInRange;

  public:
    /** Constructor of KD tree */
    KDT()
        : root(0),
          numDim(0),
          threshold(numeric_limits<double>::max()),
          isize(0),
          iheight(-1) {}

    /** Destructor of KD tree */
    virtual ~KDT() {
        deleteAll(root);
        iheight = -1;
        isize = 0;
    }

    /** build kd tree
     *  if(points.empty())
     *    return;
     *  root = buildSubtree(points, 0, points.size()-1, 1, -1)
     *
     */
    void build(vector<Point>& points) {
        if (points.empty()) return;
        // initial call when building a kd tree
        root = buildSubtree(points, 0, points.size() - 1, 0, iheight);
    }

    /** TODO */
    Point* findNearestNeighbor(Point& queryPoint) { return nullptr; }

    /** Extra credit */
    vector<Point> rangeSearch(vector<pair<double, double>>& queryRegion) {
        return {};
    }

    /** Return the size of the KD tree */
    unsigned int size() const { return isize; }

    /** Return the height of the KD tree */
    int height() const { return iheight; }

  private:
    /** TODO
     *  Recursively
     *  ~ build() method call buildSubtree
     *  points:  vector with all the data points to build the KD tree
     *  start: the inclusive start index of the points vector during building
     * subtree end: the exclusive end index of the points vector during building
     * subtree curDim: the current dimension during building subtree height: the
     * current height during building subtree
     *
     *  pusedocode:
     *  int medi;
     *  KDNode* node = nullptr;
     *  if(start<=end)
     *      sort(start, end, curDim)      // sort according to the current
     * dimension medi = floor((start+end)/2);  // set the medi to the middle
     * node node = new KDNode(points[medi]); isize++; node.left =
     * buildSubtree(points, start, medi-1, curDim+1, height+1) node.right =
     * buildSubtree(points, medi+1, end, curDim+1, height+1)
     *
     *      iheight++;
     *      return node;
     *  else
     *      return nullptr;
     */
    KDNode* buildSubtree(vector<Point>& points, unsigned int start,
                         unsigned int end, unsigned int curDim, int height) {
        int medi = 0;
        numDim = points.begin()->numDim;

        if (start <= end) {
            // Sorts the elements between [points.begin() + start,
            // points.begin() + end + 1) according to it's dimension
            sort(points.begin() + start, points.begin() + end + 1,
                 CompareValueAt(curDim));
            // calculate the parent node of subtree
            medi = floor((start + end) / 2);
            // node = new KDNode(points[medi]);
            KDNode* node = new KDNode(points[medi]);
            isize++;
            node->right = buildSubtree(points, medi + 1, end,
                                       (curDim + 1) % numDim, height + 1);
            node->left = buildSubtree(points, start, medi - 1,
                                      (curDim + 1) % numDim, height + 1);
            iheight++;
            return node;
        } else {
            return nullptr;
        }
    }

    /** TODO */
    void findNNHelper(KDNode* node, Point& queryPoint, unsigned int curDim) {}

    /** Extra credit */
    void rangeSearchHelper(KDNode* node, vector<pair<double, double>>& curBB,
                           vector<pair<double, double>>& queryRegion,
                           unsigned int curDim) {}

    /** Helper method of destructor, recursively delete the tree */
    static void deleteAll(KDNode* n) {
        if (n) {
            deleteAll(n->left);
            deleteAll(n->right);
        }
    }

    // Add your own helper methods here
};
#endif  // KDT_HPP
