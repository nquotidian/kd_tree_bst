#ifndef KDT_HPP
#define KDT_HPP

#include <math.h>     // pow, abs
#include <algorithm>  // sort, max, min
#include <limits>     // numeric_limits<type>::max()
#include <vector>     // vector<typename>
#include "Point.hpp"

using namespace std;

const double SQ = 2;

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
        numDim = points.begin()->numDim;
        // Builds subtree using the points
        root = buildSubtree(points, 0, points.size() - 1, 0, -1);
        iheight = floor(log2(points.size()));
    }

    /** TODO
     *  Return nullptr if the KD tree is empty
     *  Find the nearest neighbor. Recursively
     *  From the root, look up for the queryPoint first, to the leaf node
     *  Traverse down, use recursion
     *  Update the thredhold,
     */
    Point* findNearestNeighbor(Point& queryPoint) {
        // Return nullptr if the tree is empty
        if (!root) return nullptr;
        findNNHelper(root, queryPoint, 0);
        return &nearestNeighbor;
    }

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
     *  points:  vector with all the data points to build the KD tree
     *  start: the inclusive start index of the points vector during building
     *         subtree
     *  end: the exclusive end index of the points vector during building
     *      subtree curDim: the current dimension during building subtree
     *  height: the current height during building subtree
     */
    KDNode* buildSubtree(vector<Point>& points, unsigned int start,
                         unsigned int end, unsigned int curDim, int height) {
        if (start <= end) {
            // Sorts the elements between [points.begin() + start,
            // points.begin() + end + 1) according to it's dimension
            sort(points.begin() + start, points.begin() + end + 1,
                 CompareValueAt(curDim));
            // calculate the parent node of subtree
            int medi = floor((start + end) / 2);
            // New node
            KDNode* node = new KDNode(points[medi]);
            isize++;
            // Check if medi-1 >= 0, in case the convert from int to unsigned
            // causes segfault
            if (medi - 1 >= 0) {
                node->left = buildSubtree(points, start, medi - 1,
                                          (curDim + 1) % numDim, height + 1);
            } else {
                node->left = nullptr;
            }
            node->right = buildSubtree(points, medi + 1, end,
                                       (curDim + 1) % numDim, height + 1);
            return node;
        } else {
            return nullptr;
        }
    }

    /** Find the nearest node by updating the threshold */
    void findNNHelper(KDNode* node, Point& queryPoint, unsigned int curDim) {
        double dist = 0;
        // Leaf node
        if (node->left == nullptr && node->right == nullptr) {
            // update distance to query point
            dist = sq_ecli_dis(node->point.features, queryPoint.features);
            if (dist < threshold) {
                threshold = dist;
                node->point.distToQuery = threshold;
                nearestNeighbor = node->point;
            }
        } else if (node->left &&
                   queryPoint.features[curDim] < node->point.features[curDim]) {
            // Go left
            findNNHelper(node->left, queryPoint, (curDim + 1) % numDim);
            // Calculate distance for current dimension
            double dist_dim_r = pow(
                (node->point.features[curDim] - queryPoint.features[curDim]),
                SQ);
            // If searching the right subtree is necessary
            if (dist_dim_r < threshold) {
                // Update threshold
                dist = sq_ecli_dis(node->point.features, queryPoint.features);
                if (dist < threshold) {
                    threshold = dist;
                    nearestNeighbor = node->point;
                }
                findNNHelper(node->right, queryPoint, (curDim + 1) % numDim);
            }
        } else if (node->right && queryPoint.features[curDim] >=
                                      node->point.features[curDim]) {
            // Go right
            findNNHelper(node->right, queryPoint, (curDim + 1) % numDim);
            // Calculate distance for current dimension
            double dist_dim_l = pow(
                (node->point.features[curDim] - queryPoint.features[curDim]),
                SQ);
            // if serarching the left subtree is necessary
            if (dist_dim_l < threshold) {
                // Update threshold if necessary
                dist = sq_ecli_dis(node->point.features, queryPoint.features);
                if (dist < threshold) {
                    threshold = dist;
                    node->point.distToQuery = threshold;
                    nearestNeighbor = node->point;
                }
                findNNHelper(node->left, queryPoint, (curDim + 1) % numDim);
            }
        }
    }

    /** Extra credit */
    void rangeSearchHelper(KDNode* node, vector<pair<double, double>>& curBB,
                           vector<pair<double, double>>& queryRegion,
                           unsigned int curDim) {
        return;
    }

    /** Helper method of destructor, recursively delete the tree */
    static void deleteAll(KDNode* n) {
        if (n) {
            deleteAll(n->left);
            deleteAll(n->right);
        }
    }

    double sq_ecli_dis(vector<double> v1, vector<double> v2) {
        double dist = 0;
        for (unsigned int i = 0; i < numDim; i++)
            dist += pow((v1[i] - v2[i]), SQ);
        return dist;
    }

    // Add your own helper methods here
};
#endif  // KDT_HPP