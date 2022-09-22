#include "structures.h"

extern int DIM;

void make_space(Set *S, int size)
{
    S->points = (double **)malloc(size * sizeof(double *));
    S->size = size;
    for (int i = 0; i < size; i++)
        S->points[i] = (double *)malloc(DIM * sizeof(double));
}

void change_space(Set *S, int size)
{
    S->points = (double **)realloc(S->points, size * sizeof(double *));
    S->size = size;
}