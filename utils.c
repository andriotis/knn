#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "utils.h"
#include "parallel.h"
#include "quickselect.h"
#include "structures.h"

extern int n, d;
extern int MAX_THREADS, active_threads;
extern pthread_mutex_t mutex;
extern double **points;
extern double *distances;

void initialize(double ***points, double **distances)
{
  *points = (double **)malloc(n * sizeof(double *));
  *distances = (double *)malloc(n * sizeof(double));

  for (int i = 0; i < n; i++)
    (*points)[i] = (double *)malloc(d * sizeof(double));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < d; j++)
      (*points)[i][j] = (double)rand() / RAND_MAX;
}

double euclidean_dist(double *a, double *b)
{
  double dist = 0.0;
  for (int i = 0; i < d; i++)
    dist += pow(b[i] - a[i], 2.0);
  return sqrt(dist);
}

double get_median(Set X)
{
  return (quickselect(X.start, X.end - 1, (X.end - X.start - 1) / 2 + 1) +
          quickselect(X.start, X.end - 1, (X.end - X.start) / 2 + 1)) /
         2;
}

void calc_dist_seq(Set X)
{
  for (int i = X.start; i < X.end; i++)
    distances[i] = euclidean_dist(points[i], points[X.end]);
}

// void update_active_threads(int amount)
// {
//   pthread_mutex_lock(&mutex);
//   active_threads += amount;
//   pthread_mutex_unlock(&mutex);
// }

// DistArgs *calc_dist_args(Set X, int t)
// {
//   DistArgs *args = (DistArgs *)malloc(t * sizeof(DistArgs));
//   for (int i = 0; i < t; i++)
//   {
//     args[i].num_points = (X.end - X.start) / t;
//     if (i < (X.end - X.start) % t)
//       args[i].num_points++;

//     args[i].start = 0;
//     for (int j = 0; j < i; j++)
//       args[i].start += args[j].num_points;
//   }
//   return args;
// }

// void *calc_dist_par(void *args)
// {
//   DistArgs *d_args = (DistArgs *)args;
//   for (int i = d_args->start; i < d_args->start + d_args->num_points; i++)
//     distances[i] = euclidean_dist(points[i], points[d_args->vp_idx]);
// }

// void *routine(void *args)
// {
//   TreeArgs *t_args = (TreeArgs *)args;
//   par_make_vp_tree(t_args->node, t_args->X);
//   update_active_threads(-1);
//   pthread_exit(NULL);
//   return;
// }