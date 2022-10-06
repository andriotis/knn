#ifndef VPS_TREE_H
#define VPS_TREE_H
#include "structures.h"
#include "vps_structures.h"

VPTree *make_vps_tree(double *S);
VPTree *recurse_vps_tree(VPSListNode *list);

#endif