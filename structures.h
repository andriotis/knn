#ifndef STRUCTURES_H
#define STRUCTURES_H

// typedef struct
// {
//     int start;
//     int end;
// } Set;

typedef struct VPTree {
  int idx;
  double md;
  struct VPTree *inner;
  struct VPTree *outer;
} VPTree;

// typedef struct
// {
//     int start;
//     int num_points;
//     int vp_idx;
// } DistArgs;

// typedef struct
// {
//     Set X;
//     VPTree *node;
// } TreeArgs;

#endif