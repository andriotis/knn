#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "quickselect.h"
#include "parallel.h"

extern int n, d, k;

extern double **points;
extern double *query;
extern double *distances;

extern int MAX_THREADS, active_threads;
extern pthread_mutex_t mutex;

// Given 2 points, calculate their euclidean distance
double euclidean_dist(double *a, double *b)
{
  double dist = 0.0;
  for (int i = 0; i < d; i++)
    dist += pow(b[i] - a[i], 2.0);
  return sqrt(dist);
}

// Using quickselect, find the median of the distances
double get_median(int start, int end)
{
  return (quickselect(start, end - 1, (end - start - 1) / 2 + 1) +
          quickselect(start, end - 1, (end - start) / 2 + 1)) /
         2;
}

// an update for the active threads
void update_active_threads(int amount)
{
  pthread_mutex_lock(&mutex);
  active_threads += amount;
  pthread_mutex_unlock(&mutex);
}

// the function of the threads responsible for the distances
void *chunk_distances(void *args)
{
  dist_arg *chunk = (dist_arg *)args;
  for (int i = chunk->start; i < chunk->end; i++)
    distances[i] = euclidean_dist(points[i], points[chunk->vp]);
}

// a wraper that gives each thread a chunk to work with
void calculate_distances_parallel(int n, int t, int vp)
{
  pthread_t threads[t];
  dist_arg chunk[t];
  for (int i = 0; i < t; i++)
  {
    chunk[i].start = 0;
    for (int j = 0; j < i; j++)
      chunk[i].start += (j < n % t) ? (n / t + 1) : (n / t);
    chunk[i].end = chunk[i].start + ((i < n % t) ? (n / t + 1) : (n / t));
    chunk[i].vp = vp;
    pthread_create(&threads[i], NULL, &chunk_distances, &chunk[i]);
    pthread_join(threads[i], NULL);
  }
}

// a basic calculation for distances
void calculate_distances_sequential(int start, int end, int vp)
{
  for (int i = start; i < end; i++)
    distances[i] = euclidean_dist(points[i], points[vp]);
}

// the calling function of a thread to make the inner child
void *make_vpt_parallel(void *args)
{
  TArgs *targs = (TArgs *)args;
  make_vpt(targs->node, targs->start, targs->end);
  update_active_threads(-1);
  pthread_exit(NULL);
  return (void *)0;
}