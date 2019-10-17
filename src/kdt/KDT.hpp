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
        numDim = queryPoint.numDim;
        findNNHelper(root, queryPoint, 0);
        threshold = numeric_limits<double>::max();
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

    /** In order traverse the KD tree */
    vector<Point> inorder() {
        vector<Point> vec(0);
        inorder_helper(root, vec);
        return vec;
    }

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
        // Leaf node
        if (node->left == nullptr && node->right == nullptr) {
            // Update the threshold if it's smaller
            update_threshold(node, queryPoint);
        } else if (node->left != nullptr &&
                   queryPoint.features[curDim] < node->point.features[curDim]) {
            // Go left
            findNNHelper(node->left, queryPoint, (curDim + 1) % numDim);
            // Distance for current dimension
            double dist_dim_r = curr_dim_dis(node, queryPoint, curDim);
            // Go right
            if (node->right != nullptr && dist_dim_r <= threshold) {
                // Go to the right subtree
                findNNHelper(node->right, queryPoint, (curDim + 1) % numDim);
            }
            // If the node has a smaller threshold, update
            update_threshold(node, queryPoint);
        } else if (node->right != nullptr) {
            // Go right
            findNNHelper(node->right, queryPoint, (curDim + 1) % numDim);
            // Distance for current dimension
            double dist_dim_l = curr_dim_dis(node, queryPoint, curDim);
            // Go left
            if (node->left != nullptr && dist_dim_l <= threshold) {
                // Go to the left subtree
                findNNHelper(node->left, queryPoint, (curDim + 1) % numDim);
            }
            //  If the node has a better smaller threshold, update
            update_threshold(node, queryPoint);
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
            delete n;
        }
    }

    // Add your own helper methods here
    /** Calculate the square euclidean distance of two points */
    double curr_dim_dis(KDNode* n, Point& p, int dim) {
        return pow(fabs(n->point.features[dim] - p.features[dim]), SQ);
    }

    /** Update the threshold */
    void update_threshold(KDNode* node, Point& queryPoint) {
        double dist = 0;
        vector<double> v1 = node->point.features;
        vector<double> v2 = queryPoint.features;
        for (unsigned int i = 0; i < numDim; i++)
            dist += pow(fabs(v1[i] - v2[i]), SQ);
        if (dist < threshold) {
            threshold = dist;
            node->point.distToQuery = dist;
            nearestNeighbor = node->point;
        }
    }

    /** Helper function for in order traverse*/
    static void inorder_helper(KDNode* n, vector<Point>& vec) {
        if (n == nullptr) {
            return;
        }
        inorder_helper(n->left, vec);
        vec.push_back(n->point);
        inorder_helper(n->right, vec);
    }
};
#endif  // KDT_HPP