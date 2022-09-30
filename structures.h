#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct
{
    int *ids;
    int size;
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
    int end;
    Set *X;
    double *distances;
    double *distances_copy;
} DistThreadArgs;

#endif