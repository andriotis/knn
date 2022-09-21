#include "vp_tree.h"
#include "select.h"

typedef struct VPTree
{
  double *vp;
  double md;
  int idx;
  struct VPTree *inner;
  struct VPTree *outer;
} VPTree;

VPTree get_vp_tree(double *Set, int size)
{
}