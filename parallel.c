#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "utils.h"
#include "structures.h"

extern int n;
extern int d;
extern int t;

extern double **points;
extern double *distances;

DistArgs *calc_dist_args(Set X);
void *calc_dist_par(void *args);
void *routine(void *args);

DistArgs *calc_dist_args(Set X)
{
    DistArgs *args = (DistArgs *)malloc(t * sizeof(DistArgs));
    for (int i = 0; i < t; i++)
    {
        args[i].num_points = (X.end - X.start) / t;
        if (i < (X.end - X.start) % t)
            args[i].num_points++;

        args[i].start = 0;
        for (int j = 0; j < i; j++)
            args[i].start += args[j].num_points;
    }
    return args;
}

void *calc_dist_par(void *args)
{
    DistArgs *chunk = (DistArgs *)args;
    for (int i = chunk->start; i < chunk->start + chunk->num_points; i++)
        distances[i] = euclidean_dist(points[i], points[chunk->vp_idx]);
}

void make_vp_tree(VPTree *node, Set X)
{
    if (X.end < X.start)
        return;
    printf("%d, %d\n", X.start, X.end);
    node = (VPTree *)malloc(sizeof(VPTree));

    node->idx = X.end;
    node->vp = points[X.end];

    pthread_t *threads = (pthread_t *)malloc(t * sizeof(pthread_t));

    DistArgs *d_args = calc_dist_args(X);
    for (int i = 0; i < t; i++)
    {
        pthread_create(&threads[i], NULL, &calc_dist_par, &d_args[i]);
        pthread_join(threads[i], NULL);
    }

    node->md = get_median(X);

    Set L = {X.start, (X.start + X.end) / 2 - 1};
    Set R = {(X.start + X.end) / 2, X.end - 1};

    pthread_t *inner_thread = (pthread_t *)malloc(sizeof(pthread_t));
    TreeArgs *t_args = (TreeArgs *)malloc(sizeof(TreeArgs));

    t_args->node = node->inner;
    t_args->X = L;

    pthread_create(inner_thread, NULL, &routine, t_args);
    pthread_detach(*inner_thread);

    make_vp_tree(node->outer, R);
}

void *routine(void *args)
{
    TreeArgs *t_args = (TreeArgs *)args;
    make_vp_tree(t_args->node, t_args->X);
    pthread_exit(NULL);
}