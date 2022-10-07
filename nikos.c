#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "structures.h"
#include "utils.h"

int n = 50, d = 2, t = 3;
int MAX_THREADS = 4, MIN_WORK_PER_THREAD = 10;
int active_threads = 1;
double **points;
double *distances;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void update_active_threads(int amount)
{
    pthread_mutex_lock(&mutex);
    active_threads += amount;
    pthread_mutex_unlock(&mutex);
}

typedef struct
{
    int start;
    int end;
    int vp;
} dist_arg;

void *chunk_distances(void *args)
{
    dist_arg *chunk = (dist_arg *)args;
    for (int i = chunk->start; i < chunk->end; i++)
        distances[i] = euclidean_dist(points[i], points[chunk->vp]);
}

void calculate_distances_parallel(int n, int t, int vp)
{
    pthread_t threads[t];
    dist_arg chunk[t];
    for (int i = 0; i < t; i++)
    {
        chunk[i].start = 0;
        for (int j = 0; j < i; j++)
            chunk[i].start += (j < n % t) ? (n / t + 1) : (n / t);
        chunk[i].end = chunk[i].start + ((i < n % t) ? (n / t + 1) : (n / t));
        chunk[i].vp = vp;
        pthread_create(&threads[i], NULL, &chunk_distances, &chunk[i]);
        pthread_join(threads[i], NULL);
    }
}

void calculate_distances_sequential(int start, int end, int vp)
{
    for (int i = start; i < end; i++)
        distances[i] = euclidean_dist(points[i], points[vp]);
}

void make(VPTree *node, int start, int end)
{
    node->idx = end;
    node->inner = node->outer = NULL;
    node->md = 0;

    if (start == end)
        return;
    int available_threads = MAX_THREADS - active_threads;
    if (available_threads > 0 && (end - start + 1) / 2 > MIN_WORK_PER_THREAD)
    {
        update_active_threads(+available_threads);
        calculate_distances_parallel(end - start, available_threads, node->idx);
        update_active_threads(-available_threads);
    }
    else
        calculate_distances_sequential(start, end, node->idx);

    double md = get_median(start, end);
    node->md = md;

    node->outer = malloc(sizeof(VPTree));
    make(node->outer, (start + end) / 2, end - 1);

    if ((start + end) / 2 - 1 < start)
        return;

    node->inner = malloc(sizeof(VPTree));
    make(node->inner, start, (start + end) / 2 - 1);
}

int main()
{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // seed for same results
    srand(42);
    // making space for points
    points = malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
        points[i] = malloc(d * sizeof(double));
    // fill points with random numbers
    for (int i = 0; i < n; i++)
        for (int j = 0; j < d; j++)
            points[i][j] = (double)rand() / RAND_MAX;

    // making space for distances
    distances = malloc(n * sizeof(double));

    VPTree *root = malloc(sizeof(VPTree));
    make(root, 0, n - 1);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    for (int i = 0; i < n - 1; i++)
        printf("%f\n", distances[i]);
    free(points);
    free(distances);
    return EXIT_SUCCESS;
}