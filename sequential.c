#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "utils.h"
#include "quickselect.h"

extern int n;
extern int d;
extern double **points;
extern double *distances;

void make_vp_tree(VPTree *node, Set X)
{
    if (X.end < X.start)
    {
        printf("NULL\n");
        return;
    }
    printf("%d, %d\n", X.start, X.end);
    node = (VPTree *)malloc(sizeof(VPTree));

    node->idx = X.end;
    node->vp = points[X.end];

    calc_dist_seq(X);
    node->md = get_median(X);

    Set L = {X.start, (X.start + X.end) / 2 - 1};
    Set R = {(X.start + X.end) / 2, X.end - 1};

    make_vp_tree(node->inner, L);
    make_vp_tree(node->outer, R);
}