#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/sysinfo.h>

#include "sequential.h"
#include "utils.h"

int n = 8, d = 2;
double quickselect_time = 0;
int MAX_THREADS;

double **points;
double *distances;

double tau = 10;
int best;

int main()
{
    srand(1);
    double *query = (double *)malloc(d * sizeof(double));
    for (int i = 0; i < d; i++)
        query[i] = (double)rand() / RAND_MAX;

    initialize(&points, &distances);

    int test_best;
    double test_tau = 10;
    double current_dist;
    for (int i = 0; i < n; i++)
    {
        current_dist = euclidean_dist(query, points[i]);
        printf("%f ", current_dist);
        if (current_dist < test_tau)
        {
            test_tau = current_dist;
            test_best = i;
        }
    }
    printf("\nbrute said best is %d\n", test_best);

    Set S = {0, n - 1};
    VPTree *root = (VPTree *)malloc(sizeof(VPTree));

    clock_t begin = clock();
    make_vp_tree(root, S);
    search(root, query);
    clock_t end = clock();
    printf("seq said best is %d\n", best);

    double total_time = (double)(end - begin) / CLOCKS_PER_SEC;

    // printf("Took %f of which quickselect took %.2f %%\n", total_time, (quickselect_time / total_time) * 100);

    return EXIT_SUCCESS;
}
