#ifndef UTILS_H
#define UTILS_H
#include "structures.h"

double euclidean_dist(double *a, double *b);
double get_median(int start, int end);
void update_active_threads(int amount);
void *chunk_distances(void *args);
void calculate_distances_parallel(int n, int t, int vp);
void calculate_distances_sequential(int start, int end, int vp);
void *make_vpt_parallel(void *args);

#endif