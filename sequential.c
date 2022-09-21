#include <stdio.h>
#include <stdlib.h>
#include "select.h"
#include "utils.h"
#include "vp_tree.h"

int NUM_POINTS;
int DIM;

int main(int *argc, char *argv[])
{
    NUM_POINTS = atoi(argv[1]);
    DIM = atoi(argv[2]);

    // 1. Generate random set of n points with k dimensions
    double **dataset = create_dataset();
}