#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct VPTree
{
  int idx;
  double md;
  struct VPTree *inner;
  struct VPTree *outer;
} VPTree;

typedef struct
{
  int start;
  int end;
  int vp;
} dist_arg;

typedef struct
{
  VPTree *node;
  int start;
  int end;
} TArgs;

#endif