#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <time.h>
#include <unistd.h>

#include "parallel.h"
#include "queue.h"
#include "sequential.h"
#include "structures.h"
#include "utils.h"

int n = 100000000, d = 2;
int k = 3;
double tau = RAND_MAX;
int MAX_THREADS, MIN_WORK_PER_THREAD = 1000;

double **points;
double *distances;
double *query;
struct LinkedList *nearest;

int main() {
  srand(42);
  MAX_THREADS = 4;
  initialize(&points, &query, &distances);

  VPTree *root = (VPTree *)malloc(sizeof(VPTree));
  make_vpt(root, 0, n - 1);

  nearest = newNode(-1, RAND_MAX);
  search(root, query, k);
  // for (int i = 0; i < n - 1; i++) printf("%f\n", distances[i]);
  while (size(&nearest)) {
    printf("%f\n", peek(&nearest)->distance);
    pop(&nearest);
  }

  return EXIT_SUCCESS;
}
