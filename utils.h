#ifndef UTILS_H
#define UTILS_H
#include "structures.h"

void initialize(double ***points, double **query, double **distances);
double euclidean_dist(double *a, double *b);
double get_median(int start, int end);
// ~~~~~~~~~~~~~~~~~~~ NIKOS ~~~~~~~~~~~~~~~~~~~
typedef struct {
  int start;
  int end;
  int vp;
} dist_arg;

void update_active_threads(int amount);
void *chunk_distances(void *args);
void calculate_distances_parallel(int n, int t, int vp);
void calculate_distances_sequential(int start, int end, int vp);
// ~~~~~~~~~~~~~~~~~~~ NIKOS ~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~ STYL ~~~~~~~~~~~~~~~~~~~~~~~~~
typedef struct {
  VPTree *node;
  int start;
  int end;
} TArgs;

void *make_vpt_parallel(void *args);
// ~~~~~~~~~~~~~~~~~~~~ STYL ~~~~~~~~~~~~~~~~~~~~~~~~~
#endif