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

void initialize(double ***points, double **query, double **distances)
{
  *points = (double **)malloc(n * sizeof(double *));
  *query = (double *)malloc(d * sizeof(double));
  *distances = (double *)malloc(n * sizeof(double));

  for (int i = 0; i < n; i++)
    (*points)[i] = (double *)malloc(d * sizeof(double));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < d; j++)
      (*points)[i][j] = (double)rand() / RAND_MAX;

  for (int i = 0; i < d; i++)
    (*query)[i] = (double)rand() / RAND_MAX;
}

double euclidean_dist(double *a, double *b)
{
  double dist = 0.0;
  for (int i = 0; i < d; i++)
    dist += pow(b[i] - a[i], 2.0);
  return sqrt(dist);
}

double get_median(int start, int end)
{
  return (quickselect(start, end - 1, (end - start - 1) / 2 + 1) +
          quickselect(start, end - 1, (end - start) / 2 + 1)) /
         2;
}

void calc_dist_seq(int start, int end)
{
  for (int i = start; i < end; i++)
    distances[i] = euclidean_dist(points[i], points[end]);
}