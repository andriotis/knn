#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/sysinfo.h>

#include "sequential.h"
#include "utils.h"
#include "queue.h"

int n = 10, d = 2;
int k = 3, curr_k = 1;
double tau = RAND_MAX, k_tau = RAND_MAX;
int vp_best;

double **points;
double *distances;
double *query;
struct LinkedList *nearest;

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

    Set S = {0, n - 1};
    VPTree *root = (VPTree *)malloc(sizeof(VPTree));

    printf("brute nearest:\n");
    printf("-------------------\n");
    printf("|%.3f %.3f %.3f|\n",
           points[brute_best][0],
           points[brute_best][1],
           euclidean_dist(query, points[brute_best]));
    printf("-------------------\n");

    for (int i = 0; i < n; i++)
        printf("%.3f %.3f : %.3f\n", points[i][0], points[i][1], euclidean_dist(query, points[i]));

    make_vp_tree(root, S);

    // search(root);
    // printf("search nearest:\n");
    // printf("---------------------\n");
    // printf("|%.3f %.3f : %.3f|\n",
    //        points[vp_best][0],
    //        points[vp_best][1],
    //        euclidean_dist(query, points[vp_best]));
    // printf("---------------------\n");

    nearest = newNode(-1, RAND_MAX);
    search(root, k);
    printf("search %d-nearest:\n", queue_size(&nearest));
    printf("--------------------\n");
    for (int i = 0; i < curr_k; i++)
    {
        printf("|%.3f %.3f : %.3f|\n",
               points[peek(&nearest)->id][0],
               points[peek(&nearest)->id][1],
               peek(&nearest)->distance);
        pop(&nearest);
    }
    printf("--------------------\n");

    return EXIT_SUCCESS;
}
