#ifndef PARALLEL_H
#define PARALLEL_H
#include "structures.h"

void *calc_distances_parallel(void *params);
DistArgs *calc_dist_args(Set X, int t);
void *calc_dist_par(void *args);
void *routine(void *args);
void par_make_vp_tree(VPTree *node, Set X);

#endif