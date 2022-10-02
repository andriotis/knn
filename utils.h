#ifndef UTILS_H
#define UTILS_H
#include "structures.h"

void initialize(double ***points, double **distances);
double euclidean_dist(double *a, double *b);
double get_median(Set X);
void calc_dist_seq(Set X);

void print2DUtil(struct VPTree *root, int space);
void print2D(struct VPTree *root);
#endif