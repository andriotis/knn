#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "utils.h"
#include "quickselect.h"

extern int n;
extern int d;
extern double **points;

void make_vp_tree(VPTree *node, Set X)
{
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~Start~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("start : %d & end : %d\n", X.start, X.end);

    if (X.start == X.end)
    {
        node->idx = X.end;
        node->md = 0;
        node->vp = points[X.end];
        node->inner = NULL;
        node->outer = NULL;
    }
    else
    {
        double *distances = (double *)malloc((X.end - X.start) * sizeof(double));
        for (int i = X.start; i < X.end; i++)
        {
            printf("%d ( ", i);
            distances[i] = euclidean_dist(points[i], points[X.end]);
            for (int j = 0; j < d; j++)
                printf("%.2f ", points[i][j]);
            printf(") => %.2f\n", distances[i]);
        }

        node->md = get_median(distances, X.end - X.start);

        printf("REACHED HERE\n");
        // // Find inner set's bounds
        Set L;
        L.start = X.start;
        L.end = (X.end - X.start) / 2 - 1;
        // // Find outer set's bounds
        Set R;
        R.start = L.end + 1;
        R.end = X.end - 1;

        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~End~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        // node->inner = (VPTree *)malloc(sizeof(VPTree));
        make_vp_tree(node->inner, L);
        // node->outer = (VPTree *)malloc(sizeof(VPTree));
        make_vp_tree(node->outer, R);
    }
}