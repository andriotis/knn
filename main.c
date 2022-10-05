#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/sysinfo.h>

#include "sequential.h"
#include "utils.h"

int n = 1000, d = 2;

double tau = 1;
int vp_best;

double **points;
double *distances;
double *query;

int main()
{
    srand(53);

    initialize(&points, &distances);

    query = (double *)malloc(d * sizeof(double));
    for (int i = 0; i < d; i++)
        query[i] = (double)rand() / RAND_MAX;

    double min = RAND_MAX;
    int brute_best;
    for (int i = 0; i < n; i++)
    {
        if (euclidean_dist(query, points[i]) < min)
        {
            min = euclidean_dist(query, points[i]);
            brute_best = i;
        }
    }

    printf("brute nearest :\n");
    printf("-------------\n");
    printf("|%.3f %.3f|\n", points[brute_best][0], points[brute_best][1]);
    printf("-------------\n");

    Set S = {0, n - 1};

    VPTree *root = (VPTree *)malloc(sizeof(VPTree));
    make_vp_tree(root, S);
    search(root);
    printf("search nearest:\n");
    printf("-------------\n");
    printf("|%.3f %.3f|", points[vp_best][0], points[vp_best][1]);
    printf("\n-------------\n");

    return EXIT_SUCCESS;
}
