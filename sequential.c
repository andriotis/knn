#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "utils.h"
#include "quickselect.h"
extern int counter;
extern int n;
extern int d;

extern double **points;
extern double *distances;

void seq_make_vp_tree(VPTree *node, Set X)
{
    printf("entered vp_tree with %d, %d\n", X.start, X.end);
    node = (VPTree *)malloc(sizeof(VPTree));
    node->idx = X.end;
    node->vp = points[X.end];
    if (X.start == X.end)
    {
        printf("HIT\n");
        node->inner = node->outer = NULL;
        node->md = 0;
        return;
    }
    if (X.end < X.start)
    {
        printf("inside < if\n");
        return;
    }

    calc_dist_seq(X);
    node->md = get_median(X);

    Set L = {X.start, (X.start + X.end) / 2 - 1};
    Set R = {(X.start + X.end) / 2, X.end - 1};

    seq_make_vp_tree(node->inner, L);
    seq_make_vp_tree(node->outer, R);
}