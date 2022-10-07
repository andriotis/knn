#include <pthread.h>
#include <stdlib.h>

#include "structures.h"
#include "utils.h"
extern int MAX_THREADS, MIN_WORK_PER_THREAD;
double **points;
double *distances;
int active_threads;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void make_vpt(VPTree *node, int start, int end) {
  node->idx = end;
  node->md = 0;
  node->inner = node->outer = NULL;

  if (start == end) return;

  // Finf number of available threads
  int available_threads = MAX_THREADS - active_threads;
  // Here we should choose seq or parallel depending on thread availability
  // Calculate distances sequentially
  if (available_threads > 0 && (end - start + 1) / 2 > MIN_WORK_PER_THREAD) {
    update_active_threads(+available_threads);
    calculate_distances_parallel(end - start, available_threads, node->idx);
    update_active_threads(-available_threads);
  } else
    calculate_distances_sequential(start, end, node->idx);

  // Find median distance of current node's set (exclude the vantage point)
  node->md = get_median(start, end);

  // Here I find the bounds of inner and outer sub-trees
  int start_inner = start;
  int end_inner = (start + end) / 2 - 1;
  int start_outer = end_inner + 1;
  int end_outer = end - 1;

  // Decide I we should build the inner vpt using a seperate thread
  if (available_threads &&
      (end - start + 1) / 2 >
          MIN_WORK_PER_THREAD) {  // Create args to pass to thread
    node->inner = malloc(sizeof(VPTree));
    pthread_t t_inner;
    TArgs args_inner;
    args_inner.node = node->inner;
    args_inner.start = start_inner;
    args_inner.end = end_inner;

    // First increase the number of active threads by one
    update_active_threads(+1);
    pthread_create(&t_inner, NULL, &make_vpt_parallel, (void *)&args_inner);
    pthread_join(t_inner, NULL);

    node->outer = malloc(sizeof(VPTree));
    make_vpt(node->outer, start_outer, end_outer);

    update_active_threads(-1);
  } else {
    node->outer = malloc(sizeof(VPTree));
    make_vpt(node->outer, start_outer, end_outer);
    if ((start + end) / 2 - 1 < start) return;
    node->inner = malloc(sizeof(VPTree));
    make_vpt(node->inner, start_inner, end_inner);
  }
}