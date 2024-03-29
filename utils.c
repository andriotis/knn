#include "utils.h"

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "parallel.h"
#include "quickselect.h"
#include "structures.h"

extern int n, d;
extern int MAX_THREADS, active_threads;
extern pthread_mutex_t mutex;
extern double **points;
extern double *distances;

void initialize(double ***points, double **query, double **distances) {
  *points = (double **)malloc(n * sizeof(double *));
  *query = (double *)malloc(d * sizeof(double));
  *distances = (double *)malloc(n * sizeof(double));

  for (int i = 0; i < n; i++)
    (*points)[i] = (double *)malloc(d * sizeof(double));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < d; j++) (*points)[i][j] = (double)rand() / RAND_MAX;

  for (int i = 0; i < d; i++) (*query)[i] = (double)rand() / RAND_MAX;
}

double euclidean_dist(double *a, double *b) {
  double dist = 0.0;
  for (int i = 0; i < d; i++) dist += pow(b[i] - a[i], 2.0);
  return sqrt(dist);
}

double get_median(int start, int end) {
  return (quickselect(start, end - 1, (end - start - 1) / 2 + 1) +
          quickselect(start, end - 1, (end - start) / 2 + 1)) /
         2;
}

void update_active_threads(int amount) {
  pthread_mutex_lock(&mutex);
  active_threads += amount;
  pthread_mutex_unlock(&mutex);
}

void *chunk_distances(void *args) {
  dist_arg *chunk = (dist_arg *)args;
  for (int i = chunk->start; i < chunk->end; i++)
    distances[i] = euclidean_dist(points[i], points[chunk->vp]);
}

void calculate_distances_parallel(int n, int t, int vp) {
  pthread_t threads[t];
  dist_arg chunk[t];
  for (int i = 0; i < t; i++) {
    chunk[i].start = 0;
    for (int j = 0; j < i; j++)
      chunk[i].start += (j < n % t) ? (n / t + 1) : (n / t);
    chunk[i].end = chunk[i].start + ((i < n % t) ? (n / t + 1) : (n / t));
    chunk[i].vp = vp;
    pthread_create(&threads[i], NULL, &chunk_distances, &chunk[i]);
    pthread_join(threads[i], NULL);
  }
}

void calculate_distances_sequential(int start, int end, int vp) {
  for (int i = start; i < end; i++)
    distances[i] = euclidean_dist(points[i], points[vp]);
}

void *make_vpt_parallel(void *args) {
  TArgs *targs = (TArgs *)args;
  // Call make_vpt with the appropriate arguments
  make_vpt(targs->node, targs->start, targs->end);
  // Decrease number of threads by one
  update_active_threads(-1);
  pthread_exit(NULL);
  return (void *)0;
}