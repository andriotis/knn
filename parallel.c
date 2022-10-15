#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/sysinfo.h>

#include <pthread.h>
#include "parallel.h"

#include "structures.h"
#include "utils.h"
#include "queue.h"

// EXPERIMENT VARIABLES SHOULD BE GLOBAL
extern int n, d, k;
extern double tau;
extern double **points;
extern double *query;
extern double *distances;

// RUNTIME VARIABLES SHOULD BE LOCAL
int MAX_THREADS, MIN_WORK_PER_THREAD = 10000;
int active_threads;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct LinkedList *nearest;

// CONSTRUCT VP-TREE AND SEARCH IN PARALLEL
void make_vpt(VPTree *node, int start, int end)
{
  node->idx = end;
  node->md = 0;
  node->inner = node->outer = NULL;

  if (start == end)
    return;

  int available_threads = MAX_THREADS - active_threads;

  // add thresholds in order to call the sequential code
  if (available_threads > 0 && (end - start + 1) / 2 > MIN_WORK_PER_THREAD)
  {
    update_active_threads(+available_threads);
    calculate_distances_parallel(end - start, available_threads, node->idx);
    update_active_threads(-available_threads);
  }
  else
    calculate_distances_sequential(start, end, node->idx);

  node->md = get_median(start, end);

  int start_inner = start;
  int end_inner = (start + end) / 2 - 1;
  int start_outer = end_inner + 1;
  int end_outer = end - 1;

  if (available_threads && (end - start + 1) / 2 > MIN_WORK_PER_THREAD)
  {
    node->inner = malloc(sizeof(VPTree));
    pthread_t t_inner;
    TArgs args_inner;
    args_inner.node = node->inner;
    args_inner.start = start_inner;
    args_inner.end = end_inner;

    update_active_threads(+1);
    pthread_create(&t_inner, NULL, &make_vpt_parallel, (void *)&args_inner);
    pthread_join(t_inner, NULL);

    node->outer = malloc(sizeof(VPTree));
    make_vpt(node->outer, start_outer, end_outer);

    update_active_threads(-1);
  }
  else
  {
    node->outer = malloc(sizeof(VPTree));
    make_vpt(node->outer, start_outer, end_outer);
    if ((start + end) / 2 - 1 < start)
      return;
    node->inner = malloc(sizeof(VPTree));
    make_vpt(node->inner, start_inner, end_inner);
  }
}
void search_vpt(VPTree *node, double *query)
{
  if (node == NULL)
    return;

  double x = euclidean_dist(query, points[node->idx]);

  if (x < tau)
  {
    push(&nearest, node->idx, x);
    if (size(&nearest) > k)
      pop(&nearest);
    if (size(&nearest) == k)
      tau = peek(&nearest)->distance;
  }

  if (x < node->md)
  {
    if (x - tau <= node->md)
      search_vpt(node->inner, query);
    if (x + tau >= node->md)
      search_vpt(node->outer, query);
  }
  else
  {
    if (x + tau >= node->md)
      search_vpt(node->outer, query);
    if (x - tau <= node->md)
      search_vpt(node->inner, query);
  }
}
void run_parallel()
{
  VPTree *root = (VPTree *)malloc(sizeof(VPTree));
  nearest = newNode(-1, RAND_MAX);
  tau = RAND_MAX;
  MAX_THREADS = get_nprocs();
  make_vpt(root, 0, n - 1);
  clock_t start = clock();
  search_vpt(root, query);
  clock_t end = clock();
  printf("Parallel took : %f\n", ((double)(end - start)) / CLOCKS_PER_SEC);
}