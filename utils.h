#ifndef UTILS_H
#define UTILS_H
#include "structures.h"

void initialize(double ***points, double **distances);
double euclidean_dist(double *a, double *b);
double get_median(Set X);
void calc_dist_seq(Set X);
void update_active_threads(int amount);
DistArgs *calc_dist_args(Set X, int t);
void *calc_dist_par(void *args);
void *routine(void *args);

#endif