#ifndef PARALLEL_H
#define PARALLEL_H
#include "structures.h"

void *calc_distances_parallel(void *params);
VPTree *make_vp_tree(Set *X);

#endif