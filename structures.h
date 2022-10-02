#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct
{
    int start;
    int end;
} Set;

typedef struct VPTree
{
    // Vantage point
    double *vp;
    // Median distance of vp from all other points
    double md;
    // Index of vp in the original set
    int idx;
    // Inner VP Tree (left child node)
    struct VPTree *inner;
    // Outer VP Tree (right child node)
    struct VPTree *outer;
} VPTree;

typedef struct
{
    int start;
    int num_points;
    int vp_idx;
} DistArgs;

typedef struct
{
    Set X;
    VPTree *node;
} TreeArgs;
#endif