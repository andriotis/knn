#ifndef PARALLEL_H
#define PARALLEL_H
#include "structures.h"

void make_vpt(VPTree *node, int start, int end);
void search_vpt(VPTree *node, double *query);
void run_parallel();

#endif