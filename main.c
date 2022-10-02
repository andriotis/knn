#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "parallel.h"
#include <time.h>
#include "utils.h"
#include <pthread.h>

int n = 8, d = 2, t = 4;

double **points;
double *distances;

int main()
{
    srand(42);

    initialize(&points, &distances);

    Set S = {0, n - 1};

    VPTree *root;
    make_vp_tree(root, S);

    return EXIT_SUCCESS;
}
