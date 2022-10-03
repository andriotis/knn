#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sequential.h"
#include <time.h>
#include "utils.h"
#include <pthread.h>

int counter = 0;
int n = 8, d = 2;
int MAX_THREADS = 4;

double **points;
double *distances;

int times_make_vp_tree_run()
{
    return counter;
}

int main()
{
    srand(42);

    initialize(&points, &distances);

    Set S = {0, n - 1};
    VPTree *root;

    clock_t begin = clock();
    seq_make_vp_tree(root, S);
    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Took %f..\n", time_spent);
    printf("leaves %d\n", times_make_vp_tree_run());
    return EXIT_SUCCESS;
}
