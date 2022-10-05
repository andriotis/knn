#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct
{
    int start;
    int end;
    double low;
    double high;
} Set;

typedef struct VPTree
{
    int idx;
    Set S;
    Set L;
    Set R;
    struct VPTree *inner;
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