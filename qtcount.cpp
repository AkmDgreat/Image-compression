#include "qtcount.h"

// prunable node: can I remove both the left and the right subtree of this node? 
// how to check it its prunable?
// find all the leaves of the node
// the color-dist between the node, and all of the leaves should be within tolerance
// what if one of them leaves is not within the tolerance? well then, the node is not prunable
// (avg.r - leaf.r)^2 + (avg.g - leaf.g)^2 + (avg.b - leaf.b)^2
bool qtcount::prunable(Node* node, const int tol) const {
    /* Your code here */
    unsigned int avg_r = node->avg.r;
    unsigned int avg_g = node->avg.g;
    unsigned int avg_b = node->avg.b;

    return prunable_helper(node, tol, avg_r, avg_g, avg_b);
}

bool qtcount::prunable_helper(Node* node, const int tol, unsigned int avg_r, unsigned int avg_g, unsigned int avg_b) const {
    /* Your code here */
    bool isLeaf = 
        (node->NW == nullptr) && 
        (node->NE == nullptr) && 
        (node->SW == nullptr) &&  
        (node->SE == nullptr);

    if (isLeaf) {
        int colDist = 
            pow((node->avg.r - avg_r), 2) + 
            pow((node->avg.g - avg_g), 2) + 
            pow((node->avg.b - avg_b), 2);

        return colDist <= tol;
    }


    bool isPrunable = prunable_helper(node->NE, tol, avg_r, avg_g, avg_b) && 
        prunable_helper(node->NW, tol, avg_r, avg_g, avg_b) &&
        prunable_helper(node->SE, tol, avg_r, avg_g, avg_b) &&
        prunable_helper(node->SW, tol, avg_r, avg_g, avg_b);

    return isPrunable;
}
