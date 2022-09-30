#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include "utils.h"
#include "structures.h"

extern int n;
extern int d;

extern double **points;

extern int t;

// Read below to understand
// https://stackoverflow.com/questions/36688900/divide-an-uneven-number-between-threads

DistThreadArgs *getDistThreadArg(int num_threads, Set *X, double *distances, double *distances_copy)
{
    DistThreadArgs *params = (DistThreadArgs *)malloc(num_threads * sizeof(DistThreadArgs));
    // to num_threads einai to extern int t ektos kai an thes na allazei kathe fora
    int *num_points_per_thread = (int *)calloc(num_threads, sizeof(int));

    // Set params params for every thread
    for (int i = 0; i < t; i++)
    {
        // Point to set and distances arrays
        params[i].X = X;
        params[i].distances = distances;
        params[i].distances_copy = distances_copy;

        // Calculate the number of points each thread should handle (when computing distances)
        num_points_per_thread[i] = (params[i].X->size - 1) / num_threads;
        // Assign remaining points to threads (one point to each thread until no points remain)
        if (i < (params[i].X->size - 1) % num_threads)
            num_points_per_thread[i] += 1;

        // Calc start index for every thread)
        params[i].start = 0;
        for (int j = 0; j < i; j++)
            params[i].start += num_points_per_thread[j];

        // Calculate end index of each thread
        params[i].end = params[i].start + num_points_per_thread[i];
    }

    return params;
}

void *calc_distances_parallel(void *params)
{
    DistThreadArgs *args = (DistThreadArgs *)params;
    for (int i = args->start; i < args->end; i++)
    {
        double dist = euclidean_dist(points[args->X->ids[i]],
                                     points[args->X->ids[args->X->size - 1]]);
        args->distances[i] = dist;
        args->distances_copy[i] = dist;
    }
}

VPTree *make_vp_tree(Set *X)
{
    // Stop exeution where no points are left in the set
    if (X->size == 0)
        return NULL;

    // Initialize tree node and set the vantage point as the last point in the set
    VPTree *node;
    node = (VPTree *)malloc(sizeof(VPTree));
    node->idx = X->ids[X->size - 1];

    // Allocate space to store distances and a copy of them
    double *distances = (double *)malloc((X->size - 1) * sizeof(double));
    double *distances_copy = (double *)malloc((X->size - 1) * sizeof(double));

    //  Allocate threads responsible for calculating distances
    pthread_t *th = (pthread_t *)malloc(t * sizeof(pthread_t));

    // Calculate parms for the distance calculation routine called by every thread
    DistThreadArgs *params = getDistThreadArg(t, X, distances, distances_copy);

    // Every thread starts calculating distances for its assigned points
    for (int i = 0; i < t; i++)
        pthread_create(&th[i], NULL, &calc_distances_parallel, (void *)&params[i]);

    for (int i = 0; i < t; i++)
        pthread_join(th[i], NULL);

    // Find median distance and assign it as a node attribute
    node->md = get_median(distances_copy, X->size - 1);

    // Iinitalize data for Inner and Outer subsets
    Set *L = (Set *)malloc(sizeof(Set));
    L->ids = (int *)malloc((X->size - 1) * sizeof(int));
    L->size = 0;
    Set *R = (Set *)malloc(sizeof(Set));
    R->ids = (int *)malloc((X->size - 1) * sizeof(int));
    R->size = 0;

    //  Assign points to inner and outer sets based on median distance
    for (int i = 0; i < X->size - 1; i++)
    {
        if (distances[i] < node->md)
        {
            L->ids[L->size] = X->ids[i];
            L->size++;
        }
        else
        {
            R->ids[R->size] = X->ids[i];
            R->size++;
        }
    }

    // Reallocate space for Inner and Outer set (ids) to hold only the memory they need
    L->ids = (int *)realloc(L->ids, L->size * sizeof(int));
    R->ids = (int *)realloc(R->ids, R->size * sizeof(int));

    // Construct vp_tree for Inner and Outer sets
    node->inner = make_vp_tree(L);
    node->outer = make_vp_tree(R);

    return node;
}