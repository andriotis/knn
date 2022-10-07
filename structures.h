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
    double md;
    Set S;
    Set L;
    Set R;
    struct VPTree *inner;
    struct VPTree *outer;
} VPTree;

// typedef struct VPTNode
// {
//     int id;
//     int start;
//     int end;
//     int size;
//     VPT *inner;
//     VPT *outer;
// } VPT;

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