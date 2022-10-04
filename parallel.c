#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "sequential.h"
#include "utils.h"
#include "structures.h"

extern int n;
extern int d;
extern double quickselect_time;

extern double **points;
extern double *distances;

extern int MAX_THREADS;

int active_threads = 1;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void par_make_vp_tree(VPTree *node, Set X)
{
    node = (VPTree *)malloc(sizeof(VPTree));
    printf("%d, %d\n", X.start, X.end);
    node->idx = X.end;
    node->vp = points[X.end];
    node->md = 0;
    node->inner = node->outer = NULL;

    if (X.start == X.end)
        return;

    calc_dist_seq(X);

    int available_threads = MAX_THREADS - active_threads;
    if (available_threads)
    {
        pthread_t dist_threads[available_threads];
        DistArgs *dist_args = calc_dist_args(X, available_threads);

        update_active_threads(+available_threads);

        for (int i = 0; i < available_threads; i++)
        {
            pthread_create(&dist_threads[i], NULL, &calc_dist_par, &dist_args[i]);
            pthread_join(dist_threads[i], NULL);
        }

        update_active_threads(-available_threads);
    }
    else
        calc_dist_seq(X);

    node->md = get_median(X);

    Set L = {X.start, (X.start + X.end) / 2 - 1};
    Set R = {(X.start + X.end) / 2, X.end - 1};

    seq_make_vp_tree(node->outer, R);

    if (L.end < L.start)
        return;

    seq_make_vp_tree(node->inner, L);
}
