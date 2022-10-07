#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/sysinfo.h>

#include "structures.h"
#include "sequential.h"
#include "utils.h"
#include "queue.h"

int n = 10, d = 2;
int k = 3;
double tau = RAND_MAX;

double **points;
double *distances;
double *query;
struct LinkedList *nearest;

int main()
{
    srand(42);

    initialize(&points, &query, &distances);

    VPTree *root = (VPTree *)malloc(sizeof(VPTree));
    make(root, 0, n - 1);

    nearest = newNode(-1, RAND_MAX);
    search(root, query, k);

    return EXIT_SUCCESS;
}
