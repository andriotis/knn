#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "utils.h"
#include "quickselect.h"
#include "structures.h"

int n = 10;
int d = 2;

double **points;
double *distances;

int active_threads = 1;
int MAX_THREADS;
int MIN_WORK_PER_THREAD;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Function to update the number of active threads
void update_active_threads(int amount)
{
    pthread_mutex_lock(&mutex);
    active_threads += amount;
    pthread_mutex_unlock(&mutex);
}

typedef struct TArgs
{
    VPTree *node;
    int start;
    int end;
} TArgs;

void make_vpt(VPTree *node, int start, int end);
/*
  This function parses the TreeArgs passed by a thread
  and calls make_vpt()
*/
void *make_vpt_parallel(void *args)
{
    TArgs *targs = (TArgs *)args;
    // Call make_vpt with the appropriate arguments
    make_vpt(targs->node, targs->start, targs->end);
    // Decrease number of threads by one
    update_active_threads(-1);
    pthread_exit(NULL);
    return (void *)0;
}

void make_vpt(VPTree *node, int start, int end)
{
    node = (VPTree *)malloc(sizeof(VPTree));
    node->idx = end;
    node->md = 0;
    node->inner = node->outer = NULL;

    if (start == end)
        return;

    // Finf number of available threads
    int available_threads = MAX_THREADS - active_threads;
    // Here we should choose seq or parallel depending on thread availability
    // Calculate distances sequentially
    for (int i = start; i < end; i++)
        distances[i] = euclidean_dist(points[i], points[end]);

    // Find median distance of current node's set (exclude the vantage point)
    node->md = get_median(start, end - 1);

    // Here I find the bounds of inner and outer sub-trees
    int start_inner = start;
    int end_inner = (start + end) / 2 - 1;
    int start_outer = end_inner + 1;
    int end_outer = end - 1;

    // Decide I we should build the inner vpt using a seperate thread
    if (available_threads && (end - start + 1) / 2 > MIN_WORK_PER_THREAD)
    { // Create args to pass to thread
        pthread_t t_inner;
        TArgs args_inner;
        args_inner.node = node->inner;
        args_inner.start = start_inner;
        args_inner.end = end_inner;

        // First increase the number of active threads by one
        update_active_threads(+1);

        pthread_create(&t_inner, NULL, &make_vpt_parallel, (void *)&args_inner);
        make_vpt(node->outer, start_outer, end_outer);

        pthread_join(t_inner, NULL);
        update_active_threads(-1);
    }
    else
    {
        make_vpt(node->inner, start_inner, end_inner);
        make_vpt(node->outer, start_outer, end_outer);
    }
}

int main()
{
    srand(42);

    // Allocate memory for points
    points = (double **)malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++)
    {
        points[i] = (double *)malloc(d * sizeof(double));
    }

    // Generate random points
    for (int i = 0; i < n; i++)
        for (int j = 0; j < d; j++)
            points[i][j] = (double)rand() / RAND_MAX;

    // Now allocate space for distances
    distances = (double *)malloc(n * sizeof(double));

    // MAX_THREADS = sysconf(_SC_NPROCESSORS_ONLN);
    MAX_THREADS = 4;
    MIN_WORK_PER_THREAD = 2;

    // Create the root of the VPTree
    VPTree *root = (VPTree *)malloc(sizeof(VPTree));
    printf("We are cool here 3\n");
    make_vpt(root, 0, n - 1);

    // for (int i = 0; i < n - 1; i++)
    //     printf("%f\n", distances[i]);
    // free(points);
    // free(distances);

    return 0;
}