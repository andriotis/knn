#ifndef UTILS_H
#define UTILS_H
#include "structures.h"

void initialize(double ***points, double **query, double **distances);
double euclidean_dist(double *a, double *b);
double get_median(int start, int end);
void calc_dist_seq(int start, int end);
void update_active_threads(int amount);
DistArgs *calc_dist_args(Set X, int t);
void *calc_dist_par(void *args);
void *routine(void *args);
void print_point(double *point);
void print2DUtil(struct VPTree *root, int space, int count);
void print2D(VPTree *root);
#endif