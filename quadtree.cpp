
/**
 *
 * quadtree 
 * quadtree.cpp
 * This file will be used for grading.
 *
 */

#include "quadtree.h"
#include <cassert>
#include <cmath>
using namespace std;

// Node constructor, given.
quadtree::Node::Node(pair<int, int> ul, int d, RGBAPixel a, double v)
    : upLeft(ul), dim(d), avg(a), var(v), NW(nullptr), NE(nullptr), SE(nullptr), SW(nullptr) {}

// quadtree destructor, given.
quadtree::~quadtree() {
    clear();
}
// quadtree copy constructor, given.
quadtree::quadtree(const quadtree& other) {
    copy(other);
}
// quadtree assignment operator, given.
quadtree& quadtree::operator=(const quadtree& rhs) {
    if (this != &rhs) {
        clear();
        copy(rhs);
    }
    return *this;
}

quadtree::quadtree(PNG& imIn) {
    /* Your code here! */
    stats s(imIn);

    // setting the edge
    edge = 1;
    while ((unsigned int) edge * 2 <= imIn.width()) {
        edge *= 2;
    }
    // edge = min(imIn.width(), imIn.height());

    int dim = log2(edge);

    // assert(imIn.width() == imIn.height() && "height and width must be same");
    // assert(pow(2, dim) == edge && "Image width must be a power of 2");

    this->root = buildTree(s, {0, 0}, dim);
}

quadtree::Node* quadtree::buildTree(stats& s, pair<int, int> ul, int dim) {
    // if (dim == 0) {
    //     return new Node(ul, dim, s.getAvg(ul, dim), s.getVar(ul, dim));
    // }
    if (dim < 0) {
        return nullptr;
    }

    int x = ul.first;
    int y = ul.second;

    Node* root = new Node(ul, dim, s.getAvg(ul, dim), s.getVar(ul, dim));
    int delta = pow(2, dim - 1);

    root->NW = buildTree(s, {x, y}, dim - 1);
    root->NE = buildTree(s, {x + delta, y}, dim - 1);
    root->SW = buildTree(s, {x, y + delta}, dim - 1);
    root->SE = buildTree(s, {x + delta, y + delta}, dim - 1);

    return root;
}

PNG quadtree::render() const {
    PNG ret(edge, edge);
    render_helper(root, ret);
    return ret;
}

void quadtree::render_helper(Node* root, PNG& im) const {
    if (root == NULL) return;

    int side = pow(2, root->dim);

    if ((root->NW == NULL) && (root->NE == NULL) && (root->SE == NULL) && (root->SW == NULL)) {
        for (int x = root->upLeft.first; x < root->upLeft.first + side; x++) {
            for (int y = root->upLeft.second; y < root->upLeft.second + side; y++) {
                *im.getPixel(x, y) = root->avg;
            }
        }
        return;
    }

    render_helper(root->NW, im);
    render_helper(root->NE, im);
    render_helper(root->SE, im);
    render_helper(root->SW, im);
}

int quadtree::idealPrune(const int leaves) const {
    int low = 0;
    int high = 100000;
    int result = high;

    while (low <= high) {
        int mid = (low + high) / 2;
        int currentLeaves = pruneSize(mid);

        if (currentLeaves <= leaves) {
            result = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return result;
}

int quadtree::pruneSize(const int tol) const {
    /* Your code here! */
    int prunes = 0;
    pruneSize_helper(root, tol, &prunes);
    return prunes;
}

void quadtree::pruneSize_helper(Node* node, const int tol, int* prunes) const{
    if (node == nullptr) { 
        return; 
    }
    if (prunable(node, tol)) {
        *prunes = *prunes + 1;
        return;      
    }
    pruneSize_helper(node->NE, tol, prunes);
    pruneSize_helper(node->NW, tol, prunes);
    pruneSize_helper(node->SE, tol, prunes);
    pruneSize_helper(node->SW, tol, prunes);
}


void quadtree::prune(const int tol) {
    pruneHelper(root, tol);
}

void quadtree::pruneHelper(Node* node, int tol) {
    if (node == nullptr) {
        return;
    } 

    if (prunable(node, tol)) {
        delete node->NW;
        node->NW = nullptr;
        delete node->NE;
        node->NE = nullptr;
        delete node->SW;
        node->SW = nullptr;
        delete node->SE;
        node->SE = nullptr;
        return;      
    }

    // Recursively prune the left and right subtrees
    pruneHelper(node->NE, tol);
    pruneHelper(node->NW, tol);
    pruneHelper(node->SE, tol);
    pruneHelper(node->SW, tol);
}

void quadtree::deleteSubtree(Node* node) {

    delete node->NW;
    node->NW = nullptr;
    delete node->NE;
    node->NE = nullptr;
    delete node->SW;
    node->SW = nullptr;
    delete node->SE;
    node->SE = nullptr;
}

void quadtree::clear() {
    clearHelper(root); 
    root = nullptr; 
}

void quadtree::clearHelper(Node* node) {
    if (node == nullptr) {
        return;
    }

    // Recursively delete all children
    clearHelper(node->NW);
    clearHelper(node->NE);
    clearHelper(node->SE);
    clearHelper(node->SW);

    // Delete the current node
    delete node;
}

void quadtree::copy(const quadtree& orig) {
    // clear();
    edge = orig.edge;
    root = copyHelper(orig.root);
}

quadtree::Node* quadtree::copyHelper(const Node* otherNode) {
    if (otherNode == nullptr) {
        return nullptr;
    } 

    // Create a new node by copying the data from otherNode
    Node* newNode = new Node(otherNode->upLeft, otherNode->dim, otherNode->avg, otherNode->var);

    // Recursively copy subtrees
    newNode->NW = copyHelper(otherNode->NW);
    newNode->NE = copyHelper(otherNode->NE);
    newNode->SE = copyHelper(otherNode->SE);
    newNode->SW = copyHelper(otherNode->SW);

    return newNode;
}
